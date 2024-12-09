module ahb_monitor #(
    parameter string log_filename = "ahb_trace",
    parameter ADDR_WIDTH = 32,
    parameter DATA_WIDTH = 32
)(
    input logic HCLK,
    input logic HRESETn,
    input logic HSEL,
    input logic HREADY,
    input logic HWRITE,
    input logic [ADDR_WIDTH-1:0] HADDR,
    input logic [DATA_WIDTH-1:0] HWDATA,
    input logic [DATA_WIDTH-1:0] HRDATA,
    input logic [1:0] HRESP,
    input logic [2:0] HSIZE,
    input logic [2:0] HBURST,
    input logic [3:0] HPROT,
    input logic [1:0] HTRANS
);

    string log_filename_full;
    // File handle
    integer log_file;
    logic first_entry;

    logic [63:0] cycle_cnt;

    // Define a structure to hold transfer information
    typedef struct {
        logic [ADDR_WIDTH-1:0] HADDR;
        logic HWRITE;
        logic [2:0] HSIZE;
        logic [2:0] HBURST;
        logic [3:0] HPROT;
        logic [1:0] HTRANS;
        time time_stamp;
        logic [63:0] cycle_stamp;
    } ahb_transfer_t;

    // Queue to store address and control information
    ahb_transfer_t transfer_queue[$];

    // Open log file
    initial begin
        log_filename_full = $sformatf("npa_db/%s.json", log_filename);
        log_file = $fopen(log_filename_full, "w");
        $timeformat(-9, 3, " ns", 10);
        // Write the beginning of the JSON array
        $fwrite(log_file, "[\n");
        first_entry = 1;
        cycle_cnt = '0;
    end

    // Monitor AHB signals and write to log file
    always@(posedge HCLK or negedge HRESETn) begin
        if (!HRESETn) begin
            cycle_cnt <= '0;
            transfer_queue = {};
        end else begin
            cycle_cnt <= cycle_cnt + 1'b1;

            // Address phase: when HSEL and HREADY are valid, and HTRANS indicates a valid transfer
            if (HSEL && HREADY && HTRANS[1]) begin // HTRANS[1] is 1 indicates non-idle transfer
                // Capture address and control signals
                ahb_transfer_t transfer;
                transfer.HADDR = HADDR;
                transfer.HWRITE = HWRITE;
                transfer.HSIZE = HSIZE;
                transfer.HBURST = HBURST;
                transfer.HPROT = HPROT;
                transfer.HTRANS = HTRANS;
                transfer.time_stamp = $time;
                transfer.cycle_stamp = cycle_cnt;
                // Add transfer information to the queue
                transfer_queue.push_back(transfer);
            end

            // Data phase: when HREADY is valid, indicating data transfer is complete
            if (HREADY) begin
                if (transfer_queue.size() > 0) begin
                    ahb_transfer_t completed_transfer;
                    // Remove the corresponding transfer information from the queue
                    completed_transfer = transfer_queue.pop_front();

                    if (first_entry) begin
                        first_entry = 0;
                    end else begin
                        $fwrite(log_file, ",\n");
                    end

                    if (completed_transfer.HWRITE) begin
                        // For write transfers, HWDATA is driven by the master during the data phase
                        $fwrite(log_file, "  {\"type\": \"AHB_WR\", \"time\": \"%0t\", \"cycle\": %0d, \"HADDR\": \"%h\", \"HWDATA\": \"%h\", \"HSIZE\": \"%h\", \"HBURST\": \"%h\", \"HPROT\": \"%h\", \"HRESP\": \"%h\"}",
                        completed_transfer.time_stamp, completed_transfer.cycle_stamp, 
                        completed_transfer.HADDR, HWDATA, // Sample HWDATA during the data phase
                        completed_transfer.HSIZE, completed_transfer.HBURST, completed_transfer.HPROT, HRESP);
                    end else begin
                        // For read transfers, HRDATA is driven by the slave during the data phase
                        $fwrite(log_file, "  {\"type\": \"AHB_RD\", \"time\": \"%0t\", \"cycle\": %0d, \"HADDR\": \"%h\", \"HRDATA\": \"%h\", \"HSIZE\": \"%h\", \"HBURST\": \"%h\", \"HPROT\": \"%h\", \"HRESP\": \"%h\"}",
                        completed_transfer.time_stamp, completed_transfer.cycle_stamp, 
                        completed_transfer.HADDR, HRDATA,
                        completed_transfer.HSIZE, completed_transfer.HBURST, completed_transfer.HPROT, HRESP);
                    end
                end 
                //else begin
                //    // If there are no pending transfers, it may be an error condition
                //    // Can print a warning message
                //    $display("Warning: HREADY asserted but no transfer in queue at time %t", $time);
                //end
            end
        end
    end

    // Task: close log file
    task close_log_file;
        begin
            // Close JSON array
            $fwrite(log_file, "\n]\n");
            $fclose(log_file);
        end
    endtask

    // Call task to close log file at the end
    final begin
        close_log_file();
    end

endmodule

