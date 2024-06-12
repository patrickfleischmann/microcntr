/*
 * utils.c
 *
 *  Created on: 12.09.2023
 *      Author: patri
 */


#include "utils.h"
#include "main.h"


void piezo_toggle(void){
  palTogglePad(GPIOC, GPIOC_PIEZO_A);
  palTogglePad(GPIOC, GPIOC_PIEZO_B);
}


//https://excamera.com/sphinx/article-xorshift.html
uint32_t rand32(void)
{
  static uint32_t rseed = 2804628253;  // 100% random seed value
  rseed ^= rseed << 13;
  rseed ^= rseed >> 17;
  rseed ^= rseed << 5;
  return rseed;
}



















