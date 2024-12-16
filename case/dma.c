#include "dma.h"
#include "common.h"


//A poor version of 'pow' fuction by user.
static uint32_t pow_u(uint32_t a,uint32_t b){
    uint32_t res=1;
    if(!b)
        return 1;
    while(b--){
        res *= a;
    }
    return res;
}


void dma_init_start(DMA_InitTypeDef *p)
{
    reg32( AXI_DMA_BASE + DMAC_CFGREG) = DMAC_CFGREG_DMAC_EN | DMAC_CFGREG_INT_EN;  // Enable AXI DMA
    reg32( AXI_DMA_BASE + DMAC_CHENREG) = DMAC_CHENREG_CH1_EN;  // Enable AXI DMA Channel 1
    // TODO

    /* set source address of channelx */
    reg32( AXI_DMA_BASE + CHx_SAR_0(p->DMA_Channel) ) = p->DMA_SrcAddr;  //SAR0
    /* set destination address of channelx */
    reg32( AXI_DMA_BASE + CHx_DAR_0(p->DMA_Channel) ) = p->DMA_DstAddr;  //DAR0


    reg32( AXI_DMA_BASE + CHx_CTL_0(p->DMA_Channel) ) =    (p->DMA_IntrEn?1:0) << 0   | // 0 INT_EN : Enable interrupt
                                            
                                            // DMA_DATA_WIDTH_8    0
                                            // DMA_DATA_WIDTH_16   1
                                            // DMA_DATA_WIDTH_32   2
                                            // DMA_DATA_WIDTH_64   3
                                            // DMA_DATA_WIDTH_128  4
                                            p->DMA_DstDataWidth << 1   | // 3:1 DST_TR_WIDTH: Dst transfer width 
                                            p->DMA_SrcDataWidth << 4   | // 6:4 SRC_TR_WIDTH: Src transfer width 
                                            
                                            
                                            // DMA_ADDR_INC        0
                                            // DMA_ADDR_DEC        1
                                            // DMA_ADDR_NO_CHANGE  2
                                            p->DMA_DstInc << 7   | // 8:7 DINC: If Increments the destination address
                                            p->DMA_SrcInc << 9   | // 10:9 SINC: If Increments the source address
                                            
                                            // DMA_DATA_MSIZE_1 	0
                                            // DMA_DATA_MSIZE_4 	1
                                            // DMA_DATA_MSIZE_8 	2
                                            // DMA_DATA_MSIZE_16 	3
                                            // DMA_DATA_MSIZE_32 	4
                                            // DMA_DATA_MSIZE_64 	5
                                            // DMA_DATA_MSIZE_128 	6
                                            // DMA_DATA_MSIZE_256 	7                                            
                                            p->DMA_DstMSize << 11  | // 13:11 DEST_MSIZE: Number of data items to be transferred (each burst transaction)
                                            p->DMA_SrcMSize << 14  | // 16:14 SRC_MSIZE: Number of data items to be transferred (each burst transaction)
                                            
                                            0 << 17  | // 17 SRC_GATHER_EN: Disable source gather
                                            0 << 18  | // 18 DST_SCATTER_EN: Disable destination scatter

                                            // DMA_M2M_FC_DMAC 	0   :Memory to Memory and Flow Controller is DW_ahb_dmac 
                                            // DMA_M2P_FC_DMAC 	1   :Memory to Peripharal and Flow Controller is DW_ahb_dmac 
                                            // DMA_P2M_FC_DMAC 	2   :Peripharal to Memory and Flow Controller is DW_ahb_dmac 
                                            // DMA_P2P_FC_DMAC 	3   :Peripharal to Peripharal and Flow Controller is DW_ahb_dmac
                                            // DMA_P2M_FC_PSRC 	4   :Peripharal to Memory and Flow Controller is Peripharal_Src
                                            // DMA_P2P_FC_PSRC 	5   :Peripharal to Peripharal and Flow Controller is Peripharal_Src
                                            // DMA_M2P_FC_PDST 	6   :Memory to Peripharal and Flow Controller is Peripharal_Dst
                                            // DMA_P2P_FC_PDST 	7   :Peripharal to Peripharal and Flow Controller is Peripharal_Dst               
                                            p->DMA_Mode << 20  ; // 22:20 TT_FC: Transfer type                            
                                    

    uint32_t DMA_BlockSize = p->DMA_BlockSize_Byte/pow_u(2,p->DMA_SrcDataWidth);        //True Block size in byte is decided by the src_data_width
    reg32( AXI_DMA_BASE + CHx_CTL_32(p->DMA_Channel) ) = DMA_BlockSize;  // b:32 BLOCK_TS: Total Size of a block


    reg32( AXI_DMA_BASE + CHx_CFG_0(p->DMA_Channel) ) =    0 << 8  |//8 CH_SUSP: Disable channel suspend
                                            0 << 10 |//10 HS_SEL_DST: Select hardware handshaking for Dst
                                            0 << 11 |//11 HS_SEL_SRC: Select hardware handshaking for Src
                                            2 << 14 |//15:14 bus lock
                                            (p->DMA_BusLockEn?1:0) << 17 |//17 bus lock enable
                                            0 << 18 |//18 DST_HS_POL: Active high
                                            0 << 19 |//19 SRC_HS_POL: Active high
                                            0 << 20 |//29:20 MAX_ABRST: Maximum AMBA burst length for DMA transfers is 15
                                            0 << 30 |//30 RELOAD_SRC: Source reload disabled (automatically reloaded from its initial value at the end of every block for multi-block transfers)
                                            0 << 31 ;//31 RELOAD_DST: Destination reload disabled

    reg32( AXI_DMA_BASE + CHx_CFG_32(p->DMA_Channel) ) =   0 << (33-32) | //33 FIFO_MODE: Data available is greater than or equal to half the FIFO depth for destination transfers and space available is greater than half the fifo depth for source transfers.
                                            1 << (34 -32 ) | //Protection Control bits 1'b1 to HPROT[0]
                                            /*** The specification does not allow the source and destination to use the same interface. 
                                             Memory not use handshaking interface so SRC_PER and DEST_PER can be set to any of the all 16 interfaces when using Memory.***/
                                            p->DMA_Src_HandShakeIF << (39-32) | //b:39 SRC_PER: Use hardware handshaking interface 0
                                            p->DMA_Dst_HandShakeIF << (43-32) | //b:43 DEST_PER: Use hardware handshaking interface 0
                                            0       ;//32 FCMODE: Data pre-fetching is disabled

    reg32( AXI_DMA_BASE + DMAC_CFGREG_0 ) = 0x1;  //DMA_CFG: Enable DMAC
    reg32( AXI_DMA_BASE + DMAC_CHENREG_0 ) = (DMA_CH(p->DMA_Channel) << 8) | DMA_CH(p->DMA_Channel);    //Enable DMA CHx 
    //im_printf("\nInfo:dma ch%d,data transfer start.\n",p->DMA_Channel);
}



