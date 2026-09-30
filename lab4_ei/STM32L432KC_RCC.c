// STM32L432KC_RCC.c
// Source code for RCC functions

#include "STM32L432KC_RCC.h"

void configurePLL(void) {
    // Set clock to 80 MHz (CHANGED TO 4 MHz)
    // Output freq = (src_clk) * (N/M) / R
    // (4 MHz) * (N/M) / R = 80 MHz (CHANGED TO 4 MHz)
    // M: 1, N: 80, R: 4
    // Use MSI as PLLSRC

    // TODO: Turn off PLL
    RCC->CR &= ~(1<<24); // 24th bit goes to 0

    // TODO: Wait till PLL is unlocked (e.g., off)
    while (RCC->CR >> 25 & 1);

    // Load configuration
    // TODO: Set PLL SRC to MSI
    RCC->PLLCFGR &= ~(1<<1); // bit[1] is 0
    RCC->PLLCFGR |= (1<<0); // bit[0] is 1

    // TODO: Set PLLN
    RCC->PLLCFGR &= ~(0b1111111 << 8); // clear bits
    RCC->PLLCFGR |= (0b1010000 << 8); // Set PLLN to 80 MHz

    // TODO: Set PLLM
    RCC->PLLCFGR &= ~(0b111 << 4); // set M = 0b000

    // TODO: Set PLLR
    RCC->PLLCFGR &= ~(1 << 26); // clear bits
    RCC->PLLCFGR |= (1 << 25); // Set R = 0b01
    
    // TODO: Enable PLLR output
    RCC->PLLCFGR |= (1<<24); // Enable PLLR output

    // TODO: Enable PLL
    RCC->CR |= (1<<24); // Enable PLL
    
    // TODO: Wait until PLL is locked
    while (!((RCC->CR >> 25) & 1));
    
}

void configureClock(void){
    // Configure and turn on PLL
    configurePLL();

    // Select PLL as clock source
    RCC->CFGR |= (0b11 << 0);
    while(!((RCC->CFGR >> 2) & 0b11));
}