/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 12/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to control a 7-segment
  using two push buttons.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 1Mhz Clock.
  2) The two switches are connected to pin 0 & 1 in PORTA.
  3) Connect both switches using PULL DOWN configuration.
  4) The 7-segment is connected to first 4-pins  in PORTD.
  5) If switch 1 is pressed, just increase the number appearing in the 7-segment
  display, and if we reach the maximum number (9), do NOTHING. 
  6) The 7-segment is connected to first 4-pins  in PORTD.
  7) If switch 2 is pressed, just decrease the number appearing in the 7-segment
  display, and if we reach the minimum number (0), do NOTHING. 
  8) Make sure you handle switches de-bouncing in your code.
==============================================================================
*/

#ifndef F_CPU
#define F_CPU (1000000UL)
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void){
    /* A variable containing the number to be displayed on the 7-segment */
    uint8_t numberToDisplay = 0;
    /* Variables to indicate that the buttons are released */
    uint8_t isSwitch1Released = 1;
    uint8_t isSwitch2Released = 1;
    /* Make pins 0 & 1 in PORTA inputs */
    DDRA &= ~(1<<PA0) & ~(1<<PA1);
    /* Make the first 4-pins in PORTD output */
    DDRD |= 0x0F;
    /* Initalize the 7-segment to display zero */
    PORTD &= 0xF0;

    while(1){
        /* Check if switch 1 is pressed */
        if(PINA & (1<<PA0)){
            /* Handle de-bouncing by making a short delay */
            _delay_ms(30);
            /* Check again */
            if(PINA & (1<<PA0)){
                /* Make sure the button is released before incrementing again */
                if(isSwitch1Released == 1){
                    isSwitch1Released = 0;
                    /* Increase the number */
                    numberToDisplay++;
                    /* Handle overflow by staying on number 9 */
                    if(numberToDisplay > 9) numberToDisplay = 9;
                    /* Output the number to the 7-segment display */
                    PORTD = (PORTD & 0xF0) | numberToDisplay;
                }
            }
        } else isSwitch1Released = 1;
        
        /* Check if switch 2 is pressed */
        if(PINA & (1<<PA1)){
            /* Handle de-bouncing by making a short delay */
            _delay_ms(30);
            /* Check again */
            if(PINA & (1<<PA1)){
                /* Make sure the button is released before decreasing again */
                if(isSwitch2Released == 1){
                    isSwitch2Released = 0;
                    /* Decrease the number */
                    numberToDisplay--;
                    /* Handle underflow by staying on number 0 */
                    if(numberToDisplay == 255) numberToDisplay = 0;
                    /* Output the number to the 7-segment display */
                    PORTD = (PORTD & 0xF0) | numberToDisplay;
                }
            }
        } else isSwitch2Released = 1;
    }
    return 0;
}