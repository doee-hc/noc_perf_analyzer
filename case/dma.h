#ifndef __DMA_H__
#define __DMA_H__

#include "stdint.h"



typedef struct 
{ 
    uint32_t DMA_Channel;		//One of ch1-ch8
	uint32_t DMA_SrcAddr; 		//Dma source address
	uint32_t DMA_DstAddr; 		//Dma destination address
	uint32_t DMA_BlockSize_Byte;	//Every dma transfer data size in byte. 
									//Note: please keep DMA_BlockSize_Byte/(Source Data Width in byte) be a integer .
									//Bad example:DMA_BlockSize_Byte = 3,DMA_SrcDataWidth = DMA_DATA_WIDTH_32
	uint32_t DMA_SrcInc; 		//If source address increment
	uint32_t DMA_DstInc; 		//If destination address increment
	uint32_t DMA_SrcDataWidth; 	//Source data width. note: dccm only support 32bits access
	uint32_t DMA_DstDataWidth; 	//Destination data width
	uint32_t DMA_SrcMSize;		//Decide how much data a burst transaction carry
								//If ('data to be send' size < DMA_SrcMSize),dma controller would use single transaction automaticlly.
								//If it is set to 1,dma controller would use single transaction.
	uint32_t DMA_DstMSize;		//Same as DMA_SrcMSize
	uint32_t DMA_Mode;			//Decide srouce and destination type:Memory or Peripharal.
								//Also decide the flow controller: Srouce or Destination or dma controller.
								//Usually flow controller is set to dmac
	uint32_t DMA_Src_HandShakeIF;	//Source handshaking interface index.It is only useful when src is peripharal
	uint32_t DMA_Dst_HandShakeIF;	//Destination handshaking interface index.It is only useful when dst is peripharal
	uint32_t DMA_LLIAddr;			// Link list item(LLI) address
	uint32_t DMA_NextLLIAddr;		// Next link list item address 
	uint32_t DMA_NumofLLI;			//Number of LLI
	uint32_t DMA_LLP_Handle;		// Set by user,it can be any value. It's a ID of this Block chain,we use it to identify which block chain the LLI is belong to.
	uint32_t DMA_IntrEn;			//Interrupt enable
	uint32_t DMA_BusLockEn;			//Bus lock en
} DMA_InitTypeDef;


//Initial DMA reg(CTLx CFGx) and enable DMA channel to start,for single block transfer
void dma_init_start(DMA_InitTypeDef *p);		

//Initial DMA reg(CTLx CFGx) and enable DMA channel to start,for multi block transfer(Use LLP)	
void dma_multiblk_init_start(DMA_InitTypeDef *p);

//Wait all DMA channel transfer complete 
bool dma_wait_transfer_complete(DMA_InitTypeDef *p,uint32_t timeout);


// AXI DMA Common Reg
#define DMAC_IDREG                          0x00
#define DMAC_COMPVERREG                     0x08
#define DMAC_CFGREG                         0x10
#define DMAC_CHENREG                        0x18
//#define DMAC_CHSUSPREG                      0x20
//#define DMAC_CHABORTREG                     0x28
#define DMAC_INTSTATUSREG                   0x30
#define DMAC_COMMONREG_INTCLEARREG          0x38
#define DMAC_COMMONREG_INTSTATUS_ENABLEREG  0x40
#define DMAC_COMMONREG_INTSIGNAL_ENABLEREG  0x48
#define DMAC_COMMONREG_INTSTATUSREG         0x50
#define DMAC_RESETREG                       0x58
#define DMAC_LOWPOWER_CFGREG                0x60

#define DMAC_CFGREG_DMAC_EN                 (1 << 0)
#define DMAC_CFGREG_INT_EN                  (1 << 1)

#define DMAC_CHENREG_CH1_EN                 (1 << 0)
#define DMAC_CHENREG_CH2_EN                 (1 << 1)
#define DMAC_CHENREG_CH3_EN                 (1 << 2)
#define DMAC_CHENREG_CH4_EN                 (1 << 3)
#define DMAC_CHENREG_CH5_EN                 (1 << 4)
#define DMAC_CHENREG_CH6_EN                 (1 << 5)
#define DMAC_CHENREG_CH7_EN                 (1 << 6)
#define DMAC_CHENREG_CH8_EN                 (1 << 7)
#define DMAC_CHENREG_CH1_EN_WE              (1 << 8)
#define DMAC_CHENREG_CH2_EN_WE              (1 << 9)
#define DMAC_CHENREG_CH3_EN_WE              (1 << 10)
#define DMAC_CHENREG_CH4_EN_WE              (1 << 11)
#define DMAC_CHENREG_CH5_EN_WE              (1 << 12)
#define DMAC_CHENREG_CH6_EN_WE              (1 << 13)
#define DMAC_CHENREG_CH7_EN_WE              (1 << 14)
#define DMAC_CHENREG_CH8_EN_WE              (1 << 15)

