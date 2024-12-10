module axi_monitor #(
    parameter string log_filename = "axi_trace",
    parameter ADDR_WIDTH = 32,
    parameter DATA_WIDTH = 32,
    parameter ID_WIDTH = 4
)(
    input logic ACLK,
    input logic ARESETn,

    // Write address channel signals
    input logic [ID_WIDTH-1:0] AWID,
    input logic [ADDR_WIDTH-1:0] AWADDR,
    input logic [7:0] AWLEN,
    input logic [2:0] AWSIZE,
    input logic [1:0] AWBURST,
    input logic AWVALID,
    input logic AWREADY,

    // Write data channel signals
    input logic [DATA_WIDTH-1:0] WDATA,
    input logic [DATA_WIDTH/8-1:0] WSTRB,
    input logic WLAST,
    input logic WVALID,
    input logic WREADY,

    // Write response channel signals
    input logic [ID_WIDTH-1:0] BID,
    input logic [1:0] BRESP,
    input logic BVALID,
    input logic BREADY,

    // Read address channel signals
    input logic [ID_WIDTH-1:0] ARID,
    input logic [ADDR_WIDTH-1:0] ARADDR,
    input logic [7:0] ARLEN,
    input logic [2:0] ARSIZE,
    input logic [1:0] ARBURST,
    input logic ARVALID,
    input logic ARREADY,

    // Read data channel signals
    input logic [ID_WIDTH-1:0] RID,
    input logic [DATA_WIDTH-1:0] RDATA,
    input logic [1:0] RRESP,
    input logic RLAST,
    input logic RVALID,
    input logic RREADY
);

    string log_filename_aw;
    string log_filename_w;
    string log_filename_b;
    string log_filename_ar;
    string log_filename_r;

    // File handle
    integer log_file_aw ;
    integer log_file_w  ;
    integer log_file_b  ;
    integer log_file_ar ;
    integer log_file_r  ;

    logic first_entry_aw ; 
    logic first_entry_w  ; 
    logic first_entry_b  ; 
    logic first_entry_ar ; 
    logic first_entry_r  ; 

    logic [63:0] cycle_cnt;

    // Open log file
    initial begin
        log_filename_aw = $sformatf("npa_db/%s_aw.json", log_filename);
        log_filename_w  = $sformatf("npa_db/%s_w.json", log_filename);
        log_filename_b  = $sformatf("npa_db/%s_b.json", log_filename);
        log_filename_ar = $sformatf("npa_db/%s_ar.json", log_filename);
        log_filename_r  = $sformatf("npa_db/%s_r.json", log_filename);
        log_file_aw = $fopen(log_filename_aw, "w");
        log_file_w  = $fopen(log_filename_w, "w");
        log_file_b  = $fopen(log_filename_b, "w");
        log_file_ar = $fopen(log_filename_ar, "w");
        log_file_r  = $fopen(log_filename_r, "w");
        $timeformat(-9, 2, " ns", 10);
        // Write the beginning of the JSON array
        $fwrite(log_file_aw , "[\n");
        $fwrite(log_file_w  , "[\n");
        $fwrite(log_file_b  , "[\n");
        $fwrite(log_file_ar , "[\n");
        $fwrite(log_file_r  , "[\n");
        first_entry_aw  = 1;
        first_entry_w   = 1;
        first_entry_b   = 1;
        first_entry_ar  = 1;
        first_entry_r   = 1;
    end

    // Monitor AXI signals and write to log file
    always@(posedge ACLK or negedge ARESETn) begin
        if (!ARESETn) begin
            cycle_cnt <= '0;
        end else begin
            cycle_cnt <= cycle_cnt + 1'b1;

            // Write address channel
            if (AWVALID && AWREADY) begin
                if (first_entry_aw) begin
                    first_entry_aw = 0;
                end else begin
                    $fwrite(log_file_aw, ",\n");
                end
                $fwrite(log_file_aw, "  {\"type\": \"AXI_AW\", \"time\": \"%0t\", \"cycle\": %0d, \"AWID\": \"%h\", \"AWADDR\": \"%h\", \"AWLEN\": \"%h\", \"AWSIZE\": \"%h\", \"AWBURST\": \"%h\"}",
                    $time, cycle_cnt, AWID, AWADDR, AWLEN, AWSIZE, AWBURST);
            end

            // Write data channel
            if (WVALID && WREADY) begin
                if (first_entry_w) begin
                    first_entry_w = 0;
                end else begin
                    $fwrite(log_file_w, ",\n");
                end
                $fwrite(log_file_w, "  {\"type\": \"AXI_W\", \"time\": \"%0t\", \"cycle\": %0d, \"WDATA\": \"%h\", \"WSTRB\": \"%h\", \"WLAST\": %b}",
                    $time, cycle_cnt, WDATA, WSTRB, WLAST);
            end

            // Write response channel
            if (BVALID && BREADY) begin
                if (first_entry_b) begin
                    first_entry_b = 0;
                end else begin
                    $fwrite(log_file_b, ",\n");
                end
                $fwrite(log_file_b, "  {\"type\": \"AXI_B\", \"time\": \"%0t\", \"cycle\": %0d, \"BID\": \"%h\", \"BRESP\": \"%h\"}",
                    $time, cycle_cnt, BID, BRESP);
            end

            // Read address channel
            if (ARVALID && ARREADY) begin
                if (first_entry_ar) begin
                    first_entry_ar = 0;
                end else begin
                    $fwrite(log_file_ar, ",\n");
                end
                $fwrite(log_file_ar, "  {\"type\": \"AXI_AR\", \"time\": \"%0t\", \"cycle\": %0d, \"ARID\": \"%h\", \"ARADDR\": \"%h\", \"ARLEN\": \"%h\", \"ARSIZE\": \"%h\", \"ARBURST\": \"%h\"}",
                    $time, cycle_cnt, ARID, ARADDR, ARLEN, ARSIZE, ARBURST);
            end

            // Read data channel
            if (RVALID && RREADY) begin
                if (first_entry_r) begin
                    first_entry_r = 0;
                end else begin
                    $fwrite(log_file_r, ",\n");
                end
                $fwrite(log_file_r, "  {\"type\": \"AXI_R\", \"time\": \"%0t\", \"cycle\": %0d, \"RID\": \"%h\", \"RDATA\": \"%h\", \"RRESP\": \"%h\", \"RLAST\": %b}",
                    $time, cycle_cnt, RID, RDATA, RRESP, RLAST);
            end
        end
    end

    // Task to close log file
    task close_log_file(int file);
        begin
            // Close the JSON array
            $fwrite(file, "\n]\n");
            $fclose(file);
        end
    endtask

    // Call the task to close log file at the end
    final begin
        close_log_file(log_file_aw );
        close_log_file(log_file_w  );
        close_log_file(log_file_b  );
        close_log_file(log_file_ar );
        close_log_file(log_file_r  );
    end

endmodule

