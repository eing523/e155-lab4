// timer 7
// Emily Ing
// eing@g.hmc.edu
// 9/27/26

#include "STM32L432KC_TIM7.h"
#include "STM32L432KC_RCC.h"

void duration(void) {
  // turn on timer 7 p. 222
  RCC->APB1ENR1 |= (1 << 5); 

  // set prescaler
  TIM7->PSC = 3999; // turning 4 MHz into 1 kHz (dividing by 4000-1)

  // enable counter feature
  TIM7->CR1 |= (1<<0);
  // enable arr enable
  TIM7->CR1 |= (1<<7);

  // update interrupt flag - status register
  TIM7->SR &= ~(1<<0);

  // EGR register - update generation for registers
  TIM7->EGR |= (1<<0);

}

void runDuration(int duration){
  // set ARR for note duration. -1 to account for the counting start at 0. we use duration here because the duration we are inputting is already the max val. 
  TIM7->ARR = duration - 1;

  // update generation to reinitialize counter + update registers
  TIM7->EGR |= (1<<0);

  // clear flag caused by update generation from previous line
  TIM7->SR &= ~(1<<0);

  // restart timer and enable counter
  TIM7->CR1 |= (1 << 0);

}

