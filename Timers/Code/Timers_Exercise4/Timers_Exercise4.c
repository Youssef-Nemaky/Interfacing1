/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 19/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to generate 500Hz
  clock using PWM.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 1Mhz Clock.
  2) Use Timer0 in FAST PWM mode with clock equals to F_CPU/8 clock.
  3) Clock dutty cycle is 50 %. 
  4) Clock dutty cycle is 25 %.
==============================================================================
*/

#ifndef F_CPU
#define F_CPU (1000000UL)
#endif

#include <avr/io.h>
#include <util/delay.h>

void TIMER0_25DuttyCycle(void);
void TIMER0_50DuttyCycle(void);
void TIMER0_init(void);

int main(void){
    TIMER0_init();
    while(1){
        /* A delay of 5 seconds and then switch between 50 % and 25 % dutty cycle */
        _delay_ms(5000);
        TIMER0_25DuttyCycle();
        _delay_ms(5000);
        TIMER0_50DuttyCycle();
    }
}

/* A function to initialize Timer0 in FAST PWM mode */
void TIMER0_init(void){
    /* 1) a PWM mode -> Set Force output Compare FOC0.
       2) FAST PWM mode -> Set WGM00 & WGM01 bits. 
       3) Clear OC0 on compare match, set OC0 at BOTTOM (Non-Inverting) -> Clear COM00 & Set COM01 bits.
       4) prescaler F_CPU/8 -> Set CS01 & Clear CS00 and CS02.
    */
    TCCR0 = (1<<FOC0) | (1<<WGM00) | (1<<WGM01) |  (1<<COM01) | (1<<CS01);

    /* Make OCR0(PB3) pin output */
    DDRB |= (1<<PB3);
    /* Start with 50 % dutty cycle */
    TIMER0_50DuttyCycle();
}   
void TIMER0_50DuttyCycle(void){
    OCR0 = 128;
}

void TIMER0_25DuttyCycle(void){
    OCR0 = 64;
}