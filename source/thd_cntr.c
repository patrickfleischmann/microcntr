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
#warning use uint64_t?, unify units handling

#include "main.h"

extern uint32_t tim9_updates;
extern uint32_t adc_TAC_end_cb_counter;
extern uint32_t adc_TAC_error_cb_counter;

uint32_t div_autoset(void);

static bool cntr_running;
static uint32_t tim5_ccr1, period;
static uint32_t adc_jdr1, adc_jdr2;
static uint32_t adc_isr_count;
static uint32_t div_isr;
static uint32_t div;

//todo ping-pong histogram, weighted average
uint32_t hist_buf[HIST_BUF_LEN];
uint32_t hist_n_samples;
uint32_t hist_max;

//measurement results protected by mutex
static mutex_t mtx_cntr;
static uint64_t period_fs;
static float freq_hz;

#warning todo struct? or even return strings
uint64_t cntr_get_period_fs(void){
  chMtxLock(&mtx_cntr);
  uint64_t tmp = period_fs;
  chMtxUnlock(&mtx_cntr);
  return tmp;
}

float cntr_get_freq_hz(void){
  chMtxLock(&mtx_cntr);
  float tmp = freq_hz;
  chMtxUnlock(&mtx_cntr);
  return tmp;
}

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
  RCC->CR &= ~RCC_CR_HSITRIM; //clear trim (lowest freq, ca. 15.5 MHz)
  //RCC->CR |= 11 << RCC_CR_HSITRIM_Pos; //trim to 16M(0-31, Reset value 16)
  RCC->CR |= RCC_CR_HSITRIM; //highest freq, ca. 17.1 MHz

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

//find optimal divider value
uint32_t div_autoset(){
  uint32_t div = 8190;
  uint32_t step = div/2;
  uint32_t count = 0;
  //binary search (starting high)
  while(step > 0){
    adf_config_div_n(div);
    adc_isr_count = 0;
    chThdSleepMilliseconds(1);
    count = adc_isr_count;
    //myprintf("div_autoset div: %5u, count: %7u\n", div, count);
    if(count < 100){
      div -= step;
    } else {
      div += step;
      if(div > 8190) div = 8190;
    }
    step /= 2;
  }

  adc_isr_count = 0;
  chThdSleepMilliseconds(1);
  count = adc_isr_count;
  myprintf("div_autoset div: %5u, count: %7u\n", div, count);
  return div;
}

//interrupt vector names defined in os/hal/ports/STM32/STM32F4xx/stm32_isr.h
//priorities?
//use update handler and also check capture flag
CH_FAST_IRQ_HANDLER(Vector88) { //ADC, no chibios allowed in fast interrupt
  //  uint32_t sr = ADC1->SR; //todo can overrun be checked?
  ADC1->SR = 0; //clear all
  if(adc_isr_count == 0){
    tim5_ccr1 = TIM5->CCR1;
    adc_jdr1 = ADC1->JDR1;
    adc_jdr2 = ADC1->JDR2;
  } else if(adc_isr_count == div_isr){
    period = TIM5->CCR1 - tim5_ccr1;
  }

  //accumulate histogram
  if(hist_n_samples<HIST_SAMPLES_MAX){
    uint32_t tmp = hist_buf[(ADC1->JDR1) & HIST_IDX_MASK]++;
    if(tmp > hist_max){
      hist_max = tmp;
    }
    hist_n_samples++;
  } else {
    //hist_n_samples = 0;
    //for(uint32_t i=0; i<HIST_BUF_LEN; ++i) hist_buf[i] = 0;
  }

  adc_isr_count++;
}

void cntr_start(void){
  adc_init_TAC(); //triggered by TIM5
  TIM5_init();
  TIM1_init(); //capturing timepulse

  //todo adjust
  TIM9_init(90, 10); //90,10->delay ca. 2us, pulsewidth 100nS

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
  adf_config_div_n(1000); //


  div_isr = 100000;
  div = div_autoset();
  printf("div_autoset: %u\n", div);
  cntr_running = TRUE;
}

void cntr_stop(void){
  cntr_running = FALSE;
}

int cntr_is_running(void){
  return cntr_running;
}

void ThdCntrFunc(void) {
  myprintf("ThdCntr\n");
  chMtxObjectInit(&mtx_cntr);

  while(true){
    if(cntr_running){

      //     uint32_t a,b;
      //    while(!(TIM5->SR & TIM_SR_CC1IF));
      //    a = TIM5->CCR1; //flag CC1IF cleared by this read
      //    while(!(TIM5->SR & TIM_SR_CC1IF));
      //    b = TIM5->CCR1;
      //myprintf("a: %10u, b: %10u, b-a: %10u\n", a, b, b-a);

      // myprintf("%.3f %.3f %.3f\n\r", adc_get_temp_internal(), adc_get_temp_heater(), adc_get_current());

      if(adc_isr_count){

        chMtxLock(&mtx_cntr);
        period_fs = ((uint64_t)period)*10000000ULL/(((uint64_t)div) * ((uint64_t)div_isr));
        freq_hz = 1.0e8*div*div_isr/period;
        chMtxUnlock(&mtx_cntr);


        myprintf("\nperiod: %llu ps, freq: %f Hz\n",period_fs, freq_hz);
        myprintf("ADC1 JDR1: %u, JDR2: %4u\n",adc_jdr1, adc_jdr2);
        /* myprintf("temp: %f\n",lmt85_adcval_to_deg(adc_jdr2));
        a = b;
        b = tim5_ccr1;
        myprintf("a: %10u, b: %10u, b-a: %10u, count: %u\n", a, b, b-a, adc_isr_count);
         */
        adc_isr_count = 0;
      }

      //myprintf("adc_TAC_end_cb_counter: %d, adc_TAC_error_cb_counter: %d\n", adc_TAC_end_cb_counter, adc_TAC_error_cb_counter);

      // TIM5->SR = ~TIM_SR_CC1IF;
      // TIM5->EGR |= TIM_EGR_CC1G; //generate capture event by software, this seems to work
      //myprintf("ccr1: %u, cnt: %u, cc1F: %u\n", TIM5->CCR1, TIM5->CNT, (TIM5->SR & TIM_SR_CC1IF));
      //myprintf("sr: %u\n", TIM5->SR);

      /*
      //timepulse measurement
      int64_t period = timer_getTimepulsePeriod();
      myprintf("2 tim1_cc4_previous: %llu, tim1_cc4_current: %llu\n", timepulse_capt_prev, timepulse_capt_curr);
      myprintf("2 period: 1 s + %e s\n", (float)(period - TIME_1S) * TIME_RES_F);
       */
    }
    chThdSleepMilliseconds(1000);
  }
}





