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




#define DMA_ADDR_INC        0
#define DMA_ADDR_DEC        1
#define DMA_ADDR_NO_CHANGE  2


#define DMA_DATA_WIDTH_8    0
#define DMA_DATA_WIDTH_16   1
#define DMA_DATA_WIDTH_32   2
#define DMA_DATA_WIDTH_64   3
#define DMA_DATA_WIDTH_128  4

#define DMA_DATA_MSIZE_1 	0
#define DMA_DATA_MSIZE_4 	1
#define DMA_DATA_MSIZE_8 	2
#define DMA_DATA_MSIZE_16 	3
#define DMA_DATA_MSIZE_32 	4
#define DMA_DATA_MSIZE_64 	5
#define DMA_DATA_MSIZE_128 	6
#define DMA_DATA_MSIZE_256 	7

#define DMA_M2M_FC_DMAC 	0
#define DMA_M2P_FC_DMAC 	1
#define DMA_P2M_FC_DMAC 	2
#define DMA_P2P_FC_DMAC 	3
#define DMA_P2M_FC_PSRC 	4
#define DMA_P2P_FC_PSRC 	5
#define DMA_M2P_FC_PDST 	6
#define DMA_P2P_FC_PDST 	7

#define DMA_CH(x) (1<<(x-1))

extern volatile uint8_t sta_tfr;
extern volatile uint8_t sta_err;


//Handshking Interface Index
 #define DMA_HS_ASSI0_DMA_TX  	 0  
 #define DMA_HS_ASSI0_DMA_RX  	 1     
 #define DMA_HS_ASSI1_DMA_TX  	 2     
 #define DMA_HS_ASSI1_DMA_RX  	 3     
 #define DMA_HS_ASSI2_DMA_TX  	 4     
 #define DMA_HS_ASSI2_DMA_RX  	 5     
 #define DMA_HS_ASSI3_DMA_TX  	 6     
 #define DMA_HS_ASSI3_DMA_RX  	 7     
 #define DMA_HS_I2S_DMA_TX  	 8     
 #define DMA_HS_I2S_DMA_RX  	 9     
//  #define DMA_HS_I2C0_DMA_TX  	10     
//  #define DMA_HS_I2C0_DMA_RX  	11     
 #define DMA_HS_ASSI4_DMA_TX  	10     
 #define DMA_HS_ASSI4_DMA_RX  	11     
 #define DMA_HS_ASSI5_DMA_TX  	12     
 #define DMA_HS_ASSI5_DMA_RX  	13     
//  #define DMA_HS_ASSI6_DMA_TX  	16     
//  #define DMA_HS_ASSI6_DMA_RX  	17     
//  #define DMA_HS_ASSI7_DMA_TX  	18     
//  #define DMA_HS_ASSI7_DMA_RX  	19     
//  #define DMA_HS_ASSI8_DMA_TX  	20     
//  #define DMA_HS_ASSI8_DMA_RX  	21     
//  #define DMA_HS_ASSI9_DMA_TX  	22     
//  #define DMA_HS_ASSI9_DMA_RX  	23     
//  #define DMA_HS_EMIF_DMA_TX  	24      
//  #define DMA_HS_EMIF_DMA_RX  	25      

//dmac interrupt register offset

#define DMAC_RAWTFR                               0x2c0
#define DMAC_RAWBLOCK                             0x2c8
#define DMAC_RAWSRCTRAN                           0x2d0
#define DMAC_RAWDSTTRAN                           0x2d8
#define DMAC_RAWERR                               0x2e0
#define DMAC_STATUSTFR                            0x2e8
#define DMAC_STATUSBLOCK                          0x2f0
#define DMAC_STATUSSRCTRAN                        0x2f8
#define DMAC_STATUSDSTTRAN                        0x300
#define DMAC_STATUSERR                            0x308
#define DMAC_MASKTFR                              0x310
#define DMAC_MASKBLOCK                            0x318
#define DMAC_MASKSRCTRAN                          0x320
#define DMAC_MASKDSTTRAN                          0x328
#define DMAC_MASKERR                              0x330
#define DMAC_CLEARTFR                             0x338
#define DMAC_CLEARBLOCK                           0x340
#define DMAC_CLEARSRCTRAN                         0x348
#define DMAC_CLEARDSTTRAN                         0x350
#define DMAC_CLEARERR                             0x358
#define DMAC_STATUSINT                            0x360

