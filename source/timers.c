/*
 * TIM5.c
 *
 *  Created on: 15.03.2024
 *      Author: patri
 */

#include "main.h"

int64_t timepulse_capt_prev;
int64_t timepulse_capt_curr;
int64_t timepulse_period;
int64_t timepulse_period_avg8;
uint32_t tim1_overflows;
uint32_t timepulses;

//TIM5: capture synchronized counter input signal
//Generate TRGO on capture event to trigger adc injected conversion
//adapted from AN4776
//32bit counter, running at 100MHz
void TIM5_init(void){
#warning GPIOA_CNT_IN pin mode alternate wasnt set in board.h! try again with board.h
  palSetPadMode(GPIOA, GPIOA_CNT_IN, PAL_MODE_ALTERNATE(2) | PAL_MODE_INPUT); //setting alternate function in board.h didn't work
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM5EN); //enable peripheral clock (should be handled by mcuconf in chibi hal system)

  TIM5->CR2 = TIM_CR2_MMS_1 | TIM_CR2_MMS_0; //Compare Pulse - The trigger output send a positive pulse when the CC1IF flag is to be
                                              //set (even if it was already high), as soon as a capture or a compare match occurred
  TIM5->SMCR = 0; // Reset the SMCR register
  TIM5->ARR = 0xFFFFFFFF; //auto reload (period) set to max
  TIM5->PSC = 0; //prescaler 1
  TIM5->EGR = TIM_EGR_UG; //update (load ARR, prescaler)
  TIM5->CCER = 0; //all CC channels off
  TIM5->CCMR1 = 0;
  TIM5->CCMR1 |= TIM_CCMR1_CC1S_0; //CC1 channel is configured as input, IC1 is mapped on TI1
                                   //CC1S bits are writable only when the channel is OFF (CC1E = 0 in TIMx_CCER).

#warning should probably set to falling edge
  //(TIM5->CCER |= TIM_CCER_CC1P; //Circuit is sensitive to TIxFP1 falling edge (capture..)
  //CC1P = 0 -> //Circuit is sensitive to TIxFP1 rising edge (capture..
  TIM5->CCER |= TIM_CCER_CC1E; //CC1 enabled
  TIM5->CR1 = 0;//upcounter, continuous
  TIM5->CR1 |= TIM_CR1_CEN; //enable
  TIM5->SR = ~TIM_SR_CC1IF; //Clear event flag
}

//TIM1 capture timepulse input on rising edge(GPIOA_TIM1_CH4_IN)
//16bit -> use update interrupt to count overflows
//continuous up-counter. overflow -> update event -> update interrupt
//input capture
void TIM1_init(void){
//#warning GPIOA_CNT_IN pin mode alternate wasn't set in board.h! try again with board.h
//  palSetPadMode(GPIOA, GPIOA_CNT_IN, PAL_MODE_ALTERNATE(2) | PAL_MODE_INPUT); //setting alternate function in board.h didn't work
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN); //enable peripheral clock (should be handled by mcuconf in chibi hal system?)
  SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM1RST); //assert reset
  CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM1RST); //deassert reset -> registers should be at power up defaults

  TIM1->DIER = TIM_DIER_UIE; //Update interrupt enable
  TIM1->ARR = 0xFFFF; //auto reload (period) set to max (16bit)
  TIM1->EGR = TIM_EGR_UG; //update (load ARR, prescaler)
  TIM1->CCMR2 |= TIM_CCMR2_CC4S_0; //CC4 channel is configured as input, IC4 is mapped on TI4
                                   //CCxS bits are writable only when the channel is OFF (CC1E = 0 in TIMx_CCER).
  TIM1->CCER |= TIM_CCER_CC4E; //CC4 enabled
  TIM1->CR1 = TIM_CR1_CEN; //enable
  TIM1->SR = ~TIM_SR_CC4IF; //Clear event flag

  tim1_overflows = 0;
  timepulses = 0;

  NVIC_SetPriority(TIM1_UP_IRQn, 7);
  NVIC_EnableIRQ(TIM1_UP_IRQn);
}

//interrupt vector names defined in os/hal/ports/STM32/STM32F4xx/stm32_isr.h
//priorities?
//use update handler and also check capture flag
CH_FAST_IRQ_HANDLER(STM32_TIM1_UP_TIM10_HANDLER){ //no chibios calls allowed in fast isr
  static int64_t avg8;

  uint32_t sr = TIM1->SR;
  TIM1->SR = 0; //clear all
  uint16_t ccr = TIM1->CCR4;
  if(sr & TIM_SR_CC4IF){ //capture event
    timepulses++;
    timepulse_capt_prev = timepulse_capt_curr;
    timepulse_capt_curr = ((uint64_t)ccr << 16) + ((uint64_t)tim1_overflows << 32);
    timepulse_period = timepulse_capt_curr - timepulse_capt_prev;
    avg8 += timepulse_period;
    if((timepulses % 8) == 0){
      timepulse_period_avg8 = avg8 / 8;
      avg8 = 0;
    }
  }
  tim1_overflows++;
}

uint32_t timer_getTimepulses(void){
  return timepulses;
}

uint64_t timer_getTimepulsePeriod(void){
  uint32_t timepulses_old = timepulses;
  uint64_t temp = timepulse_capt_curr - timepulse_capt_prev;
  if(timepulses_old == timepulses){ //no update happened during calc -> result ok
    timepulse_period = temp;
  }
  return timepulse_period;
}



//TIM9 (16bit, 100MHz) one pulse mode
//generate discharge pulse for interpolator
//input: PC5, TIM9_CH2, GPIOC_CNT_IN
//output: PC4, TIM9_CH1,GPIOC_DISCHARGE
void TIM9_init(uint16_t delay, uint16_t width){
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM9EN); //enable peripheral clock
  SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM9RST); //assert reset
  CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM9RST); //deassert reset -> registers should be at power up defaults

  //trigger input
  TIM9->CCMR1 = TIM_CCMR1_CC2S_0 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0; //channel 2 is input, PWM mode 2: positive pulse after delay
  TIM9->CCER = TIM_CCER_CC2P | TIM_CCER_CC1E; //falling edge, CC1 output enabled
  TIM9->SMCR = TIM_SMCR_TS_2 | TIM_SMCR_TS_1 | TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1; //trigger input = Filtered Timer Input 2 (TI2FP2)
                                                                                //Slave mode = trigger (counter starts on trigger)
  //output
  TIM9->CCR1 = delay; //delay after trigger
  TIM9->ARR = delay + width; //pulse width
  TIM9->CR1 = TIM_CR1_OPM; //stop after one pulse (CEN cleared by hw)
}










