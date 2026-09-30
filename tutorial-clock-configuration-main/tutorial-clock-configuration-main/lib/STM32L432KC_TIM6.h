// Header for TIM 6 functions
// Emily Ing
// eing@g.hmc.edu
// 9/27/26

#ifndef STM32L432KC_TIM6_H
#define STM32L432KC_TIM6_H

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////
#define __IO volatile

// CLK_INT
#define CK_INT 4000000UL

// base address for TIM6 -- pg 70 of ref manual
#define TIM6_BASE (0x40001000UL) 

///////////////////////////////////////////////////////////////////////////////
// Bitfield struct for TIM6
///////////////////////////////////////////////////////////////////////////////

// values from Table 144 in Lecture 9
typedef struct {
  volatile uint32_t CR1;      // 0x00
  volatile uint32_t CR2;      // 0x04
  uint32_t          RESERVED0;// 0x08
  volatile uint32_t DIER;     // 0x0C
  volatile uint32_t SR;       // 0x10
  volatile uint32_t EGR;      // 0x14
  uint32_t          RESERVED1[3]; // 0x18, 0x1C, 0x20 -- the gap between 14 and 24
  volatile uint32_t CNT;      // 0x24
  volatile uint32_t PSC;      // 0x28
  volatile uint32_t ARR;      // 0x2C
} TIM_TypeDef;

// Pointers to TIM_TypeDef-sized chunks of memory for each peripheral
#define TIM6 ((TIM_TypeDef *) TIM6_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////

void pitch(void);
void runPitch(int f_note);

#endif