/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 10/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to control two leds
  using two push buttons.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 1Mhz Clock.
  2) The switch 1 & 2 are connected to pin 0 & 1 in PORTB.
  3) Connect both leds using POSITIVE LOGIC configuration.
  4) The led 1 & 2 are connected to pin 0 & 1 in PORTC.
  5) If switch 1 is pressed, just turn on the first led1 only and if switch2 is
  pressed, just turn on led 2 only.  
  6) In case both switches are pressed, both leds are on.
  7) In case no switches are pressed both leds are off.
==============================================================================
*/
#ifndef F_CPU
#define F_CPU (1000000UL)
#endif

#include <avr/io.h>

int main(void){
    /* Configure pin 0 & 1 in PORTB to be input */
    DDRB &= (~(1<<PB0)) & (~(1<<PB1));

    /* Configure pin 0 & 1 in PORTC to be output */
    DDRC |= (1<<PC0) | (1<<PC1);

    /* Initialize the leds to be OFF */
    PORTC &= ~(1<<PC0) & ~(1<<PC1);

    while(1){
        /* Check if switch 0 is pressed */
        if(PINB & (1<<PB0)){
            /* Turn ON the LED*/
            PORTC |= (1<<PB0);
        } else {
            /* Turn OFF the LED */
            PORTC &= ~(1<<PB0);
        }

        /* Check if switch 1 is pressed */
        if(PINB & (1<<PB1)){
            /* Turn ON the LED*/
            PORTC |= (1<<PB1);
        } else {
            /* Turn OFF the LED */
            PORTC &= ~(1<<PB1);
        }
    }
    return 0;
}