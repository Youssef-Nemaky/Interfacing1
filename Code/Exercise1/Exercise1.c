/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 9/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to control a led 
  using a push button.
  REQUIREMENTS:
  1) Configure the uc clock with internal 1Mhz clock.
  2) The switch is connected to pin 3 in PORTA using PULL DOWN configuration.
  3) The led is connected to pin 5 in PORTC using POSITIVE LOGIC configuration.
  4) Turn on the led when the switch status is pressed.
  5) Turn off the led when the switch status is released.
==============================================================================
*/

#include <avr/io.h>
#include <util/delay.h>


int main(void){
    /* Make pin 3 in PORTA input */
    DDRA &= ~(1<<PA3);
    /* Make pin 5 in PORTC output and set initial value of logic low */
    DDRC |= (1<< PC5);
    PORTC &= ~(1<< PC5);

    /* SUPER LOOP */
    while(1){
        /* Check if the switch is pressed */
        if(PINA & (1<<PA3)){
            /* Turn ON the led when switch is pressed */
            PORTC |= (1<<PC5);
        } else {
            /* Turn OFF the led when the swtich is released */
            PORTC &= ~(1<<PC5);
        }
    }
    return 0;
}