/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 18/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to a LED using Timer0.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 1Mhz Clock.
  2) The LED is connected to pin 0 of PORTC.
  3) Connect the LED using POSITIVE LOGIC configuration.
  4) Configure the timer clock to F_CPU/1024 prescaler
  5) Timing should be count using Timer0 in NORMAL mode.
  6) Toggle the led every (0.5) second.
==============================================================================
*/


#ifndef F_CPU
#define F_CPU (1000000UL)
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

/* A variable to count number of overflows of Timer0 */
uint8_t timer0OverflowCounter = 0;

/* Timer0 overflow interrupt service routine */
ISR(TIMER0_OVF_vect){
    timer0OverflowCounter++;
}
/* A function to initialize the LED */
void LED_init(void){
    /*** LED Configuration ***/
    /* Make pin 0 of PORTC OUTPUT */
    DDRC |= (1<<PC0);
    /* Initalize the LED to be off by setting the output of the pin to 0 volts (POSITIVE LOGIC) */
    PORTC &= ~(1<<PC0);
}

/* A function to initialize Timer0 in NORMAL mode */
void TIMER0_init(void){
    /* 1) Clear Force output Compare FOC0.
       2) Clear WGM00 & WGM01 bits to make Timer0 work on NORMAL mode.
       3) Clear COM00 & COM01 bits to disconnect OC0.
       4) Set CS00, CS02 and Clear CS01 to make the prescaler F_CPU/1024
    */
    TCCR0 = (1<<CS00) | (1<<CS02);
    /* 5) Set TOIE0 to enable timer0 overflow interrupt. */
    TIMSK |= (1<<TOIE0);
}

int main(void){
    /* Initialize the LED */
    LED_init();
    /* Initialize Timer0 */
    TIMER0_init();
    /* Enable Global Interrupts */
    SREG |= (1<<7);
    /* SUPER LOOP */    
    while(1){
        /* Check if a 0.5 second has passed */
        if(timer0OverflowCounter >= 2){
            /* Toggle the LED */
            PORTC ^= (1<<PC0);
            /* Reset the counter to 0 */
            timer0OverflowCounter = 0;
        }
    }
}