
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
      reg32(0x00200000+core_id*4) = 0x12345630|core_id; //DCCM
    }

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

