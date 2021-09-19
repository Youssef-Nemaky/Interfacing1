/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 19/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to control LED 
  brightness using FAST PWM.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 1Mhz Clock.
  2) Use Timer0 in FAST PWM mode with clock equals to F_CPU/8 clock.
  3) Generate a PWM signal with different dutty cycles to control the brightness of the LED.
==============================================================================
*/

#ifndef F_CPU
#define F_CPU (1000000UL)
#endif

#include <avr/io.h>
#include <util/delay.h>

void TIMER0_setDuttyCycle(uint8_t x);
void TIMER0_init(void);

int main(void){
    uint8_t dutty;
    TIMER0_init();
    while(1){
        /* Increase Brightness */
        for(dutty = 0; dutty < 255; dutty++){
            TIMER0_setDuttyCycle(dutty);
            _delay_ms(30);
        }
        /* Decrease Brightness */
        for(dutty = 255; dutty > 0; dutty--){
            TIMER0_setDuttyCycle(dutty);
            _delay_ms(30);
        }
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
}   

void TIMER0_setDuttyCycle(uint8_t x){
    OCR0 = x;
}


