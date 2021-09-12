/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 12/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to control a 7-segment
  using a push button.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 1Mhz Clock.
  2) The switch is connected to pin 4 in PORTD.
  3) Connect the switch using PULL DOWN configuration.
  4) The 7-segment is connected to first 4-pins  in PORTC.
  5) If the switch is pressed, just increase the number appearing in the 7-segment
  display, and if we reach the maximum number (9) overflow occurs. 
  6) Make sure you handle switch de-bouncing in your code.
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
    /* A variable to indicate that the button is released */
    uint8_t isReleased = 1;
    /* Make pin 4 in PORTD input */
    DDRD &= ~(1<<PD4);
    /* Make the first 4-pins in PORTC output */
    DDRC |= 0x0F;
    /* Initalize the 7-segment to display zero */
    PORTC &= 0xF0;

    while(1){
        /* Check if the button is pressed */
        if(PIND & (1<<PD4)){
            /* Handle de-bouncing by making a short delay */
            _delay_ms(30);
            /* Check again */
            if(PIND & (1<<PD4)){
                /* Make sure the button is released before incrementing again */
                if(isReleased == 1){
                    isReleased = 0;
                    /* Increase the number */
                    numberToDisplay++;
                    /* Handle overflow as 10 can't be displayed on a single 7-segment display */
                    if(numberToDisplay > 9) numberToDisplay = 0;
                    /* Output the number to the 7-segment display */
                    PORTC = (PORTC & 0xF0) | numberToDisplay;
                }
            }
        } else isReleased = 1;
    }
    return 0;
}