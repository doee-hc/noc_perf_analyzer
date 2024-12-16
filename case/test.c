
/*
 *-----------------------------------------------------------------------------
 *-----------------------------------------------------------------------------
 */
#include "common.h"
#include "chip_define.h"

#include "crgtop.h"
#include "csr_reg.h"
#include "ext_int.h"
void  __attribute__ ((interrupt)) internal_exception_handler(void){
  uint32_t mcause, ex_code;
  CSR_GETEX(CSR_MCAUSE, mcause);
  ex_code = mcause & 0x00000FFF;
  if (BIT(31) & mcause){
    printf("catch int NO. %d\n",  ex_code);
  }
  else {
    printf("catch exception %d\n",  ex_code);
  }
  //  CSR_SETEX(CSR_MIP, 0); //MIP will clean by hardware
}
#define DCCM_BASE_ADDR  0x00200000
#define CORE0_DCCM      (CORE_BASE + CORE_SIZE*0 + DCCM_BASE_ADDR)
#define CORE1_DCCM      (CORE_BASE + CORE_SIZE*1 + DCCM_BASE_ADDR)
#define CORE2_DCCM      (CORE_BASE + CORE_SIZE*2 + DCCM_BASE_ADDR)
#define CORE3_DCCM      (CORE_BASE + CORE_SIZE*3 + DCCM_BASE_ADDR)
#define CORE4_DCCM      (CORE_BASE + CORE_SIZE*4 + DCCM_BASE_ADDR)
#define CORE5_DCCM      (CORE_BASE + CORE_SIZE*5 + DCCM_BASE_ADDR)
#define CORE6_DCCM      (CORE_BASE + CORE_SIZE*6 + DCCM_BASE_ADDR)
#define CORE7_DCCM      (CORE_BASE + CORE_SIZE*7 + DCCM_BASE_ADDR)
#define CORE8_DCCM      (CORE_BASE + CORE_SIZE*8 + DCCM_BASE_ADDR)
#define CORE9_DCCM      (CORE_BASE + CORE_SIZE*9 + DCCM_BASE_ADDR)
#define CORE10_DCCM     (CORE_BASE + CORE_SIZE*10 + DCCM_BASE_ADDR)
#define CORE11_DCCM     (CORE_BASE + CORE_SIZE*11 + DCCM_BASE_ADDR)
#define CORE12_DCCM     (CORE_BASE + CORE_SIZE*12 + DCCM_BASE_ADDR)
#define CORE13_DCCM     (CORE_BASE + CORE_SIZE*13 + DCCM_BASE_ADDR)
#define CORE14_DCCM     (CORE_BASE + CORE_SIZE*14 + DCCM_BASE_ADDR)
#define CORE15_DCCM     (CORE_BASE + CORE_SIZE*15 + DCCM_BASE_ADDR)