volatile uint8_t sta_tfr;
volatile uint8_t sta_err;

bool dma_wait_transfer_complete(DMA_InitTypeDef *p,uint32_t timeout){
    //wait for transfer completion
    //check channel 0 Transfer Complete interrupts
    uint32_t n = 0;
    uint8_t i;
    uint32_t times = 0;


    //Wait until all channel transfer complete.
    while(reg32(AXI_DMA_BASE + DMAC_CHENREG_0) & 0xff){

        if(timeout < 0xffffffff){
            times++;
            if(times >= timeout){
                im_printf("\nError:dma ch%d,data transfer timeout.\n",i);
                break;
            }
        }//else wait permanetly.

        sta_tfr = reg32( AXI_DMA_BASE + DMAC_STATUSTFR ) & 0xff;   //Check transfer complete interrupt.
        sta_err = reg32( AXI_DMA_BASE + DMAC_STATUSERR ) & 0xff;   //Check transfer error interrupt.

        //Check error
        if(sta_err){
            for(i=0;i<8;i++){
                if((sta_err>>i)&0x01){
                    im_printf("\nError:dma ch%d,data transfer error.\n",i+1);
                    reg32( AXI_DMA_BASE + DMAC_MASKERR) = (uint32_t)sta_err << 8;        //Clear Transfer error interrupt status
                }
            }
            return FALSE;
        }
        //Check transfer complete
        if(sta_tfr){
            for(i=0;i<8;i++){
                if((sta_tfr>>i)&0x01){
                    im_printf("\nInfo:dma ch%d,data transfer complete.\n",i+1);
                    reg32( AXI_DMA_BASE + DMAC_MASKTFR) = (uint32_t)sta_tfr << 8;        //Clear Transfer Complete interrupt status
                }
            }
        }
    }
    //All channel transfer compelte,print the last channel's information
    sta_tfr = reg32( AXI_DMA_BASE + DMAC_STATUSTFR ) & 0xff;   //Check transfer complete interrupt.
    if(sta_tfr){
        for(i=0;i<8;i++){
            if((sta_tfr>>i)&0x01){
                im_printf("\nInfo:dma ch%d,data transfer complete.\n",i+1);
                reg32( AXI_DMA_BASE + DMAC_MASKTFR) = (uint32_t)sta_tfr << 8;        //Clear Transfer Complete interrupt status
            }
        }
    }
    return TRUE;
} 