#define DMAC_CHENREG_CH1_SUSP               (1 << 16)
#define DMAC_CHENREG_CH2_SUSP               (1 << 17)
#define DMAC_CHENREG_CH3_SUSP               (1 << 18)
#define DMAC_CHENREG_CH4_SUSP               (1 << 19)
#define DMAC_CHENREG_CH5_SUSP               (1 << 20)
#define DMAC_CHENREG_CH6_SUSP               (1 << 21)
#define DMAC_CHENREG_CH7_SUSP               (1 << 22)
#define DMAC_CHENREG_CH8_SUSP               (1 << 23)
#define DMAC_CHENREG_CH1_SUSP_WE            (1 << 24)
#define DMAC_CHENREG_CH2_SUSP_WE            (1 << 25)
#define DMAC_CHENREG_CH3_SUSP_WE            (1 << 26)
#define DMAC_CHENREG_CH4_SUSP_WE            (1 << 27)
#define DMAC_CHENREG_CH5_SUSP_WE            (1 << 28)
#define DMAC_CHENREG_CH6_SUSP_WE            (1 << 29)
#define DMAC_CHENREG_CH7_SUSP_WE            (1 << 30)
#define DMAC_CHENREG_CH8_SUSP_WE            (1 << 31)

#define DMAC_CHENREG_CH1_ABORT              (1 << 32)
#define DMAC_CHENREG_CH2_ABORT              (1 << 33)
#define DMAC_CHENREG_CH3_ABORT              (1 << 34)
#define DMAC_CHENREG_CH4_ABORT              (1 << 35)
#define DMAC_CHENREG_CH5_ABORT              (1 << 36)
#define DMAC_CHENREG_CH6_ABORT              (1 << 37)
#define DMAC_CHENREG_CH7_ABORT              (1 << 38)
#define DMAC_CHENREG_CH8_ABORT              (1 << 39)
#define DMAC_CHENREG_CH1_ABORT_WE           (1 << 40)
#define DMAC_CHENREG_CH2_ABORT_WE           (1 << 41)
#define DMAC_CHENREG_CH3_ABORT_WE           (1 << 42)
#define DMAC_CHENREG_CH4_ABORT_WE           (1 << 43)
#define DMAC_CHENREG_CH5_ABORT_WE           (1 << 44)
#define DMAC_CHENREG_CH6_ABORT_WE           (1 << 45)
#define DMAC_CHENREG_CH7_ABORT_WE           (1 << 46)
#define DMAC_CHENREG_CH8_ABORT_WE           (1 << 47)

#define DMAC_INTSTATUSREG_CH1_IntStat       (1 << 0)
#define DMAC_INTSTATUSREG_CH2_IntStat       (1 << 1)
#define DMAC_INTSTATUSREG_CH3_IntStat       (1 << 2)
#define DMAC_INTSTATUSREG_CH4_IntStat       (1 << 3)
#define DMAC_INTSTATUSREG_CH5_IntStat       (1 << 4)
#define DMAC_INTSTATUSREG_CH6_IntStat       (1 << 5)
#define DMAC_INTSTATUSREG_CH7_IntStat       (1 << 6)
#define DMAC_INTSTATUSREG_CH8_IntStat       (1 << 7)
#define DMAC_INTSTATUSREG_CommonReg_IntStat (1 << 16)

#define DMAC_COMMONREG_INTCLEARREG_Clear_SLVIF_CommonReg_DEC_ERR_IntStat        (1 << 0)
#define DMAC_COMMONREG_INTCLEARREG_Clear_SLVIF_CommonReg_WR2RO_ERR_IntStat      (1 << 1)
#define DMAC_COMMONREG_INTCLEARREG_Clear_SLVIF_CommonReg_RD2WO_ERR_IntStat      (1 << 2)
#define DMAC_COMMONREG_INTCLEARREG_Clear_SLVIF_CommonReg_WrOnHold_ERR_IntStat   (1 << 3)
#define DMAC_COMMONREG_INTCLEARREG_Clear_SLVIF_UndefinedReg_DEC_ERR_IntStat     (1 << 8)

