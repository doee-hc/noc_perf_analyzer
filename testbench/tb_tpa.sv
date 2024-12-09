`include "bus_define.svh"

module tb_npa;

    // Instantiate APB monitor with filename as parameter
    apb_monitor #(
        .log_filename("apb_cru_top"), // Pass the filename as parameter
        .ADDR_WIDTH(32),
        .DATA_WIDTH(32)
    ) u_apb_mon_cru_top(
        .PCLK       (`pclk_cru_top       ),
        .PRESETn    (`presetn_cru_top    ),
        .PSEL       (`psel_cru_top       ),
        .PENABLE    (`penable_cru_top    ),
        .PWRITE     (`pwrite_cru_top     ),
        .PADDR      (`paddr_cru_top      ),
        .PWDATA     (`pwdata_cru_top     ),
        .PRDATA     (`prdata_cru_top     ),
        .PREADY     (`pready_cru_top     ),
        .PSTRB      (`pstrb_cru_top      ),
        .PSLVERR    (`pslverr_cru_top    )
    );

// Instantiate AXI monitor with filename as parameter
axi_monitor #(
    .log_filename("axi_core0_d"), // Pass the filename as parameter
    .ADDR_WIDTH(32),
    .DATA_WIDTH(64),
    .ID_WIDTH(4)
) u_axi_mon_core0_d(
    .ACLK       (`aclk_core0_d       ),
    .ARESETn    (`aresetn_core0_d    ),

    // Write address channel signals
    .AWID       (`awid_core0_d       ),
    .AWADDR     (`awaddr_core0_d     ),
    .AWLEN      (`awlen_core0_d      ),
    .AWSIZE     (`awsize_core0_d     ),
    .AWBURST    (`awburst_core0_d    ),
    .AWVALID    (`awvalid_core0_d    ),
    .AWREADY    (`awready_core0_d    ),

    // Write data channel signals
    .WDATA      (`wdata_core0_d      ),
    .WSTRB      (`wstrb_core0_d      ),
    .WLAST      (`wlast_core0_d      ),
    .WVALID     (`wvalid_core0_d     ),
    .WREADY     (`wready_core0_d     ),

    // Write response channel signals
    .BID        (`bid_core0_d        ),
    .BRESP      (`bresp_core0_d      ),
    .BVALID     (`bvalid_core0_d     ),
    .BREADY     (`bready_core0_d     ),

    // Read address channel signals
    .ARID       (`arid_core0_d       ),
    .ARADDR     (`araddr_core0_d     ),
    .ARLEN      (`arlen_core0_d      ),
    .ARSIZE     (`arsize_core0_d     ),
    .ARBURST    (`arburst_core0_d    ),
    .ARVALID    (`arvalid_core0_d    ),
    .ARREADY    (`arready_core0_d    ),

    // Read data channel signals
    .RID        (`rid_core0_d        ),
    .RDATA      (`rdata_core0_d      ),
    .RRESP      (`rresp_core0_d      ),
    .RLAST      (`rlast_core0_d      ),
    .RVALID     (`rvalid_core0_d     ),
    .RREADY     (`rready_core0_d     )
);

axi_monitor #(
    .log_filename("axi_core0_dma_m1"), // Pass the filename as parameter
    .ADDR_WIDTH(40),
    .DATA_WIDTH(256),
    .ID_WIDTH(4)
) u_axi_mon_core0_dma_m1(
    .ACLK       (`aclk_core0_dma_m1       ),
    .ARESETn    (`aresetn_core0_dma_m1    ),

    // Write address channel signals
    .AWID       (`awid_core0_dma_m1       ),
    .AWADDR     (`awaddr_core0_dma_m1     ),
    .AWLEN      (`awlen_core0_dma_m1      ),
    .AWSIZE     (`awsize_core0_dma_m1     ),
    .AWBURST    (`awburst_core0_dma_m1    ),
    .AWVALID    (`awvalid_core0_dma_m1    ),
    .AWREADY    (`awready_core0_dma_m1    ),

    // Write data channel signals
    .WDATA      (`wdata_core0_dma_m1      ),
    .WSTRB      (`wstrb_core0_dma_m1      ),
    .WLAST      (`wlast_core0_dma_m1      ),
    .WVALID     (`wvalid_core0_dma_m1     ),
    .WREADY     (`wready_core0_dma_m1     ),

    // Write response channel signals
    .BID        (`bid_core0_dma_m1        ),
    .BRESP      (`bresp_core0_dma_m1      ),
    .BVALID     (`bvalid_core0_dma_m1     ),
    .BREADY     (`bready_core0_dma_m1     ),

    // Read address channel signals
    .ARID       (`arid_core0_dma_m1       ),
    .ARADDR     (`araddr_core0_dma_m1     ),
    .ARLEN      (`arlen_core0_dma_m1      ),
    .ARSIZE     (`arsize_core0_dma_m1     ),
    .ARBURST    (`arburst_core0_dma_m1    ),
    .ARVALID    (`arvalid_core0_dma_m1    ),
    .ARREADY    (`arready_core0_dma_m1    ),

    // Read data channel signals
    .RID        (`rid_core0_dma_m1        ),
    .RDATA      (`rdata_core0_dma_m1      ),
    .RRESP      (`rresp_core0_dma_m1      ),
    .RLAST      (`rlast_core0_dma_m1      ),
    .RVALID     (`rvalid_core0_dma_m1     ),
    .RREADY     (`rready_core0_dma_m1     )
);

// Instantiate AHB monitor with filename as parameter
ahb_monitor #(
    .log_filename("ahb_core1_slv"), // Pass the filename as parameter
    .ADDR_WIDTH(32),
    .DATA_WIDTH(64)
) u_ahb_mon_core1_slv(
    .HCLK       (`hclk_core1_slv       ),
    .HRESETn    (`hresetn_core1_slv    ),

    // AHB signals
    .HSEL       (`hsel_core1_slv       ),
    .HREADY     (`hready_core1_slv     ),
    .HWRITE     (`hwrite_core1_slv     ),
    .HADDR      (`haddr_core1_slv      ),
    .HWDATA     (`hwdata_core1_slv     ),
    .HRDATA     (`hrdata_core1_slv     ),
    .HRESP      (`hresp_core1_slv      ),
    .HSIZE      (`hsize_core1_slv      ),
    .HBURST     (`hburst_core1_slv     ),
    .HPROT      (`hprot_core1_slv      ),
    .HTRANS     (`htrans_core1_slv     )
);

endmodule