void dma_multiblk_init_start(DMA_InitTypeDef *p)
{
    
    reg32( AXI_DMA_BASE + DMAC_CLEARTFR )      = 0xffffffff;  //ClearTFR: clear bit for the channelx transfer done interrupt
    reg32( AXI_DMA_BASE + DMAC_CLEARBLOCK )    = 0xffffffff;  //ClearBlock: clear bit for block done interrupt
    reg32( AXI_DMA_BASE + DMAC_CLEARSRCTRAN )  = 0xffffffff;  //ClearSrcTran: clear bit for src transaction done interrupt
    reg32( AXI_DMA_BASE + DMAC_CLEARDSTTRAN )  = 0xffffffff;  //ClearDstTran: clear bit for dst transaction done interrupt
    reg32( AXI_DMA_BASE + DMAC_CLEARERR )      = 0xffffffff;  //ClearErr: clear bit for error interrupt
    
    reg32( AXI_DMA_BASE + DMAC_MASKBLOCK )    = 0xffffffff;
    reg32( AXI_DMA_BASE + DMAC_MASKTFR )       = 0xffffffff;  //MaskTfr: mask bit for chx transfer complete interrupt


    reg32( AXI_DMA_BASE + CHx_CTL_0(p->DMA_Channel) ) =    0x1         <<27|//LLP_DST_EN       1
                                                        0x1         <<28;//LLP_SRC_EN       1

    reg32( AXI_DMA_BASE + CHx_LLP_0(p->DMA_Channel) ) = p[0].DMA_LLIAddr;  //First LLI Address.
    

    reg32( AXI_DMA_BASE + CHx_CFG_0(p->DMA_Channel) ) =   0         <<5 |//CH_PRIOR        
                                            0 << 8  |//8 CH_SUSP: Disable channel suspend
                                            0 << 10 |//10 HS_SEL_DST: Select hardware handshaking for Dst
                                            0 << 11 |//11 HS_SEL_SRC: Select hardware handshaking for Src
                                            0 << 18 |//18 DST_HS_POL: Active high
                                            0 << 19 |//19 SRC_HS_POL: Active high
                                            0 << 20 |//29:20 MAX_ABRST: Maximum AMBA burst length for DMA transfers is 15
                                            0 << 30 |//30 RELOAD_SRC: Source reload disabled (automatically reloaded from its initial value at the end of every block for multi-block transfers)
                                            0 << 31 ;//31 RELOAD_DST: Destination reload disabled

    reg32( AXI_DMA_BASE + CHx_CFG_32(p->DMA_Channel) ) =   0 << (33-32) | //33 FIFO_MODE: Data available is greater than or equal to half the FIFO depth for destination transfers and space available is greater than half the fifo depth for source transfers.
                                            1 << (34 -32 ) | //Protection Control bits 1'b1 to HPROT[0]
                                            /*** The specification does not allow the source and destination to use the same interface. 
                                             Memory not use handshaking interface so SRC_PER and DEST_PER can be set to any of the all 16 interfaces when using Memory.***/
                                            p->DMA_Src_HandShakeIF << (39-32) | //b:39 SRC_PER: Use hardware handshaking interface 0
                                            p->DMA_Dst_HandShakeIF << (43-32) | //b:43 DEST_PER: Use hardware handshaking interface 0
                                            0       ;//32 FCMODE: Data pre-fetching is disabled 


    // Configuration of every item of this block chain
    uint32_t i=0;
    for(i=0;i<p->DMA_NumofLLI;i++){
        reg32( p[i].DMA_LLIAddr + LLI_SAR ) = p[i].DMA_SrcAddr;  //SAR
        reg32( p[i].DMA_LLIAddr + LLI_DAR ) = p[i].DMA_DstAddr;  //DAR

        reg32( p[i].DMA_LLIAddr + LLI_CTL_0 ) = (p[i].DMA_IntrEn?1:0) << 0   | // 0 INT_EN : Enable interrupt
                                            
                                            // DMA_DATA_WIDTH_8    0
                                            // DMA_DATA_WIDTH_16   1
                                            // DMA_DATA_WIDTH_32   2
                                            // DMA_DATA_WIDTH_64   3
                                            // DMA_DATA_WIDTH_128  4
                                            p[i].DMA_DstDataWidth << 1   | // 3:1 DST_TR_WIDTH: Dst transfer width 
                                            p[i].DMA_SrcDataWidth << 4   | // 6:4 SRC_TR_WIDTH: Src transfer width 
                                            
                                            
                                            // DMA_ADDR_INC        0
                                            // DMA_ADDR_DEC        1
                                            // DMA_ADDR_NO_CHANGE  2
                                            p[i].DMA_DstInc << 7   | // 8:7 DINC: If Increments the destination address
                                            p[i].DMA_SrcInc << 9   | // 10:9 SINC: If Increments the source address
                                            
                                            // DMA_DATA_MSIZE_1 	0
                                            // DMA_DATA_MSIZE_4 	1
                                            // DMA_DATA_MSIZE_8 	2
                                            // DMA_DATA_MSIZE_16 	3
                                            // DMA_DATA_MSIZE_32 	4
                                            // DMA_DATA_MSIZE_64 	5
                                            // DMA_DATA_MSIZE_128 	6
                                            // DMA_DATA_MSIZE_256 	7                                            
                                            p[i].DMA_DstMSize << 11  | // 13:11 DEST_MSIZE: Number of data items to be transferred (each burst transaction)
                                            p[i].DMA_SrcMSize << 14  | // 16:14 SRC_MSIZE: Number of data items to be transferred (each burst transaction)
                                            
                                            0 << 17  | // 17 SRC_GATHER_EN: Disable source gather
                                            0 << 18  | // 18 DST_SCATTER_EN: Disable destination scatter

                                            // DMA_M2M_FC_DMAC 	0   :Memory to Memory and Flow Controller is DW_ahb_dmac 
                                            // DMA_M2P_FC_DMAC 	1   :Memory to Peripharal and Flow Controller is DW_ahb_dmac 
                                            // DMA_P2M_FC_DMAC 	2   :Peripharal to Memory and Flow Controller is DW_ahb_dmac 
                                            // DMA_P2P_FC_DMAC 	3   :Peripharal to Peripharal and Flow Controller is DW_ahb_dmac
                                            // DMA_P2M_FC_PSRC 	4   :Peripharal to Memory and Flow Controller is Peripharal_Src
                                            // DMA_P2P_FC_PSRC 	5   :Peripharal to Peripharal and Flow Controller is Peripharal_Src
                                            // DMA_M2P_FC_PDST 	6   :Memory to Peripharal and Flow Controller is Peripharal_Dst
                                            // DMA_P2P_FC_PDST 	7   :Peripharal to Peripharal and Flow Controller is Peripharal_Dst               
                                            p[i].DMA_Mode << 20 | // 22:20 TT_FC: Transfer type  

                                            (p[i].DMA_NextLLIAddr?1:0)      <<27 |//LLP_DST_EN   
                                            (p[i].DMA_NextLLIAddr?1:0)      <<28;//LLP_SRC_EN                              
        
        uint32_t DMA_BlockSize = p[i].DMA_BlockSize_Byte/pow_u(2,p[i].DMA_SrcDataWidth);        //True Block size in byte is decided by the src_data_width
        reg32( p[i].DMA_LLIAddr + LLI_CTL_32) = DMA_BlockSize;  // b:32 BLOCK_TS: Total Size of a block
 


        if(p[i].DMA_NextLLIAddr)
            reg32( p[i].DMA_LLIAddr + LLI_LLP ) = p[i].DMA_NextLLIAddr; //Next LLI Address
        else{
            reg32( p[i].DMA_LLIAddr + LLI_LLP ) = 0; //Error: No next LLI address.
            break;     //Last item of this block chain, break
        }
    }
    reg32( AXI_DMA_BASE + DMAC_CFGREG_0 ) = 0x1;  //DMA_CFG: Enable DMAC
    reg32( AXI_DMA_BASE + DMAC_CHENREG_0 ) = (DMA_CH(p->DMA_Channel) << 8) | DMA_CH(p->DMA_Channel);    //Enable DMA CHx 
}



