/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 10/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to control a led
  REQUIREMENTS: 
  1) Configure the uc clock with internal 8Mhz Clock.
  2) The led is connected to pin 6 in PORTD
  3) Connect the led using NEGATIVE LOGIC configuration.
  4) Flash the led every 1 second.
==============================================================================
*/
#ifndef F_CPU
#define F_CPU (8000000UL)
#endif
#include <avr/io.h>
#include <util/delay.h>

int main(void){
    /* Make pin 6 of PROTD output */
    DDRD |= (1<<PD6);
    /* Initalize the led to be turned OFF */
    PORTD |= (1<<PD6);

    while (1){
        /* Wait 1 Second */
        _delay_ms(1000);
        /* Toggle(flash) the led*/
        PORTD ^= (1<<PD6);
    }
    
    return 0;
}