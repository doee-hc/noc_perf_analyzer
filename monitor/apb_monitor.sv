module apb_monitor #(
    parameter string log_filename = "apb_trace",
    parameter ADDR_WIDTH,
    parameter DATA_WIDTH
)(
    input logic PCLK,
    input logic PRESETn,
    input logic PSEL,
    input logic PENABLE,
    input logic PWRITE,
    input logic [ADDR_WIDTH-1:0] PADDR,
    input logic [DATA_WIDTH-1:0] PWDATA,
    input logic [DATA_WIDTH-1:0] PRDATA,
    input logic PREADY,
    input logic [DATA_WIDTH/8-1:0] PSTRB,
    input logic PSLVERR
);

    string log_filename_full;
    // File handle
    integer log_file;
    logic first_entry;

    logic [63:0] cycle_cnt;

    // Open log file
    initial begin
        log_filename_full = $sformatf("npa_db/%s.json", log_filename);
        log_file = $fopen(log_filename_full, "w");
        $timeformat(-9, 3, " ns", 10);
        // Write the beginning of the JSON array
        $fwrite(log_file, "[\n");
        first_entry = 1;
    end

    // Monitor APB signals and write to log file
    always@(posedge PCLK or negedge PRESETn) begin
        if (!PRESETn) begin
            cycle_cnt <= '0;
        end else begin
            cycle_cnt <= cycle_cnt + 1'b1;

            // Bus phase
            if (PSEL && !PREADY) begin
                if (first_entry) begin
                    first_entry = 0;
                end else begin
                    $fwrite(log_file, ",\n");
                end
                $fwrite(log_file, "  {\"type\": \"BP\", \"time\": \"%0t\", \"cycle\": %0d}",
                    $time, cycle_cnt);
            end

            // Transaction phase
            if (PSEL && PENABLE) begin
                if (first_entry) begin
                    first_entry = 0;
                end else begin
                    $fwrite(log_file, ",\n");
                end
                if (PWRITE) begin
                    $fwrite(log_file, "  {\"type\": \"APB_WR\", \"time\": \"%0t\", \"cycle\": %0d, \"PADDR\": \"%h\", \"PWDATA\": \"%h\", \"PRDATA\": \"%h\", \"PWRITE\": %b, \"PREADY\": %b, \"PSTRB\": \"%b\", \"PSLVERR\": %b}",
                    $time, cycle_cnt, PADDR, PWDATA, PRDATA, PWRITE, PREADY, PSTRB, PSLVERR);
                end else begin
                    $fwrite(log_file, "  {\"type\": \"APB_RD\", \"time\": \"%0t\", \"cycle\": %0d, \"PADDR\": \"%h\", \"PWDATA\": \"%h\", \"PRDATA\": \"%h\", \"PWRITE\": %b, \"PREADY\": %b, \"PSTRB\": \"%b\", \"PSLVERR\": %b}",
                    $time, cycle_cnt, PADDR, PWDATA, PRDATA, PWRITE, PREADY, PSTRB, PSLVERR);

                end
            end
        end
    end

    // Task to close log file
    task close_log_file;
        begin
            // Close the JSON array
            $fwrite(log_file, "\n]\n");
            $fclose(log_file);
        end
    endtask

    // Call the task to close log file at the end
    final begin
        close_log_file();
    end

endmodule

