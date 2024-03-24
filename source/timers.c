/*
 * TIM5.c
 *
 *  Created on: 15.03.2024
 *      Author: patri
 */

#include "main.h"

void basic_timer_setup(TIM_TypeDef *TMR);

//adapted from AN4776
//32bit counter, running at 100MHz
void TIM5_init(void){
  palSetPadMode(GPIOA, GPIOA_CNT_IN, PAL_MODE_ALTERNATE(2) | PAL_MODE_INPUT); //setting alternate function in board.h didn't work
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM5EN); //enable peripheral clock (should be handled by mcuconf in chibi hal system)

  TIM5->CR2 = 0; //defaults

  TIM5->SMCR = 0; // Reset the SMCR register

  TIM5->ARR = 0xFFFFFFFF; //auto reload (period) set to max

  TIM5->PSC = 0; //prescaler 1

  TIM5->EGR = TIM_EGR_UG; //update (load ARR, prescaler)

  TIM5->CCER = 0; //all CC channels off

  TIM5->CCMR1 = 0;
  TIM5->CCMR1 |= TIM_CCMR1_CC1S_0; //CC1 channel is configured as input, IC1 is mapped on TI1
                                   //CC1S bits are writable only when the channel is OFF (CC1E = 0 in TIMx_CCER).


  //(TIM5->CCER |= TIM_CCER_CC1P; //Circuit is sensitive to TIxFP1 falling edge (capture..)
  //CC1P = 0 -> //Circuit is sensitive to TIxFP1 rising edge (capture..
  TIM5->CCER |= TIM_CCER_CC1E; //CC1 enabled

  TIM5->CR1 = 0;//upcounter, continuous
  TIM5->CR1 |= TIM_CR1_CEN; //enable

  TIM5->SR = ~TIM_SR_CC1IF; //Clear event flag


}


uint32_t TIM5_get_capture_reg(void){
  return TIM5->CCR1;
}

uint32_t TIM5_get_cnt_reg(void){
  return TIM5->CNT;
}


//copied from https://electronics.stackexchange.com/questions/610435/a-question-about-stm32-global-timers
//todo edit, use nice driver structure
void basic_timer_setup(TIM_TypeDef *TMR) {



    TMR->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS; //ARR is buffered | only overflow/underflow generates update event.
    TMR->PSC = (108000U / 2U) - 1U; //APB1 is 54MHz, timer is 2x APB1 Freq, so now the timer is at 2kHz; 16-bit value!!! 65535 max!
    TMR->ARR = 6000U; //6000 ticks at 2kHz is 3s
    TMR->CNT = 0U; //start value 0
    TMR->DIER |= TIM_DIER_UIE; //update event interrupt enable
    TMR->CR1 |= TIM_CR1_OPM; //one pulse mode

}