//DMAC/Software_Handshake Registers
#define DMACSRCREG                            0x368
#define DMACDSTREG                            0x370
#define DMAC_SGLRQSRCREG                          0x378
#define DMAC_SGLRQDSTREG                          0x380
#define DMAC_LSTSRCREG                            0x388
#define DMAC_LSTDSTREG                            0x390

//common register offset 
#define DMAC_CFGREG_0                             0x398
#define DMAC_CFGREG_32                            0x39c
#define DMAC_CHENREG_0                            0x3a0
#define DMAC_CHENREG_32                           0x3a4
#define DMAC_IDREG_0                              0x3a8
#define DMAC_IDREG_32                             0x3ac
#define DMAC_TESTREG_0                            0x3b0
#define DMAC_TESTREG_32                           0x3b4
#define DMAC_LPTIMEOUTREG_0                       0x3b8
#define DMAC_LPTIMEOUTREG_32                      0x3bc

#define DMAC_COMP_PARAMS6_0                       0x3c8
#define DMAC_COMP_PARAMS6_32                      0x3cc
#define DMAC_COMP_PARAMS5_0                       0x3d0
#define DMAC_COMP_PARAMS5_32                      0x3d4
#define DMAC_COMP_PARAMS4_0                       0x3d8
#define DMAC_COMP_PARAMS4_32                      0x3dc
#define DMAC_COMP_PARAMS3_0                       0x3e0
#define DMAC_COMP_PARAMS3_32                      0x3e4
#define DMAC_COMP_PARAMS2_0                       0x3e8
#define DMAC_COMP_PARAMS2_32                      0x3ec
#define DMAC_COMP_PARAMS1_0                       0x3f0
#define DMAC_COMP_PARAMS1_32                      0x3f4
#define DMAC_COMPSID_0                            0x3f8
#define DMAC_COMPSID_32                           0x3fc
/*
#define DMAC_CHSUSPREG_0                          0x20
#define DMAC_CHSUSPREG_32                         0x24
#define DMAC_CHABORTREG_0                         0x28
#define DMAC_CHABORTREG_32                        0x2c
#define DMAC_INTSTATUSREG_0                       0x30
#define DMAC_INTSTATUSREG_32                      0x34
#define DMAC_COMMONREG_INTCLEARREG_0              0x38
#define DMAC_COMMONREG_INTCLEARREG_32             0x3c
#define DMAC_COMMONREG_INTSTATUS_ENABLEREG_0      0x40
#define DMAC_COMMONREG_INTSTATUS_ENABLEREG_32     0x44
#define DMAC_COMMONREG_INTSIGNAL_ENABLEREG_0      0x48
#define DMAC_COMMONREG_INTSIGNAL_ENABLEREG_32     0x4c
#define DMAC_COMMONREG_INTSTATUSREG_0             0x50
#define DMAC_COMMONREG_INTSTATUSREG_32            0x54
#define DMAC_RESETREG_0                           0x58
#define DMAC_RESETREG_32                          0x5c
#define DMAC_LOWPOWER_CFGREG_0                    0x60
#define DMAC_LOWPOWER_CFGREG_32                   0x64
*/


//LLP register offset
#define LLI_SAR                                 0x00		//Only support 32bits access
#define LLI_DAR                                 0x04
#define LLI_LLP                                 0x08
#define LLI_CTL_0                              	0x0c
#define LLI_CTL_32                           	0x10
#define LLI_SSTAT_0                             0x14
#define LLI_SSTAT_32                            0x18
#define LLI_DSTAT_0                             0x1c
#define LLI_DSTAT_32                            0x20

