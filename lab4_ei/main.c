// main.c
// GPIO blink LED with clock configuration, playing Fur Elise
// Emily Ing
// eing@g.hmc.edu
// 9/27/26

// Includes for libraries
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_TIM6.h"
#include "STM32L432KC_TIM7.h"
#include "STM32L432KC_FLASH.h"

//#include <stdint.h>

// Define macros for constants
#define LED_PIN 3 // LM386 - low-voltage audio power amplifier

// Fur Elise - Pitch in Hz, duration in ms
const int notes[][2] = {
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	250},
{  0,	125},
{494,	125},
{523,	125},
{587,	125},
{659,	375},
{392,	125},
{699,	125},
{659,	125},
{587,	375},
{349,	125},
{659,	125},
{587,	125},
{523,	375},
{330,	125},
{587,	125},
{523,	125},
{494,	250},
{  0,	125},
{330,	125},
{659,	125},
{  0,	250},
{659,	125},
{1319,	125},
{  0,	250},
{623,	125},
{659,	125},
{  0,	250},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	500},
{  0,	0}};

int main(void) {
    configureFlash();
    configureClock();

    // Turn on clock to GPIOB
    RCC->AHB2ENR |= (1 << 1);

    pitch();
    duration();

    // Set LED_PIN as output
    pinMode(LED_PIN, GPIO_OUTPUT);

    // Blink LED
    for(int i = 0; i < (sizeof(notes)/sizeof(notes[0])); i++) {
        // duration the note lasts
        runDuration(notes[i][1]);
        // while the duration is running, do this
        while(!((TIM7->SR >> 0) & 1)){
            // pitch is on while duration running
            runPitch(notes[i][0]);
            // if there's no more duration, flag update
            if (notes[i][0] == 0){
                TIM6->SR &= ~(1<<0);
            }
            else{
                // while the pitch is on, do this
                while(!((TIM6->SR >> 0) & 1)){
                    // note is running
                    togglePin(LED_PIN);
                    TIM6->SR &= ~(1<<0);
                }
            }
            TIM6->SR &= ~(1 << 0);
        }
    }
    return 0;
}