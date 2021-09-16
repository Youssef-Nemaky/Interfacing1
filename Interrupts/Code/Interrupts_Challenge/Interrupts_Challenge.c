/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 16/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to control a 7-segment
  using external interrupt INT2.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 1Mhz Clock.
  2) The 7-segment is connected to the first 4-pins of PORTC.
  3) Connect the switch using PULL DOWN configuration on INT2 (PB2).
  4) When the INT2 is triggered, just increase the number appeared in the 7-segment
  display and if we reach the maximum number (9) overflow occurs.
==============================================================================
*/

#ifndef F_CPU
#define F_CPU (1000000UL)
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(INT2_vect){
    /* Check if the number is 9 */
    if((PORTC & 0x0F) == 9) {
        /* Overflow */
        PORTC = (PORTC & 0xF0);
    } else {
        /* Increment PORTC by 1 */
        PORTC++;
    }
}

int main(void){
    /* Enable Global Interrupts */
    SREG |= (1<<7);

    /*** 7-segment Configration ***/
    /* Make the first 4 pins of PORTC output */
    DDRC |= 0x0F;

    /* Start the 7-segment with zero displayed */
    PORTC = (PORTC & 0xF0);

    /*** INT2 Configuration ***/
    /* Make INT2 (PB2) pin input */
    DDRB &= (~(1<<PB2));
    
    /* Make INT2 work on RISING EDGE (As the pin is working on PULL DOWN configuration) */
    MCUCSR |= (1<<ISC2);

    /* Enable external interrupt INT2 request */
    GICR |= (1<<INT2);

    while(1){

    }

}