//channel 1 register
#define CH1_SAR_0                                 0x00
#define CH1_SAR_32                                0x04
#define CH1_DAR_0                                 0x08
#define CH1_DAR_32                                0x0c
#define CH1_LLP_0                                 0x10
#define CH1_LLP_32                                0x14
#define CH1_CTL_0                                 0x18
#define CH1_CTL_32                                0x1c
#define CH1_SSTAT_0                               0x20
#define CH1_SSTAT_32                              0x24
#define CH1_DSTAT_0                               0x28
#define CH1_DSTAT_32                              0x2c
#define CH1_SSTATAR_0                             0x30
#define CH1_SSTATAR_32                            0x34
#define CH1_DSTATAR_0                             0x38
#define CH1_DSTATAR_32                            0x3c
#define CH1_CFG_0                                 0x40
#define CH1_CFG_32                                0x44
#define CH1_SGR_0                                 0x48
#define CH1_SGR_32                                0x4c
#define CH1_DSR_0                                 0x50
#define CH1_DSR_32                                0x54

//channel 2 register
#define CH2_SAR_0                                 (0x00+(1*0x58))
#define CH2_SAR_32                                (0x04+(1*0x58))
#define CH2_DAR_0                                 (0x08+(1*0x58))
#define CH2_DAR_32                                (0x0c+(1*0x58))
#define CH2_LLP_0                                 (0x10+(1*0x58))
#define CH2_LLP_32                                (0x14+(1*0x58))
#define CH2_CTL_0                                 (0x18+(1*0x58))
#define CH2_CTL_32                                (0x1c+(1*0x58))
#define CH2_SSTAT_0                               (0x20+(1*0x58))
#define CH2_SSTAT_32                              (0x24+(1*0x58))
#define CH2_DSTAT_0                               (0x28+(1*0x58))
#define CH2_DSTAT_32                              (0x2c+(1*0x58))
#define CH2_SSTATAR_0                             (0x30+(1*0x58))
#define CH2_SSTATAR_32                            (0x34+(1*0x58))
#define CH2_DSTATAR_0                             (0x38+(1*0x58))
#define CH2_DSTATAR_32                            (0x3c+(1*0x58))
#define CH2_CFG_0                                 (0x40+(1*0x58))
#define CH2_CFG_32                                (0x44+(1*0x58))
#define CH2_SGR_0                                 (0x48+(1*0x58))
#define CH2_SGR_32                                (0x4c+(1*0x58))
#define CH2_DSR_0                                 (0x50+(1*0x58))
#define CH2_DSR_32                                (0x54+(1*0x58))

//channel 3 register
#define CH3_SAR_0                                 (0x00+(2*0x58))
#define CH3_SAR_32                                (0x04+(2*0x58))
#define CH3_DAR_0                                 (0x08+(2*0x58))
#define CH3_DAR_32                                (0x0c+(2*0x58))
#define CH3_LLP_0                                 (0x10+(2*0x58))
#define CH3_LLP_32                                (0x14+(2*0x58))
#define CH3_CTL_0                                 (0x18+(2*0x58))
#define CH3_CTL_32                                (0x1c+(2*0x58))
#define CH3_SSTAT_0                               (0x20+(2*0x58))
#define CH3_SSTAT_32                              (0x24+(2*0x58))
#define CH3_DSTAT_0                               (0x28+(2*0x58))
#define CH3_DSTAT_32                              (0x2c+(2*0x58))
#define CH3_SSTATAR_0                             (0x30+(2*0x58))
#define CH3_SSTATAR_32                            (0x34+(2*0x58))
#define CH3_DSTATAR_0                             (0x38+(2*0x58))
#define CH3_DSTATAR_32                            (0x3c+(2*0x58))
#define CH3_CFG_0                                 (0x40+(2*0x58))
#define CH3_CFG_32                                (0x44+(2*0x58))
#define CH3_SGR_0                                 (0x48+(2*0x58))
#define CH3_SGR_32                                (0x4c+(2*0x58))
#define CH3_DSR_0                                 (0x50+(2*0x58))
#define CH3_DSR_32                                (0x54+(2*0x58))