int main (void)
{
  int test_value = 0x55;
  unsigned int error = 0;
  unsigned int test_result;
  unsigned int test_addr;
  unsigned int temp;
  unsigned int core_id;
  unsigned int my_id;
  unsigned int trans_cnt;
  TEST_START(); // prompt for test start.

////assert all core reset and access dccm
  my_id = reg32(COREN_GRF_BASE+0x4000);
  my_id = ( my_id & 0xF0 ) >> 4;
//reg32(CRU_TOP_BASE+CRU_SOFTRST_CON03) = 0xFFFFFFFE; //assert all core reset except core0
 
  if (my_id == 0 ) {
    // init data for reset core
    for(core_id = 0; core_id < 16; core_id ++ ) {
      reg32( DCCM_BASE_ADDR + core_id*4 ) = 0x12345630|core_id; //DCCM
    }

    reg64( AXI_DMA_BASE + DMAC_CFGREG) = DMAC_CFGREG_DMAC_EN | DMAC_CFGREG_INT_EN;  // Enable AXI DMA

    reg64( AXI_DMA_BASE + CHx_SAR(1) ) = CORE0_DCCM; 
    reg64( AXI_DMA_BASE + CHx_DAR(1) ) = CORE1_DCCM; 
    reg64( AXI_DMA_BASE + CHx_CTL(1) ) =    CHx_CTL_SMS_M1 | 
                                            CHx_CTL_DMS_M1 |
                                            CHx_CTL_SINC |
                                            CHx_CTL_DINC |
                                            CHx_CTL_SRC_TR_WIDTH_512 |
                                            CHx_CTL_DST_TR_WIDTH_512 |
                                            CHx_CTL_SRC_MSIZE_256 |
                                            CHx_CTL_DST_MSIZE_256; 
                                            
                                            
    reg64( AXI_DMA_BASE + CHx_BLOCK_TS(1) ) = 256;

    reg64( AXI_DMA_BASE + DMAC_CHENREG) = DMAC_CHENREG_CH1_EN;  // Enable AXI DMA Channel 1

    // write core1
    for(trans_cnt = 0; trans_cnt < 256; trans_cnt += 4){
        reg32(CORE_BASE+CORE_SIZE+ 0x00200000 + trans_cnt) = trans_cnt; //DCCM
    }

    // read core1
    for(trans_cnt = 0; trans_cnt < 256; trans_cnt += 4){
        temp = reg32(CORE_BASE+CORE_SIZE+ 0x00200000 + trans_cnt); //DCCM
        reg32(RAM_BASE+(1+trans_cnt)*4) = temp;
        printf("->get dccm data %x\n",temp);
        if (temp != trans_cnt){
            printf("Fail");
            error+=1;
        }
    }


    //for(core_id = 1; core_id < 16; core_id ++ ) {
    //  temp = reg32(CORE_BASE+core_id*CORE_SIZE+ 0x00003c00) ;
    //  reg32(RAM_BASE+core_id * 4) = temp;
    //  printf("->get iccm data %x\n",temp);
    //}

    //for(core_id = 1; core_id < 16; core_id ++ ) {
    //    for(trans_cnt = 0; trans_cnt < 256; trans_cnt+=4){
    //        temp = reg32(CORE_BASE+core_id*CORE_SIZE+ 0x00200000 + trans_cnt) ;
    //        reg32(RAM_BASE+core_id * 4 * 256) = temp;
    //    }
    //  temp = reg32(CORE_BASE+core_id*CORE_SIZE+ 0x00200000) ;
    //  printf("->get dccm data %x\n",temp);
    //}

    // checking data
    //for(core_id = 1; core_id < 16; core_id ++ ) {
    //  while(1) {
    //    temp = reg32( 0x00200000 + core_id * 4 );
    //    printf("->checking resp data from core%d(%x)\n",core_id,temp);
    //    if ( temp == 0x89abcdef ) {
    //      break;
    //    }
    //  }
    //}

    // finish other core 
    for(core_id = 1; core_id < 16; core_id ++ ) {
      reg32(CORE_BASE + core_id*CORE_SIZE + PRINT_AHB_BASE+4) = 0xAAA0AAA0; //test pass
      reg32(CORE_BASE + core_id*CORE_SIZE + PRINT_AHB_BASE+8) = 0x85585885; // test end
      reg32(CORE_BASE + core_id*CORE_SIZE + PRINT_AHB_BASE  ) = 0xFF; // test end
    }
  } else {
    // poll ram 
    //while(1) {
    //  temp = reg32(RAM_BASE+my_id * 4) ;
    //  if ( temp == (0x12345620 | my_id) ) {
    //    printf("get data %x\n",temp);
    //    break;
    //  }
    //}
    //reg32(CORE_BASE + 0x00200000 + my_id*4) = 0x89abcdef; //DCCM
    //// write to core0 dccm to finish;
    while(1);
  }


  if (error>0)
    test_result = TEST_FAILD;
  else
    test_result = TEST_OK;

  TEST_END(test_result); // prompt for test end.
  return 0;
}

