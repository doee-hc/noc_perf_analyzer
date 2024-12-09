`ifndef __bus_define__
`define __bus_define__

    `define pclk_cru_top     tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_NODE0BUSDDR.U_NODE0BUSDDR.clk_periclk_i
    `define presetn_cru_top  tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_NODE0BUSDDR.U_NODE0BUSDDR.n0_apb_peri_preset_no
    `define paddr_cru_top    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_NODE0BUSDDR.U_NODE0BUSDDR.n0_apb_peri_paddr_o
    `define penable_cru_top  tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_NODE0BUSDDR.U_NODE0BUSDDR.n0_apb_peri_penable_o
    `define pwdata_cru_top   tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_NODE0BUSDDR.U_NODE0BUSDDR.n0_apb_peri_pwdata_o
    `define prdata_cru_top   tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_NODE0BUSDDR.U_NODE0BUSDDR.n0_apb_peri_prdata_i
    `define pwrite_cru_top   tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_NODE0BUSDDR.U_NODE0BUSDDR.n0_apb_peri_pwrite_o
    `define pready_cru_top   tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_NODE0BUSDDR.U_NODE0BUSDDR.n0_apb_peri_pready_i
    `define pstrb_cru_top    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_NODE0BUSDDR.U_NODE0BUSDDR.n0_apb_peri_pstrb_o
    `define psel_cru_top     tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CORE0_APB.psel_cru_top
    `define pslverr_cru_top  tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_NODE0BUSDDR.U_NODE0BUSDDR.n0_apb_peri_pslverr_i

    // core0 data axi
    `define awid_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_awid[3:0]
    `define awaddr_core0_d  tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_awaddr[31:0]
    `define awlen_core0_d   tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_awlen[7:0]
    `define awsize_core0_d  tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_awsize[2:0]
    `define awburst_core0_d  tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_awburst[1:0]
    `define awvalid_core0_d  tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_awvalid
    `define awready_core0_d  tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_awready

    `define wdata_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_wdata[63:0]
    `define wstrb_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_wstrb[7:0]
    `define wlast_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_wlast
    `define wvalid_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_wvalid
    `define wready_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_wready

    `define bid_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_bid[3:0]
    `define bresp_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_bresp[1:0]
    `define bvalid_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_bvalid
    `define bready_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_bready

    `define aclk_core0_d tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.aclk 
    `define aresetn_core0_d tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.aresetn
    `define arid_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_arid[3:0]
    `define araddr_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_araddr[31:0]
    `define arlen_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_arlen[7:0]
    `define arsize_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_arsize[2:0]
    `define arburst_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_arburst[1:0]
    `define arvalid_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_arvalid
    `define arready_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_arready

    `define rid_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_rid[3:0]
    `define rdata_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_rdata[63:0]
    `define rresp_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_rresp[1:0]
    `define rlast_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_rlast
    `define rvalid_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_rvalid
    `define rready_core0_d    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_INTF_CPU0_SUBSYSTEM.U_NODE0_CPU_SUBSYSTEM.d_rready

    // core0 dma axi m1
    `define aclk_core0_dma_m1      tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.dmac_core_clock
    `define aresetn_core0_dma_m1   tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.dmac_core_resetn

    `define awid_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.awid_m1[3:0]
    `define awaddr_core0_dma_m1  tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.awaddr_m1[39:0]
    `define awlen_core0_dma_m1   tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.awlen_m1[7:0]
    `define awsize_core0_dma_m1  tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.awsize_m1[2:0]
    `define awburst_core0_dma_m1  tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.awburst_m1[1:0]
    `define awvalid_core0_dma_m1  tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.awvalid_m1
    `define awready_core0_dma_m1  tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.awready_m1

    `define wdata_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.wdata_m1[255:0]
    `define wstrb_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.wstrb_m1[31:0]
    `define wlast_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.wlast_m1
    `define wvalid_core0_dma_m1   tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.wvalid_m1
    `define wready_core0_dma_m1   tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.wready_m1

    `define bid_core0_dma_m1       tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.bid_m1[3:0]
    `define bresp_core0_dma_m1     tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.bresp_m1[1:0]
    `define bvalid_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.bvalid_m1
    `define bready_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.bready_m1

    `define arid_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.arid_m1[3:0]
    `define araddr_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.araddr_m1[39:0]
    `define arlen_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.arlen_m1[7:0]
    `define arsize_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.arsize_m1[2:0]
    `define arburst_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.arburst_m1[1:0]
    `define arvalid_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.arvalid_m1
    `define arready_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.arready_m1

    `define rid_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.rid_m1[3:0]
    `define rdata_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.rdata_m1[255:0]
    `define rresp_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.rresp_m1[1:0]
    `define rlast_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.rlast_m1
    `define rvalid_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.rvalid_m1
    `define rready_core0_dma_m1    tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE00_TOP.U_INTF_CPU0_SYSTEM.U_AXI_DMA.rready_m1

    `define hclk_core1_slv          tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE01_TOP.U_INTF_CPUN_SYSTEM.U_INTF_CPUN_SUBSYSTEM.U_NODEN_CPU_SUBSYSTEM.core_clk[0:0]
    `define hresetn_core1_slv       tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE01_TOP.U_INTF_CPUN_SYSTEM.U_INTF_CPUN_SUBSYSTEM.U_NODEN_CPU_SUBSYSTEM.core_resetn[0:0]
    `define hsel_core1_slv          tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE01_TOP.U_INTF_CPUN_SYSTEM.U_INTF_CPUN_SUBSYSTEM.U_NODEN_CPU_SUBSYSTEM.hart0_slv_hsel
    `define hready_core1_slv        tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE01_TOP.U_INTF_CPUN_SYSTEM.U_INTF_CPUN_SUBSYSTEM.U_NODEN_CPU_SUBSYSTEM.hart0_slv_hready
    `define hwrite_core1_slv        tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE01_TOP.U_INTF_CPUN_SYSTEM.U_INTF_CPUN_SUBSYSTEM.U_NODEN_CPU_SUBSYSTEM.hart0_slv_hwrite
    `define haddr_core1_slv         tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE01_TOP.U_INTF_CPUN_SYSTEM.U_INTF_CPUN_SUBSYSTEM.U_NODEN_CPU_SUBSYSTEM.hart0_slv_haddr[31:0]
    `define hwdata_core1_slv        tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE01_TOP.U_INTF_CPUN_SYSTEM.U_INTF_CPUN_SUBSYSTEM.U_NODEN_CPU_SUBSYSTEM.hart0_slv_hwdata[63:0]
    `define hrdata_core1_slv        tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE01_TOP.U_INTF_CPUN_SYSTEM.U_INTF_CPUN_SUBSYSTEM.U_NODEN_CPU_SUBSYSTEM.hart0_slv_hrdata[63:0]
    `define hresp_core1_slv         tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE01_TOP.U_INTF_CPUN_SYSTEM.U_INTF_CPUN_SUBSYSTEM.U_NODEN_CPU_SUBSYSTEM.hart0_slv_hresp[1:0]
    `define hsize_core1_slv         tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE01_TOP.U_INTF_CPUN_SYSTEM.U_INTF_CPUN_SUBSYSTEM.U_NODEN_CPU_SUBSYSTEM.hart0_slv_hsize[2:0]
    `define hburst_core1_slv        tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE01_TOP.U_INTF_CPUN_SYSTEM.U_INTF_CPUN_SUBSYSTEM.U_NODEN_CPU_SUBSYSTEM.hart0_slv_hburst[2:0]
    `define hprot_core1_slv         tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE01_TOP.U_INTF_CPUN_SYSTEM.U_INTF_CPUN_SUBSYSTEM.U_NODEN_CPU_SUBSYSTEM.hart0_slv_hprot[3:0]
    `define htrans_core1_slv        tb_chiplet_top.chip_row[0].chip_col[0].genblk1.u_chiplet_top.U_DIE_TOP.U_SYSTEM_16CORE_TOP.U_CORE01_TOP.U_INTF_CPUN_SYSTEM.U_INTF_CPUN_SUBSYSTEM.U_NODEN_CPU_SUBSYSTEM.hart0_slv_htrans[1:0]


`endif

