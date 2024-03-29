/*
 * TIM5.c
 *
 *  Created on: 15.03.2024
 *      Author: patri
 */

#include "main.h"

void basic_timer_setup(TIM_TypeDef *TMR);

uint64_t tim1_overflows;
uint64_t tim1_cc4_previous;
uint64_t tim1_cc4_current;


//TIM5: capture synchronized counter input signal
//adapted from AN4776
//32bit counter, running at 100MHz
void TIM5_init(void){
#warning GPIOA_CNT_IN pin mode alternate wasn't set in board.h! try again with board.h
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

#warning should probably set to falling edge
  //(TIM5->CCER |= TIM_CCER_CC1P; //Circuit is sensitive to TIxFP1 falling edge (capture..)
  //CC1P = 0 -> //Circuit is sensitive to TIxFP1 rising edge (capture..
  TIM5->CCER |= TIM_CCER_CC1E; //CC1 enabled
  TIM5->CR1 = 0;//upcounter, continuous
  TIM5->CR1 |= TIM_CR1_CEN; //enable
  TIM5->SR = ~TIM_SR_CC1IF; //Clear event flag
}

//TIM1 capture timepulse input (GPIOA_TIM1_CH4_IN)
//16bit -> use update interrupt to count overflows
//continuous up-counter. overflow -> update event -> update interrupt
void TIM1_init(void){
//#warning GPIOA_CNT_IN pin mode alternate wasn't set in board.h! try again with board.h
//  palSetPadMode(GPIOA, GPIOA_CNT_IN, PAL_MODE_ALTERNATE(2) | PAL_MODE_INPUT); //setting alternate function in board.h didn't work
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM1EN); //enable peripheral clock (should be handled by mcuconf in chibi hal system?)
  SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM1RST); //assert reset
  CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_TIM1RST); //deassert reset -> registers should be at power up defaults

  //TIM1->CR2 = 0; //defaults
  //TIM1->SMCR = 0; // Reset the SMCR register
  TIM1->DIER = TIM_DIER_UIE; //Update interrupt enable
  TIM1->ARR = 0xFFFF; //auto reload (period) set to max (16bit)
  //TIM1->PSC = 0; //prescaler 1
  TIM1->EGR = TIM_EGR_UG; //update (load ARR, prescaler)
  //TIM1->CCER = 0; //all CC channels off
  //TIM1->CCMR1 = 0;
  TIM1->CCMR2 |= TIM_CCMR2_CC4S_0; //CC4 channel is configured as input, IC4 is mapped on TI4
                                   //CC1S bits are writable only when the channel is OFF (CC1E = 0 in TIMx_CCER).

  //(TIM5->CCER |= TIM_CCER_CC1P; //Circuit is sensitive to TIxFP1 falling edge (capture..)
  //CCER_CC1P = 0 -> //Circuit is sensitive to TIxFP1 rising edge (capture..
  TIM1->CCER |= TIM_CCER_CC4E; //CC4 enabled
  //TIM1->CR1 = 0;//upcounter, continuous
  TIM1->CR1 = TIM_CR1_CEN; //enable
  TIM1->SR = ~TIM_SR_CC4IF; //Clear event flag

  tim1_overflows = 0;
  tim1_cc4_previous = 0;
  tim1_cc4_current = 0;

  NVIC_SetPriority(TIM1_UP_IRQn, 7);
  NVIC_EnableIRQ(TIM1_UP_IRQn);

}




//interrupt vector names defined in os/hal/ports/STM32/STM32F4xx/stm32_isr.h
//priorities?
//use update handler and also check capture flag
CH_IRQ_HANDLER(STM32_TIM1_UP_TIM10_HANDLER)
{
  CH_IRQ_PROLOGUE();

  uint32_t sr = TIM1->SR;
  TIM1->SR = 0; //clear all

  if(sr & TIM_SR_CC4IF){ //capture event
    tim1_cc4_previous = tim1_cc4_current;
    tim1_cc4_current = TIM1->CCR4 + (tim1_overflows<<16);
  }

  tim1_overflows++;
  CH_IRQ_EPILOGUE();
}
