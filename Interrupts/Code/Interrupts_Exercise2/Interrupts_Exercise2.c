/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 15/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to control 8 LEDs by 
  external interrupt INT1.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 1Mhz Clock.
  2) 8 LEDs are connected to PORTC.
  3) Connect all LEDs using POSITIVE LOGIC configuration. 
  4) A roll action is performed using the LEDs each led for half second.
  The first LED is lit and roll down to the last LED then back to the first LED.
  This operation is done continously.
  5) Enable INTERNAL PULL UP resistance at INT1 pin (PD3).
  6) When the INT0 is triggererd, Flash the LEDS 5 times in 5 seconds.
==============================================================================
*/

#ifndef F_CPU
#define F_CPU (1000000UL)
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define NUMBEROFFLASHES 5

uint8_t flashCounter;

int main(void){
    uint8_t ledToBeOn = 0;
    /* LEDs Configurations */
    /* Make PORTC output */
    DDRC = 0xFF;
    /* Initialize the LEDs to be OFF by writing logical 0 to the whole port (POSITIVE LOGIC) */
    PORTC = 0;

    /* External Interrupt INT1 Configurations */
    /* Make INT1 pin(PD3 in PORTD) input */
    DDRD &= ~(1<<PD3);
    /* Enable INTERNAL PULL UP resistance */
    PORTD |= (1<<PD3);
    /* Make INT1 work on FALLING EDGE (As the pin is already configured with INTERNAL PULL UP resistance) */
    MCUCR |= (1<<ISC11);
    /* Enable External Interrupt INT1 */
    GICR |= (1<<INT1);

    /* Enable Global Interrupts */
    SREG |= (1<<7);
    
    /* SUPER LOOP */
    while(1){
        /* Roll down the LEDs */
        PORTC = (1<<ledToBeOn);
        /* Increment the LEDs */
        ledToBeOn++;
        /* Make sure that you don't exceed 7 as the LEDs are connected to PORTC from pin 0 to pin 7 */
        ledToBeOn = ledToBeOn > 7? 0 : ledToBeOn;
        /* A small delay of 0.5 second between each roll */
        _delay_ms(500);
    }
    return 0;
}

ISR(INT1_vect){
    /* Turn off all the LEDs */
    PORTC = 0;
    /* Flash the LEDs 5 times in 5 seconds meaning you light up the LEDs each 0.5 second */
    for(flashCounter = 0; flashCounter < 2 * NUMBEROFFLASHES; flashCounter++){
        /* A delay of 0.5 second */
        _delay_ms(500);
        /* Toggle the LEDs */
        PORTC ^= 0xFF;
    }
}