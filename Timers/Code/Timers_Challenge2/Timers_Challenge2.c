/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 18/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to generate 3 digital
  clocks with frequency 10KHz, 5KHz and 2.5KHz using Timer0 CTC mode. 
  REQUIREMENTS: 
  1) Configure the uc clock with internal 8Mhz Clock.
  2) Use Timer0 in CTC mode with clock equals to F_CPU/8 clock.
  3) The three clocks are output from the first 3 pins in PORTC with 
  dutty cycle 50 %.
==============================================================================
*/

#ifndef F_CPU
#define F_CPU (8000000UL)
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

void TIMER0_init(void);

/* Global variable to keep track of number of CTC matches */
uint8_t g_timer0CTCMatchCounter = 0;

int main(void){
    /* Enable global interrupts */
    SREG |= (1<<7);
    /* Make the first 3 pins of PORTC output */
    DDRC |= 0x07;
    /* Initialize the output to be 0V */
    PORTC &= 0xF8;

    /* Call TIMER0_init() function to initialize Timer0 */
    TIMER0_init();

    while(1){
 
    }
}

/* A function to initialize Timer0 in CTC mode */
void TIMER0_init(void){
    /* 1) Non PWM mode -> Clear Force output Compare FOC0.
       2) CTC mode -> Clear WGM00 & Set WGM01 bits to make Timer0 work on 
       3) Disconnect OC0 -> Clear COM00 & COM01 bits.
       4) prescaler F_CPU/8 -> Set CS01 & Clear CS00 and CS02.
    */
    TCCR0 = (1<<WGM01) |(1<<CS01);

    /* 5) Set OCR0 to 50 */
    OCR0 = 50;
    /* 6) Enable CTC interrupt */
    TIMSK |= (1<<OCIE0);
}

ISR(TIMER0_COMP_vect){
    g_timer0CTCMatchCounter++;
    PORTC ^= (1 << PC0);
    switch (g_timer0CTCMatchCounter){
    case 2:
        /* Toggle the second wave */
        PORTC ^= (1 << PC1);
        break;
    case 4:
        /* Toggle the second wave */
        PORTC ^= (1 << PC1);
        /* Toggle the third wave */
        PORTC ^= (1 << PC2);
        g_timer0CTCMatchCounter = 0;
        break;
    }
}