//channel 4 register
#define CH4_SAR_0                                 (0x00+(3*0x58))
#define CH4_SAR_32                                (0x04+(3*0x58))
#define CH4_DAR_0                                 (0x08+(3*0x58))
#define CH4_DAR_32                                (0x0c+(3*0x58))
#define CH4_LLP_0                                 (0x10+(3*0x58))
#define CH4_LLP_32                                (0x14+(3*0x58))
#define CH4_CTL_0                                 (0x18+(3*0x58))
#define CH4_CTL_32                                (0x1c+(3*0x58))
#define CH4_SSTAT_0                               (0x20+(3*0x58))
#define CH4_SSTAT_32                              (0x24+(3*0x58))
#define CH4_DSTAT_0                               (0x28+(3*0x58))
#define CH4_DSTAT_32                              (0x2c+(3*0x58))
#define CH4_SSTATAR_0                             (0x30+(3*0x58))
#define CH4_SSTATAR_32                            (0x34+(3*0x58))
#define CH4_DSTATAR_0                             (0x38+(3*0x58))
#define CH4_DSTATAR_32                            (0x3c+(3*0x58))
#define CH4_CFG_0                                 (0x40+(3*0x58))
#define CH4_CFG_32                                (0x44+(3*0x58))
#define CH4_SGR_0                                 (0x48+(3*0x58))
#define CH4_SGR_32                                (0x4c+(3*0x58))
#define CH4_DSR_0                                 (0x50+(3*0x58))
#define CH4_DSR_32                                (0x54+(3*0x58))

//channel 5 register
#define CH5_SAR_0                                 (0x00+(4*0x58))
#define CH5_SAR_32                                (0x04+(4*0x58))
#define CH5_DAR_0                                 (0x08+(4*0x58))
#define CH5_DAR_32                                (0x0c+(4*0x58))
#define CH5_LLP_0                                 (0x10+(4*0x58))
#define CH5_LLP_32                                (0x14+(4*0x58))
#define CH5_CTL_0                                 (0x18+(4*0x58))
#define CH5_CTL_32                                (0x1c+(4*0x58))
#define CH5_SSTAT_0                               (0x20+(4*0x58))
#define CH5_SSTAT_32                              (0x24+(4*0x58))
#define CH5_DSTAT_0                               (0x28+(4*0x58))
#define CH5_DSTAT_32                              (0x2c+(4*0x58))
#define CH5_SSTATAR_0                             (0x30+(4*0x58))
#define CH5_SSTATAR_32                            (0x34+(4*0x58))
#define CH5_DSTATAR_0                             (0x38+(4*0x58))
#define CH5_DSTATAR_32                            (0x3c+(4*0x58))
#define CH5_CFG_0                                 (0x40+(4*0x58))
#define CH5_CFG_32                                (0x44+(4*0x58))
#define CH5_SGR_0                                 (0x48+(4*0x58))
#define CH5_SGR_32                                (0x4c+(4*0x58))
#define CH5_DSR_0                                 (0x50+(4*0x58))
#define CH5_DSR_32                                (0x54+(4*0x58))

//channel 6 register
#define CH6_SAR_0                                 (0x00+(5*0x58))
#define CH6_SAR_32                                (0x04+(5*0x58))
#define CH6_DAR_0                                 (0x08+(5*0x58))
#define CH6_DAR_32                                (0x0c+(5*0x58))
#define CH6_LLP_0                                 (0x10+(5*0x58))
#define CH6_LLP_32                                (0x14+(5*0x58))
#define CH6_CTL_0                                 (0x18+(5*0x58))
#define CH6_CTL_32                                (0x1c+(5*0x58))
#define CH6_SSTAT_0                               (0x20+(5*0x58))
#define CH6_SSTAT_32                              (0x24+(5*0x58))
#define CH6_DSTAT_0                               (0x28+(5*0x58))
#define CH6_DSTAT_32                              (0x2c+(5*0x58))
#define CH6_SSTATAR_0                             (0x30+(5*0x58))
#define CH6_SSTATAR_32                            (0x34+(5*0x58))
#define CH6_DSTATAR_0                             (0x38+(5*0x58))
#define CH6_DSTATAR_32                            (0x3c+(5*0x58))
#define CH6_CFG_0                                 (0x40+(5*0x58))
#define CH6_CFG_32                                (0x44+(5*0x58))
#define CH6_SGR_0                                 (0x48+(5*0x58))
#define CH6_SGR_32                                (0x4c+(5*0x58))
#define CH6_DSR_0                                 (0x50+(5*0x58))
#define CH6_DSR_32                                (0x54+(5*0x58))

