/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 10/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to control 8 LEDs.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 1Mhz Clock.
  2) 8-Leds are connected to PORTC.
  3) Connect all LEDs using POSITIVE LOGIC configuration.
  5) A roll action is perform using the LEDs each led for half second. The first
     LED is lit and roll down to the last LED then back to the first LED. This
     operation is done continously.
==============================================================================
*/

#ifndef F_CPU 
#define F_CPU (1000000UL)
#endif

#include <avr/io.h>
#include <util/delay.h>

#define LEDS_DDR DDRA
#define LEDS_PORT PORTA

int main(void){
    /* Make the PORT of the LEDS output */
    LEDS_DDR = 0xFF;
    /* Initialize the LEDS with low level output */
    LEDS_PORT = 0;

    /* SUPER LOOP */
    while(1){
        /* Wait for 0.5 second */
        _delay_ms(500);
        /* Roll the LEDs */
        LEDS_PORT = (LEDS_PORT << 1);
        /* Lit the first LED */
        if(LEDS_PORT == 0) LEDS_PORT = 1;
    }
    return 0;
}