#define DMAC_COMMONREG_INTSTATUS_ENABLEREG_Enable_SLVIF_CommonReg_DEC_ERR_IntStat        (1 << 0)
#define DMAC_COMMONREG_INTSTATUS_ENABLEREG_Enable_SLVIF_CommonReg_WR2RO_ERR_IntStat      (1 << 1)
#define DMAC_COMMONREG_INTSTATUS_ENABLEREG_Enable_SLVIF_CommonReg_RD2WO_ERR_IntStat      (1 << 2)
#define DMAC_COMMONREG_INTSTATUS_ENABLEREG_Enable_SLVIF_CommonReg_WrOnHold_ERR_IntStat   (1 << 3)
#define DMAC_COMMONREG_INTSTATUS_ENABLEREG_Enable_SLVIF_UndefinedReg_DEC_ERR_IntStat     (1 << 8)

#define DMAC_COMMONREG_INTSIGNAL_ENABLEREG_Enable_SLVIF_CommonReg_DEC_ERR_IntSignal        (1 << 0)
#define DMAC_COMMONREG_INTSIGNAL_ENABLEREG_Enable_SLVIF_CommonReg_WR2RO_ERR_IntSignal      (1 << 1)
#define DMAC_COMMONREG_INTSIGNAL_ENABLEREG_Enable_SLVIF_CommonReg_RD2WO_ERR_IntSignal      (1 << 2)
#define DMAC_COMMONREG_INTSIGNAL_ENABLEREG_Enable_SLVIF_CommonReg_WrOnHold_ERR_IntSignal   (1 << 3)
#define DMAC_COMMONREG_INTSIGNAL_ENABLEREG_Enable_SLVIF_UndefinedReg_DEC_ERR_IntSignal     (1 << 8)

#define DMAC_COMMONREG_INTSTATUSREG_SLVIF_CommonReg_DEC_ERR_IntStat        (1 << 0)
#define DMAC_COMMONREG_INTSTATUSREG_SLVIF_CommonReg_WR2RO_ERR_IntStat      (1 << 1)
#define DMAC_COMMONREG_INTSTATUSREG_SLVIF_CommonReg_RD2WO_ERR_IntStat      (1 << 2)
#define DMAC_COMMONREG_INTSTATUSREG_SLVIF_CommonReg_WrOnHold_ERR_IntStat   (1 << 3)
#define DMAC_COMMONREG_INTSTATUSREG_SLVIF_UndefinedReg_DEC_ERR_IntStat     (1 << 8)

#define DMAC_RESETREG_DMAC_RST                  (1 << 0)

// TODO: DMAC_LOWPOWER_CFGREG

// AXI DMA Channel Reg
#define CHx_SAR(ch)                                 (0x100+((ch-1)*0x100))
#define CHx_DAR(ch)                                 (0x108+((ch-1)*0x100))
#define CHx_BLOCK_TS(ch)                            (0x110+((ch-1)*0x100))
#define CHx_CTL(ch)                                 (0x118+((ch-1)*0x100))
#define CHx_CFG(ch)                                 (0x120+((ch-1)*0x100))
#define CHx_LLP(ch)                                 (0x128+((ch-1)*0x100))
#define CHx_STATUSREG(ch)                           (0x130+((ch-1)*0x100))
#define CHx_SWHSSRCREG(ch)                          (0x138+((ch-1)*0x100))
#define CHx_SWHSDSTREG(ch)                          (0x140+((ch-1)*0x100))
#define CHx_BLK_TFR_RESUMEREQREG(ch)                (0x148+((ch-1)*0x100))
#define CHx_AXI_IDREG(ch)                           (0x150+((ch-1)*0x100))
#define CHx_AXI_QOSREG(ch)                          (0x158+((ch-1)*0x100))
#define CHx_SSTAT(ch)                               (0x160+((ch-1)*0x100))
#define CHx_DSTAT(ch)                               (0x168+((ch-1)*0x100))
#define CHx_SSTATAR(ch)                             (0x170+((ch-1)*0x100))
#define CHx_DSTATAR(ch)                             (0x178+((ch-1)*0x100))
#define CHx_INTSTATUS_ENABLEREG(ch)                 (0x180+((ch-1)*0x100))
#define CHx_INTSTATUS(ch)                           (0x188+((ch-1)*0x100))
#define CHx_INTSIGNAL_ENABLEREG(ch)                 (0x190+((ch-1)*0x100))
#define CHx_INTCLEARREG(ch)                         (0x198+((ch-1)*0x100))

