/*
 * thd_cntr.c
 *
 *  Created on: 04.03.2024
 *      Author: patri
 */

#include "main.h"

void cntr_cal_sel_TIMEPULSE_HSI(void){
  palClearPad(GPIOB, GPIOB_CAL_SOUR_SEL);
}

void cntr_cal_sel_CAL_100M(void){
  palSetPad(GPIOB, GPIOB_CAL_SOUR_SEL);
}

uint32_t cntr_count_CAL_100M(void){
#warning debug todo
  cntr_cal_sel_CAL_100M();
  adf_config_div_n(8000);
  return TIM5_get_capture_reg();
}


void ThdCntrFunc(void) {
  myprintf("ThdCntr\n");

  TIM5_init();

  //selftest muxout
  myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));

  //enable and select int 100M ref
  palSetPad(GPIOB, GPIOB_REF_INT_EN);
  palClearPad(GPIOB, GPIOB_REF_INT_SEL);
  chThdSleepMilliseconds(100);

  myprintf("testmode muxout low\n");
  adf_config_testmode_muxout_low();
  chThdSleepMilliseconds(1);

  //disable and select ext to freeze synchronizer with 0 at output
  palClearPad(GPIOB, GPIOB_REF_INT_EN);
  palSetPad(GPIOB, GPIOB_REF_INT_SEL);
  chThdSleepMilliseconds(100);

  myprintf("testmode muxout high\n");
  adf_config_testmode_muxout_high();
  chThdSleepMilliseconds(1);
  myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));

  myprintf("testmode muxout low\n");
  adf_config_testmode_muxout_low();
  chThdSleepMilliseconds(1);
  myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));

#warning testmode muxout low scheint eher muxout high-z zu sein

//  myprintf("testmode muxout high\n");
//  adf_config(1, 1, 1); //testmode muxout high
//  chThdSleepMilliseconds(1);
//  myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));

  while(true){

    //myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));

    uint32_t a,b;
    cntr_count_CAL_100M();
    a = TIM5_get_capture_reg();
    chThdSleepMilliseconds(1000);
    b = TIM5_get_capture_reg();

    myprintf("diff: 0x%10u\n", b-a);



    chThdSleepMilliseconds(10);
  }
}