//channel 7 register
#define CH7_SAR_0                                 (0x00+(6*0x58))
#define CH7_SAR_32                                (0x04+(6*0x58))
#define CH7_DAR_0                                 (0x08+(6*0x58))
#define CH7_DAR_32                                (0x0c+(6*0x58))
#define CH7_LLP_0                                 (0x10+(6*0x58))
#define CH7_LLP_32                                (0x14+(6*0x58))
#define CH7_CTL_0                                 (0x18+(6*0x58))
#define CH7_CTL_32                                (0x1c+(6*0x58))
#define CH7_SSTAT_0                               (0x20+(6*0x58))
#define CH7_SSTAT_32                              (0x24+(6*0x58))
#define CH7_DSTAT_0                               (0x28+(6*0x58))
#define CH7_DSTAT_32                              (0x2c+(6*0x58))
#define CH7_SSTATAR_0                             (0x30+(6*0x58))
#define CH7_SSTATAR_32                            (0x34+(6*0x58))
#define CH7_DSTATAR_0                             (0x38+(6*0x58))
#define CH7_DSTATAR_32                            (0x3c+(6*0x58))
#define CH7_CFG_0                                 (0x40+(6*0x58))
#define CH7_CFG_32                                (0x44+(6*0x58))
#define CH7_SGR_0                                 (0x48+(6*0x58))
#define CH7_SGR_32                                (0x4c+(6*0x58))
#define CH7_DSR_0                                 (0x50+(6*0x58))
#define CH7_DSR_32                                (0x54+(6*0x58))

//channel 8 register
#define CH8_SAR_0                                 (0x00+(7*0x58))
#define CH8_SAR_32                                (0x04+(7*0x58))
#define CH8_DAR_0                                 (0x08+(7*0x58))
#define CH8_DAR_32                                (0x0c+(7*0x58))
#define CH8_LLP_0                                 (0x10+(7*0x58))
#define CH8_LLP_32                                (0x14+(7*0x58))
#define CH8_CTL_0                                 (0x18+(7*0x58))
#define CH8_CTL_32                                (0x1c+(7*0x58))
#define CH8_SSTAT_0                               (0x20+(7*0x58))
#define CH8_SSTAT_32                              (0x24+(7*0x58))
#define CH8_DSTAT_0                               (0x28+(7*0x58))
#define CH8_DSTAT_32                              (0x2c+(7*0x58))
#define CH8_SSTATAR_0                             (0x30+(7*0x58))
#define CH8_SSTATAR_32                            (0x34+(7*0x58))
#define CH8_DSTATAR_0                             (0x38+(7*0x58))
#define CH8_DSTATAR_32                            (0x3c+(7*0x58))
#define CH8_CFG_0                                 (0x40+(7*0x58))
#define CH8_CFG_32                                (0x44+(7*0x58))
#define CH8_SGR_0                                 (0x48+(7*0x58))
#define CH8_SGR_32                                (0x4c+(7*0x58))
#define CH8_DSR_0                                 (0x50+(7*0x58))
#define CH8_DSR_32                                (0x54+(7*0x58))

//channel 9 register


//channel 10 register

//Macro defined value
#define AXI_MASTER_0                                    0x0
#define AXI_MASTER_1                                    0x1
#define SRC_ADDR_INCREMENT                              0x0
#define SRC_ADDR_NOCHANGE                               0x1
#define DST_ADDR_INCREMENT                              0x0
#define DST_ADDR_NOCHANGE                               0x1

#define SRC_TRANSFER_WIDTH_8                            0x0
#define SRC_TRANSFER_WIDTH_16                           0x1
#define SRC_TRANSFER_WIDTH_32                           0x2
#define SRC_TRANSFER_WIDTH_64                           0x3
#define SRC_TRANSFER_WIDTH_128                          0x4
#define SRC_TRANSFER_WIDTH_256                          0x5
#define SRC_TRANSFER_WIDTH_512                          0x6
#define DST_TRANSFER_WIDTH_8                            0x0
#define DST_TRANSFER_WIDTH_16                           0x1
#define DST_TRANSFER_WIDTH_32                           0x2
#define DST_TRANSFER_WIDTH_64                           0x3
#define DST_TRANSFER_WIDTH_128                          0x4
#define DST_TRANSFER_WIDTH_256                          0x5
#define DST_TRANSFER_WIDTH_512                          0x6

