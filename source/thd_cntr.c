/*
 * thd_cntr.c
 *
 *  Created on: 04.03.2024
 *      Author: patri
 */

#include "main.h"

void ThdCntrFunc(void) {
  myprintf("ThdCntr\n");

  //selftest muxout
  myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));

  //enable and select int 100M ref
  palSetPad(GPIOB, GPIOB_REF_INT_EN);
  palClearPad(GPIOB, GPIOB_REF_INT_SEL);
  chThdSleepMilliseconds(100);

  myprintf("testmode muxout low\n");
  adf_config(1, 1, 2); //testmode muxout low
  chThdSleepMilliseconds(1);

  //disable and select ext to freeze synchronizer with 0 at output
  palClearPad(GPIOB, GPIOB_REF_INT_EN);
  palSetPad(GPIOB, GPIOB_REF_INT_SEL);
  chThdSleepMilliseconds(100);

  myprintf("testmode muxout high\n");
  adf_config(1, 1, 1); //testmode muxout high
  chThdSleepMilliseconds(1);
  myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));

  myprintf("testmode muxout low\n");
  adf_config(1, 1, 2); //testmode muxout low
  chThdSleepMilliseconds(1);
  myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));

#warning testmode muxout low scheint eher muxout high-z zu sein

//  myprintf("testmode muxout high\n");
//  adf_config(1, 1, 1); //testmode muxout high
//  chThdSleepMilliseconds(1);
//  myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));

  while(true){
    chThdSleepMilliseconds(1000);
    myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));
  }
}
