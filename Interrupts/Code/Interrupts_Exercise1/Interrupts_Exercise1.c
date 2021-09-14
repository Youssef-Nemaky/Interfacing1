/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 14/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to control a LED by 
  external interrupt INT0.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 1Mhz Clock.
  2) The led is connected to pin 0 in PORTC.
  3) Connect the LED using NEGATIVE LOGIC configuration. 
  4) Connect a push button with PULL DOWN configuration at INT0 pin (PD2).
  5) When the INT0 is triggererd, just toggle the LED.
==============================================================================
*/

#ifndef F_CPU
#define F_CPU (1000000UL)
#endif

#include <avr/io.h>
#include <avr/interrupt.h>


int main(void){
    /* LED Configurations */
    /* Make pin 0 in PORTC output */
    DDRC |= (1<<PC0);
    /* Initialize the led to be OFF by writing logical 1 to the pin(NEGATIVE LOGIC) */
    PORTC |= (1<<PC0);

    /* External Interrupt INT0 Configurations */
    /* Make INT0 pin(PD2 in PORTD) input */
    DDRD &= ~(1<<PD2);
    /* Make INT0 work on RISING EDGE (As the push button is working on PULL DOWN configuration) */
    MCUCR |= (1<<ISC00) | (1<<ISC01);
    /* Enable External Interrupt INT0 */
    GICR |= (1<<INT0);

    /* Enable Global Interrupts */
    SREG |= (1<<7);
    
    /* SUPER LOOP */
    while(1){
        
    }
    return 0;
}

ISR(INT0_vect){
    /* Toggle the LED */
    PORTC ^= (1<<PC0);
}