#define CHx_CTL_SMS_M1                          (0 << 0)
#define CHx_CTL_SMS_M2                          (1 << 0)
#define CHx_CTL_DMS_M1                          (0 << 2)
#define CHx_CTL_DMS_M2                          (1 << 2)
#define CHx_CTL_SINC                            (1 << 4)
#define CHx_CTL_DINC                            (1 << 6)
#define CHx_CTL_SRC_TR_WIDTH_8                  (0 << 8)
#define CHx_CTL_SRC_TR_WIDTH_16                 (1 << 8)
#define CHx_CTL_SRC_TR_WIDTH_32                 (2 << 8)
#define CHx_CTL_SRC_TR_WIDTH_64                 (3 << 8)
#define CHx_CTL_SRC_TR_WIDTH_128                (4 << 8)
#define CHx_CTL_SRC_TR_WIDTH_256                (5 << 8)
#define CHx_CTL_SRC_TR_WIDTH_512                (6 << 8)
#define CHx_CTL_DST_TR_WIDTH_8                  (0 << 11)
#define CHx_CTL_DST_TR_WIDTH_16                 (1 << 11)
#define CHx_CTL_DST_TR_WIDTH_32                 (2 << 11)
#define CHx_CTL_DST_TR_WIDTH_64                 (3 << 11)
#define CHx_CTL_DST_TR_WIDTH_128                (4 << 11)
#define CHx_CTL_DST_TR_WIDTH_256                (5 << 11)
#define CHx_CTL_DST_TR_WIDTH_512                (6 << 11)
#define CHx_CTL_SRC_MSIZE_1                     (0 << 14)
#define CHx_CTL_SRC_MSIZE_4                     (1 << 14)
#define CHx_CTL_SRC_MSIZE_8                     (2 << 14)
#define CHx_CTL_SRC_MSIZE_16                    (3 << 14)
#define CHx_CTL_SRC_MSIZE_32                    (4 << 14)
#define CHx_CTL_SRC_MSIZE_64                    (5 << 14)
#define CHx_CTL_SRC_MSIZE_128                   (6 << 14)
#define CHx_CTL_SRC_MSIZE_256                   (7 << 14)
#define CHx_CTL_SRC_MSIZE_512                   (8 << 14)
#define CHx_CTL_SRC_MSIZE_1024                  (9 << 14)
#define CHx_CTL_DST_MSIZE_1                     (0 << 18)
#define CHx_CTL_DST_MSIZE_4                     (1 << 18)
#define CHx_CTL_DST_MSIZE_8                     (2 << 18)
#define CHx_CTL_DST_MSIZE_16                    (3 << 18)
#define CHx_CTL_DST_MSIZE_32                    (4 << 18)
#define CHx_CTL_DST_MSIZE_64                    (5 << 18)
#define CHx_CTL_DST_MSIZE_128                   (6 << 18)
#define CHx_CTL_DST_MSIZE_256                   (7 << 18)
#define CHx_CTL_DST_MSIZE_512                   (8 << 18)
#define CHx_CTL_DST_MSIZE_1024                  (9 << 18)

// TODO: Ax_CACHE

#define CHx_CTL_NonPosted_LastWrite_Enable      (1 << 30)
#define CHx_CTL_NonPosted_LastWrite_Disable     (0 << 30)

// TODO: Ax_PROT 

#define CHx_CTL_ARLEN_Enable                    (1 << 38)
#define CHx_CTL_ARLEN_Disable                   (0 << 38)
#define CHx_CTL_ARLEN(n)                        (n << 39)
#define CHx_CTL_AWLEN_Enable                    (1 << 47)
#define CHx_CTL_AWLEN_Disable                   (0 << 47)
#define CHx_CTL_AWLEN(n)                        (n << 48)

#define CHx_CTL_SRC_STAT_EN                     (1 << 56)
#define CHx_CTL_DST_STAT_EN                     (1 << 57)
#define CHx_CTL_IOC_BlkTfr_EN                   (1 << 58)
#define CHx_CTL_SHADOWREG_OR_LLI_LAST           (1 << 62)
#define CHx_CTL_SHADOWREG_OR_LLI_VALID          (1 << 63)

#define CHx_CFG_SRC_MULTBLK_TYPE_Contiguous     (0 << 0)
#define CHx_CFG_SRC_MULTBLK_TYPE_Reload         (1 << 0)
#define CHx_CFG_SRC_MULTBLK_TYPE_ShadowRegister (2 << 0)
#define CHx_CFG_SRC_MULTBLK_TYPE_LinkedList     (3 << 0)

