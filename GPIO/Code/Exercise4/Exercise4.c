/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 10/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to control a led
  using a push button.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 1Mhz Clock.
  2) The switch is connected to pin 0 in PORTB.
  3) Connect the switch using internal PULL UP configuration.
  4) The led is connected to pin 0 in PORTC.
  5) Connect the led using NEGATIVE LOGIC configuration.
  6) If the switch is pressed, just toggle the led.
  7) Make sure you handle switch de-bouncing in your code.
==============================================================================
*/

#include <avr/io.h>
#include <util/delay.h>

int main(void){
    /* Make pin 0 in PORTB input */
    DDRB &= ~(1<<PB0);
    /* Enable internal pull up resistor */
    PORTB |= (1<<PB0);
    /* Make pin 0 in PORTC output */
    DDRC |= (1<<PC0);
    /* Initialize the led to be OFF */
    PORTC |= (1<<PC0);
    while(1){
        /* Check if the switch is pressed */
        if((PINB & (1<<PB0)) == 0){
            /* A small delay of 20 ms */
            _delay_ms(20);
            /* Check again to handle the de-bouncing problem */
            if((PINB & (1<<PB0)) ==  0){
                /* Toggle the LED */
                PORTC ^= (1<<PC0);
            }            
        }
    }
    return 0;
}