/*
 * thd_cntr.c
 *
 * Created on: 04.03.2024
 * Author: patrick
 *
 * time units:
 * timer TIM1,TIM5 tick: 10ns
 * shifted by 16 in int64_t. LSB: 0.152587890625 ps MSB: 703687.441777 s
 * max value/overflow: ca. 1407375 s (= 16.3 d)
 *
 * gnss timepulse: 1 pps
 */

#define TIME_1S (100000000LL << 16)
#define TIME_RES ((float)(0.152587890625e-12))

#include "main.h"

int64_t timepulse_capt_prev;
int64_t timepulse_capt_curr;
extern uint32_t tim9_updates;
extern uint32_t adc_TAC_end_cb_counter;
extern uint32_t adc_TAC_error_cb_counter;

uint32_t tim5_ccr1;
uint32_t adc_jdr1;
bool adc_isr_flag;

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

//default state
//GNSS enabled, MCO disabled
#warning todo disconnect timepulse in hw. then keep GNSS running
void calModeOff(void){
  myprintf("calModeOff\n");
  palSetPad(GPIOA, GPIOA_CAL_EN);
  palClearPad(GPIOB, GPIOB_CAL_SOUR_SEL); //HSI

  palClearPad(GPIOC, GPIOC_GPS_RESETn); //ensure timepulse output of GNSS module is high-z

  //defaults configuration for MCO_1 in RCC->CFGR: no division, HSI selected
  //actually configured in mcuconf.h
  CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO1EN); //disable output

  palSetPadMode(GPIOA, GPIOA_MCO_1, PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(GPIOA, GPIOA_MCO_1);
}

#warning only required as long as timepulse is still connected
void calModeGNSSEnabled(void){ //enable and select int 100M ref
  myprintf("calModeGnssEnabled\n");
  palSetPad(GPIOA, GPIOA_CAL_EN);
  palClearPad(GPIOB, GPIOB_CAL_SOUR_SEL); //HSI

  palSetPadMode(GPIOA, GPIOA_MCO_1, PAL_MODE_INPUT);
  palSetPad(GPIOC, GPIOC_GPS_RESETn); //ensure MCO_1 is high-z before this
}



void ThdCntrFunc(void) {
  myprintf("ThdCntr\n");

  adc_init_TAC(); //triggered by TIM5
  TIM5_init();

  timepulse_capt_prev = 0;
  timepulse_capt_curr = 0;
  TIM1_init(); //capturing timepulse

  //todo adjust
  TIM9_init(90, 10); //90,10->delay ca. 2us, pulsewidth 100nS


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

  calModeIntRef100M();
  //calModeGNSSEnabled();
  //calModeOff();
  //calModeHSI();
  //adf_config_div_n(1000);
  //adf_config_div_r(50); //seems to work
  adf_config_div_n(1000); //

  while(true){


      uint32_t a,b;
//    while(!(TIM5->SR & TIM_SR_CC1IF));
//    a = TIM5->CCR1; //flag CC1IF cleared by this read
//    while(!(TIM5->SR & TIM_SR_CC1IF));
//    b = TIM5->CCR1;
    //myprintf("a: %10u, b: %10u, b-a: %10u\n", a, b, b-a);

   // myprintf("%.3f %.3f %.3f\n\r", adc_get_temp_internal(), adc_get_temp_heater(), adc_get_current());



    if(adc_isr_flag){
      myprintf("ADC1 JDR1: %04d\n",adc_jdr1);
      a = b;
      b = tim5_ccr1;
      myprintf("a: %10u, b: %10u, b-a: %10u\n", a, b, b-a);
      adc_isr_flag = 0;
    }


    //myprintf("adc_TAC_end_cb_counter: %d, adc_TAC_error_cb_counter: %d\n", adc_TAC_end_cb_counter, adc_TAC_error_cb_counter);

   // TIM5->SR = ~TIM_SR_CC1IF;
   // TIM5->EGR |= TIM_EGR_CC1G; //generate capture event by software, this seems to work
    //myprintf("ccr1: %u, cnt: %u, cc1F: %u\n", TIM5->CCR1, TIM5->CNT, (TIM5->SR & TIM_SR_CC1IF));
    //myprintf("sr: %u\n", TIM5->SR);

/*
    //timepulse measurement
    int64_t period = timepulse_capt_curr - timepulse_capt_prev;
    myprintf("2 tim1_cc4_previous: %llu, tim1_cc4_current: %llu\n", timepulse_capt_prev, timepulse_capt_curr);
    myprintf("2 period: 1 s + %e s\n", (float)(period - TIME_1S) * TIME_RES);
*/
    chThdSleepMilliseconds(1000);
  }
}

//interrupt vector names defined in os/hal/ports/STM32/STM32F4xx/stm32_isr.h
//priorities?
//use update handler and also check capture flag
CH_FAST_IRQ_HANDLER(Vector88) { //ADC, no chibios allowed in fast interrupt
//  uint32_t sr = ADC1->SR; //todo can overrun be checked?
  ADC1->SR = 0; //clear all
  if(!adc_isr_flag){
    tim5_ccr1 = TIM5->CCR1;
    adc_jdr1 = ADC1->JDR1;
    adc_isr_flag = 1;
  }
}