#define CHx_CFG_DST_MULTBLK_TYPE_Contiguous     (0 << 2)
#define CHx_CFG_DST_MULTBLK_TYPE_Reload         (1 << 2)
#define CHx_CFG_DST_MULTBLK_TYPE_ShadowRegister (2 << 2)
#define CHx_CFG_DST_MULTBLK_TYPE_LinkedList     (3 << 2)

#define CHx_CFG_TT_FC_M2M_DMAC                  (0 << 32)
#define CHx_CFG_TT_FC_M2P_DMAC                  (1 << 32)
#define CHx_CFG_TT_FC_P2M_DMAC                  (2 << 32)
#define CHx_CFG_TT_FC_P2P_DMAC                  (3 << 32)
#define CHx_CFG_TT_FC_P2M_SRC                   (4 << 32)
#define CHx_CFG_TT_FC_P2P_SRC                   (5 << 32)
#define CHx_CFG_TT_FC_M2P_DST                   (6 << 32)
#define CHx_CFG_TT_FC_P2P_DST                   (7 << 32)

#define CHx_CFG_HS_SEL_SRC_HARDWARE_HS          (0 << 35)
#define CHx_CFG_HS_SEL_SRC_SOFTWARE_HS          (1 << 35)

#define CHx_CFG_HS_SEL_DST_HARDWARE_HS          (0 << 36)
#define CHx_CFG_HS_SEL_DST_SOFTWARE_HS          (1 << 36)

#define CHx_CFG_HS_SEL_SRC_HWHS_POL_HIGH        (0 << 37)
#define CHx_CFG_HS_SEL_SRC_HWHS_POL_LOW         (1 << 37)

#define CHx_CFG_HS_SEL_DST_HWHS_POL_HIGH        (0 << 38)
#define CHx_CFG_HS_SEL_DST_HWHS_POL_LOW         (1 << 38)

#define CHx_CFG_SRC_PER_HS_IF(n)                (n << 39)
#define CHx_CFG_DST_PER_HS_IF(n)                (n << 44)
#define CHx_CFG_CH_PRIOR(n)                     (n << 48)
#define CHx_CFG_CH_PRIOR(n)                     (n << 49)

#define CHx_CFG_LOCK_CH                         (1 << 52)

#define CHx_CFG_LOCK_CH_L_DMAtransfer           (0 << 53)
#define CHx_CFG_LOCK_CH_L_BLOCKtransfer         (1 << 53)

#define CHx_CFG_SRC_OSR_LMT(n)                  (n << 55)
#define CHx_CFG_DST_OSR_LMT(n)                  (n << 59)

#define CHx_CFG_DST_OSR_LMT(n)                  (n << 59)


// TODO LLP Reg

#define CHx_STATUSREG_CMPLTD_BLK_TFR_SIZE_MASK      (0x3fffff)
#define CHx_STATUSREG_DATA_LEFT_IN_FIFO_MASK        (0x8fff00000000)

#define CHx_SWHSSRCREG_SWHS_REQ_SRC                 (1 << 0)
#define CHx_SWHSSRCREG_SWHS_REQ_SRC_WE              (1 << 1)
#define CHx_SWHSSRCREG_SWHS_SGLREQ_SRC              (1 << 2)
#define CHx_SWHSSRCREG_SWHS_SGLREQ_SRC_WE           (1 << 3)
#define CHx_SWHSSRCREG_SWHS_LST_SRC                 (1 << 4)
#define CHx_SWHSSRCREG_SWHS_LST_SRC_WE              (1 << 5)

#define CHx_SWHSDSTREG_SWHS_REQ_DST                 (1 << 0)
#define CHx_SWHSDSTREG_SWHS_REQ_DST_WE              (1 << 1)
#define CHx_SWHSDSTREG_SWHS_SGLREQ_DST              (1 << 2)
#define CHx_SWHSDSTREG_SWHS_SGLREQ_DST_WE           (1 << 3)
#define CHx_SWHSDSTREG_SWHS_LST_DST                 (1 << 4)
#define CHx_SWHSDSTREG_SWHS_LST_DST_WE              (1 << 5)

// TODO CHx_BLK_TFR_RESUMEREQREG

#define CHx_AXI_IDREG_AXI_READ_ID_SUFFIX(n)         (n << 0)
#define CHx_AXI_IDREG_AXI_WRITE_ID_SUFFIX(n)        (n << 16)

#define CHx_AXI_QOSREG_AXI_AWQOS(n)                 (n << 0)
#define CHx_AXI_QOSREG_AXI_ARQOS(n)                 (n << 4)

#define CHx_SSTAT_SSTAT_MASK                        0xffffffff
#define CHx_DSTAT_DSTAT_MASK                        0xffffffff


#endif