#define SRC_MSIZE_1                                     0x0
#define SRC_MSIZE_4                                     0x1
#define SRC_MSIZE_8                                     0x2
#define SRC_MSIZE_16                                    0x3
#define SRC_MSIZE_32                                    0x4
#define SRC_MSIZE_64                                    0x5
#define SRC_MSIZE_128                                   0x6
#define SRC_MSIZE_256                                   0x7
#define SRC_MSIZE_512                                   0x8
#define SRC_MSIZE_1024                                  0x9
#define DST_MSIZE_1                                     0x0
#define DST_MSIZE_4                                     0x1
#define DST_MSIZE_8                                     0x2
#define DST_MSIZE_16                                    0x3
#define DST_MSIZE_32                                    0x4
#define DST_MSIZE_64                                    0x5
#define DST_MSIZE_128                                   0x6
#define DST_MSIZE_256                                   0x7
#define DST_MSIZE_512                                   0x8
#define DST_MSIZE_1024                                  0x9

#define NONPOSTED_LASTWRITE_EN                          0x1
#define NONPOSTED_LASTWRITE_DISABLE                     0x0

#define ARLEN_EN                                        0x1
#define ARLEN_DISABLE                                   0x0
#define AWLEN_EN                                        0x1
#define AWLEN_DISABLE                                   0x0
#define SRC_STATUS_EN                                   0x1
#define SRC_STATUS_DISABLE                              0x0
#define DST_STATUS_EN                                   0x1
#define DST_STATUS_DISABLE                              0x0

#define INTEN_COMPLETOFBLKTRANS_SHADORLLI               0x1
#define INTDISABLE_COMPLETOFBLKTRANS_SHADORLLI          0x0
#define NOTLAST_SHADORLLI                               0x0
#define LAST_SHADORLLI                                  0x1

#define SHADORLLI_VALID                                 0x1
#define SHADORLLI_INVALID                               0x0

#define SRC_CONTIGUOUS                                  0x0
#define SRC_RELOAD                                      0x1
#define SRC_SHADOW_REGISTER                             0x2
#define SRC_LINKED_LIST                                 0x3
#define DST_CONTIGUOUS                                  0x0
#define DST_RELOAD                                      0x1
#define DST_SHADOW_REGISTER                             0x2
#define DST_LINKED_LIST                                 0x3

#define MEM_TO_MEM_DMAC                                 0x0
#define MEM_TO_PER_DMAC                                 0x1
#define PER_TO_MEM_DMAC                                 0x2
#define PER_TO_PER_DMAC                                 0x3
#define PER_TO_MEM_SRC                                  0x4
#define PER_TO_PER_SRC                                  0x5
#define MEM_TO_PER_DST                                  0x6
#define PER_TO_PER_DST                                  0x7

#define SRC_HARDWARE_HS                                 0x0
#define DST_HARDWARE_HS                                 0x0
#define SRC_SOFTWARE_HS                                 0x1
#define DST_SOFTWARE_HS                                 0x1
#define SRC_HWHS_HIGHPOL                                0x0
#define SRC_HWHS_LOWPOL                                 0x1
#define DST_HWHS_HIGHPOL                                0x0
#define DST_HWHS_LOWPOL                                 0x1

#define CHANNEL_PRIORITY0                               0x0
#define CHANNEL_PRIORITY1                               0x1
#define CHANNEL_PRIORITY2                               0x2
#define CHANNEL_PRIORITY3                               0x3
#define CHANNEL_PRIORITY4                               0x4
#define CHANNEL_PRIORITY5                               0x5
#define CHANNEL_PRIORITY6                               0x6
#define CHANNEL_PRIORITY7                               0x7
#define CHANNEL_PRIORITY8                               0x8
#define CHANNEL_PRIORITY9                               0x9

#define CHANNEL_LOCK_EN                                 0x1
#define CHANNEL_LOCK_DISABLE                            0x0
#define CHANNEL_LOCK_DMATRANSFER                        0x0
#define CHANNEL_LOCK_BLKTRANSFER                        0x1

#endif
