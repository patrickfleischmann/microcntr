/*
 * buttons.c
 *
 *  Created on: 17.06.2024
 *      Author: patri
 */

#include "main.h"

/*
      if(!palReadPad(GPIOB, GPIOB_BUTTON_A)){
        mui_NextField(mui);
      } else if(!palReadPad(GPIOB, GPIOB_BUTTON_B)){
        mui_PrevField(mui);
      } else if(!palReadPad(GPIOB, GPIOB_BUTTON_C)){
        mui_SendSelect(mui);
      }

#define GPIOB_BUTTON_A                 6U
#define GPIOB_BUTTON_B                 7U
#define GPIOB_BUTTON_C                 8U
*/

void buttons_init(void){
  SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN); //enable peripheral clock
  SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SYSCFGRST); //assert reset
  CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_SYSCFGRST); //deassert reset -> registers should be at power up defaults

  SYSCFG->EXTICR[1] |= (1 << SYSCFG_EXTICR2_EXTI6_Pos); //select PB6
  SYSCFG->EXTICR[1] |= (1 << SYSCFG_EXTICR2_EXTI7_Pos); //select PB7
  SYSCFG->EXTICR[2] |= (1 << SYSCFG_EXTICR3_EXTI8_Pos); //select PB8

  EXTI->IMR  =  EXTI_IMR_MR6 | EXTI_IMR_MR7 | EXTI_IMR_MR8; //mask reg
  EXTI->RTSR = 0; //disable all rising edge
  EXTI->FTSR = EXTI_FTSR_TR6 | EXTI_FTSR_TR7 | EXTI_FTSR_TR8; //enable falling edge
  EXTI->PR |= (EXTI_PR_PR6 | EXTI_PR_PR7 | EXTI_PR_PR8); //clear pending bit by writing 1
}

int button_A_pressed(void){
  if(EXTI->PR & EXTI_PR_PR6){
    EXTI->PR |= EXTI_PR_PR6; //clear
    return 1;
  }
  return 0;
}

int button_B_pressed(void){
  if(EXTI->PR & EXTI_PR_PR7){
    EXTI->PR |= EXTI_PR_PR7; //clear
    return 1;
  }
  return 0;
}

int button_C_pressed(void){
  if(EXTI->PR & EXTI_PR_PR8){
    EXTI->PR |= EXTI_PR_PR8; //clear
    return 1;
  }
  return 0;
}
