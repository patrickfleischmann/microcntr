/*
 * thd_cntr.c
 *
 *  Created on: 04.03.2024
 *      Author: patri
 */

#include "main.h"

extern uint64_t tim1_overflows;
extern uint64_t tim1_cc4_previous;
extern uint64_t tim1_cc4_current;

void cntr_cal_sel_TIMEPULSE_HSI(void){
  palClearPad(GPIOB, GPIOB_CAL_SOUR_SEL);
}

uint32_t cntr_count_CAL_100M(void){
  return TIM5->CCR1;
}

void calModeHSI(void){ //enable and select HSI output
  myprintf("calModeHSI\n");
  palSetPad(GPIOA, GPIOA_CAL_EN);
  palClearPad(GPIOB, GPIOB_CAL_SOUR_SEL);

//#warning should be managed by GPS thread
  palClearPad(GPIOC, GPIOC_GPS_RESETn); //ensure timepulse output of GNSS module is high-z
  palSetPadMode(GPIOA, GPIOA_MCO_1, PAL_MODE_ALTERNATE(0) | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_OTYPE_PUSHPULL);
  //to use timepulse: palSetPadMode(GPIOA, GPIOA_MCO_1, PAL_MODE_INPUT); //(input without pulldown)

  //defaults configuration for MCO_1 in RCC->CFGR: no division, HSI selected
  //actually configured in mcuconf.h
  //RCC->CFGR |= RCC_CFGR_MCO1EN;//enable output
  SET_BIT(RCC->CFGR, RCC_CFGR_MCO1EN); //enable output

  //enable ref int 100M to view pulse signal at interpolator
//todo commented to have more duty cycle for debugging
  palSetPad(GPIOB, GPIOB_REF_INT_EN);
  palClearPad(GPIOB, GPIOB_REF_INT_SEL);
}

void calModeIntRef100M(void){ //enable and select int 100M ref
  myprintf("calModeIntRef100M\n");
  palSetPad(GPIOB, GPIOB_REF_INT_EN);
  palClearPad(GPIOB, GPIOB_REF_INT_SEL);
  palSetPad(GPIOA, GPIOA_CAL_EN);
  //palClearPad(GPIOA, GPIOA_CAL_EN); //input comp seems to toggle with exactly 100M at this setting
  palSetPad(GPIOB, GPIOB_CAL_SOUR_SEL);
}

void calModeOff(void){ //enable and select int 100M ref
  myprintf("calModeOff\n");
  palSetPad(GPIOA, GPIOA_CAL_EN);
  palClearPad(GPIOB, GPIOB_CAL_SOUR_SEL);

#warning synchronize gnss configuration
  palClearPad(GPIOC, GPIOC_GPS_RESETn); //ensure timepulse output of GNSS module is high-z

  //defaults configuration for MCO_1 in RCC->CFGR: no division, HSI selected
  //actually configured in mcuconf.h
  CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO1EN); //disable output

  palSetPadMode(GPIOA, GPIOA_MCO_1, PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(GPIOA, GPIOA_MCO_1);
}

void calModeGNSSEnabled(void){ //enable and select int 100M ref
  myprintf("calModeGnssEnabled\n");
  palSetPad(GPIOA, GPIOA_CAL_EN);
  palClearPad(GPIOB, GPIOB_CAL_SOUR_SEL);

  palSetPadMode(GPIOA, GPIOA_MCO_1, PAL_MODE_INPUT);
#warning should be managed by GPS thread
  palSetPad(GPIOC, GPIOC_GPS_RESETn); //ensure MCO_1 is high-z before this
}



void ThdCntrFunc(void) {
  myprintf("ThdCntr\n");

  TIM5_init();
  tim1_overflows = 0;
  TIM1_init();

  myprintf("tim1_overflows: %u\n", (uint32_t)tim1_overflows);

  uint64_t test = 0;
  myprintf("a: %u\n", test);
  test++;
  myprintf("b: %u, c:%u\n", (uint32_t)test, (uint32_t)(test>>32));
  test++;
  myprintf("b: %lu, c:%u\n", (uint32_t)test);
  test++;
  myprintf("b: %lu, c:%u\n", test);


//  //selftest muxout
//  myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));
//
//  calModeIntRef100M();
//  chThdSleepMilliseconds(100);
//
//  myprintf("testmode muxout low\n");
//  adf_config_testmode_muxout_low();
//  chThdSleepMilliseconds(1);
//
//  //disable and select ext to freeze synchronizer with 0 at output
//  palClearPad(GPIOB, GPIOB_REF_INT_EN);
//  palSetPad(GPIOB, GPIOB_REF_INT_SEL);
//  chThdSleepMilliseconds(100);
//
//  myprintf("testmode muxout high\n");
//  adf_config_testmode_muxout_high();
//  chThdSleepMilliseconds(1);
//  myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));
//
//  myprintf("testmode muxout low\n");
//  adf_config_testmode_muxout_low();
//  chThdSleepMilliseconds(1);
//  myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));

//#warning testmode muxout low scheint eher muxout high-z zu sein

//  myprintf("testmode muxout high\n");
//  adf_config(1, 1, 1); //testmode muxout high
//  chThdSleepMilliseconds(1);
//  myprintf("CNT_in = %d\n", palReadPad(GPIOA, GPIOA_CNT_IN));

  //calModeIntRef100M();
  calModeGNSSEnabled();
  //calModeOff();
  //calModeHSI();
  //adf_config_div_n(1000);
  //adf_config_div_r(50); //seems to work
  adf_config_div_n(1000); //divider not working correctly

  while(true){

/*
    uint32_t a,b;
    while(!(TIM5->SR & TIM_SR_CC1IF));
    a = TIM5->CCR1; //flag CC1IF cleared by this read
    while(!(TIM5->SR & TIM_SR_CC1IF));
    b = TIM5->CCR1;
    myprintf("a: %10u, b: %10u, b-a: %10u\n", a, b, b-a);
*/


   // TIM5->SR = ~TIM_SR_CC1IF;
   // TIM5->EGR |= TIM_EGR_CC1G; //generate capture event by software, this seems to work
    //myprintf("ccr1: %u, cnt: %u, cc1F: %u\n", TIM5->CCR1, TIM5->CNT, (TIM5->SR & TIM_SR_CC1IF));
    //myprintf("sr: %u\n", TIM5->SR);

    myprintf("tim1_cc4_previous: %u, tim1_cc4_current: %u\n", (uint32_t)tim1_cc4_previous, (uint32_t)tim1_cc4_current);
    myprintf("period: %u\n", (uint32_t)(tim1_cc4_current - tim1_cc4_previous));



#warning myprintf only supports 32bit integers todo extend to 64bit
    myprintf("tim1_overflows: %u\n", (uint32_t)tim1_overflows);

    chThdSleepMilliseconds(500);
  }
}



