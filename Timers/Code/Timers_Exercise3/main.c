/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 18/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to generate a 2KHz 
  clock using Timer0 CTC mode.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 1Mhz Clock.
  2) Use Timer0 in CTC mode with clock equals to F_CPU clock.
  3) Clock dutty cycle is 50 %.
==============================================================================
*/

#ifndef F_CPU
#define F_CPU (1000000UL)
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

void TIMER0_init(void);

int main(void){
    TIMER0_init();
    while(1){

    }
}

/* A function to initialize Timer0 in NORMAL mode */
void TIMER0_init(void){
    /* 1) Clear Force output Compare FOC0.
       2) Clear WGM00 & Set WGM01 bits to make Timer0 work on CTC mode.
       3) Set COM00 & Clear COM01 bits to Toggle OC0 on compare match.
       4) Set CS00 & Clear CS02 and Clear CS01 to make the prescaler F_CPU/1 (No Prescalling)
    */
    TCCR0 = (1<<WGM01) | (1<<COM00) |(1<<CS00);

    /* 5) Make OC0 (PB3) PIN output*/
    DDRB |= (1<<PB3);

    /* 6) Set OCR0 to 250 to toggle the OC0 pin every half period (50 % dutty cycle) (0.00025 second) */
    OCR0 = 250;

}
