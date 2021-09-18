/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 18/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to control a 7-segment
  using Timer0.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 8Mhz Clock.
  2) The 7-segment is connected to the first 4-pins of PORTC.
  4) Configure the timer clock to F_CPU/256 prescaler
  5) Timing should be count using Timer0 in NORMAL mode.
  6) Every second, the 7-segment shoudl be incremented by one. if the 7-segment 
  reaches 9, overlfow will occur.
==============================================================================
*/

#ifndef F_CPU
#define F_CPU (8000000UL)
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

#define DISPLAY_DDR   DDRC
#define DISPLAY_PORT  PORTC

void DISPLAY_init(void);
void TIMER0_init(void);


/* Global Variables */
uint8_t g_timer0OvfCounter = 0;

int main(void){
    /* Call DISPLAY_init to initialize the 7-segment */
    DISPLAY_init();
    /* Call TIMER0_init to initialize Timer0 */
    TIMER0_init();
    /* Enable Global Interrupts */
    SREG |= (1<<7);
    /* SUPER LOOP */  
    while(1){
        if(g_timer0OvfCounter == 122){
            /* reset the counter */
            g_timer0OvfCounter = 0;
            /* 
              Check if the display is displaying 9 and if does 
              just overflow as you can't display 10
              else just increment the display by 1
            */
            if((DISPLAY_PORT & 0x0F) == 9){
            /* Overflow */
            DISPLAY_PORT &= 0xF0;
            } else {
                /* Increment the 7-segment */
                DISPLAY_PORT++;
            }
        }
    }
}

/* A function to initialize the 7-segment */
void DISPLAY_init(void){
    /* Make the first 4-pins of PORTC output */
    DISPLAY_DDR |= 0x0F;

    /* Display 0 at first */
    DISPLAY_PORT &= 0xF0;
}

/* A function to initialize Timer0 */
void TIMER0_init(void){
    /*
       1) Clear Force output Compare FOC0.
       2) Clear WGM00 & WGM01 bits to make Timer0 work on NORMAL mode.
       3) Clear COM00 & COM01 bits to disconnect OC0.
       4) Set CS02 & Clear CS00 and CS01 to make the prescaler F_CPU/256
    */
    TCCR0 = (1<<CS02);
    /* 5) Set TOIE0 to enable timer0 overflow interrupt. */
    TIMSK |= (1<<TOIE0);
}


/* Timer0 overflow interrupt service routine */
ISR(TIMER0_OVF_vect){
    g_timer0OvfCounter++;
}