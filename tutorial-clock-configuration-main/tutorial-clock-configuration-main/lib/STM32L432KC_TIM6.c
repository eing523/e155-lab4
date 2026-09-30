// timer 6 - frequency
// Emily Ing
// eing@g.hmc.edu
// 9/27/26

#include "STM32L432KC_TIM6.h"
#include "STM32L432KC_RCC.h"

void pitch() {
  // turn on timer 6 pg. 222
  RCC->APB1ENR1 |= (1 << 4);

  // set prescaler - 0 means clk input unchanged
  TIM6->PSC = 0;

  // enable counter feature
  TIM6->CR1 |= (1<<0);
  // enable arr enable
  TIM6->CR1 |= (1<<7);

  // update interrupt flag - status register
  TIM6->SR &= ~(1<<0);

  // EGR register - update generation for registers
  TIM6->EGR |= (1<<0);

}

void runPitch(int f_note){

  if (f_note == 0){
    // stops the timer when counter disabled
    TIM6->CR1 &= ~(1<<0);
  }
  else{
    // set ARR for the note frequency
    TIM6->ARR = (CK_INT / (2*f_note)) - 1; // equation from calcs. PSC = 0.
    
    // update generation to reinitialize counter + update registers
    TIM6->EGR |= (1<<0);

    // clear flag caused by update generation from previous line
    TIM6->SR &= ~(1<<0);

    // restart timer and enable counter
    TIM6->CR1 |= (1 << 0);
 
  }

}




