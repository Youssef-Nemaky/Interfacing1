/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 19/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to genrate a 4KHz clock 
  using Timer0 PWM mode.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 8Mhz Clock.
  2) Use Timer0 in FAST PWM mode and you choose the required frequency pre-scaler (F_CPU/8 -> 3,906.25 Hz).
  3) Clock dutty cycle is 50 %.
==============================================================================
*/

#ifndef F_CPU
#define F_CPU (8000000UL)
#endif

#include <avr/io.h>

void TIMER0_setDuttyCycle(uint8_t x);
void TIMER0_init(void);

int main(void){
    TIMER0_init();
    while(1){

    }
}

/* A function to initialize Timer0 in FAST PWM mode */
void TIMER0_init(void){
    /* 1) a PWM mode -> Clear Force output Compare FOC0.
       2) FAST PWM mode -> Set WGM00 & WGM01 bits. 
       3) Clear OC0 on compare match, set OC0 at BOTTOM (Non-Inverting) -> Clear COM00 & Set COM01 bits.
       4) prescaler F_CPU/8 -> Set CS01 & Clear CS00 and CS02.
    */
    TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

    /* Make OCR0(PB3) pin output */
    DDRB |= (1<<PB3);
    /* Set Dutty Cycle */
    TIMER0_setDuttyCycle(128);
}   

void TIMER0_setDuttyCycle(uint8_t x){
    OCR0 = x;
}


