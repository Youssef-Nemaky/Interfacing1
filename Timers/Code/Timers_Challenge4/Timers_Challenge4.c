/*
==============================================================================
* Authour: Youssef El-Nemaky
* Date: 19/9/2021
* Program/Purpose: Write Embedded C code using ATmega16 uc to genrate a 2KHz clock 
  using Timer1 in CTC mode.
  REQUIREMENTS: 
  1) Configure the uc clock with internal 8Mhz Clock.
  2) Use Timer1 in CTC mode with clock equals to F_CPU/8 clock.
  3) Generate a PWM signal on PC0 pin with dutty cycle 25 %.
==============================================================================
*/

#ifndef F_CPU
#define F_CPU (8000000UL)
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
void TIMER1_init(void);

uint8_t g_timer1CompareMatchCounter = 0;

int main(void){
    /* Make PC0 output */
    DDRC |= (1<<PC0);
    /* Set output on pin PC0 */
    PORTC |= (1<<PC0);
    /* Initialize Timer1 */
    TIMER1_init();
    /* Enable Global Interrupts */
    SREG |= (1<<7);
    while(1){

    }
}

/* A function to initialize Timer1 in CTC mode */
void TIMER1_init(void){
    /* 1) Disconnect OC1A & OC1B
       2) CTC mode -> Set WGM12 bit. 
       3) prescaler F_CPU/8 -> Set CS11.
    */
    TCCR1A = (1<<FOC1A);
    TCCR1B = (1<<WGM12) | (1<<CS11);

    /* Start Counting from 0*/
    TCNT1 = 0;
    /* OCR1A = 125 to get 25% duty cycle */
    OCR1A = 125;

    /* Enable output compare A match interrupt */
    TIMSK |= (1<<OCIE1A);

}   

ISR(TIMER1_COMPA_vect){
    g_timer1CompareMatchCounter++;
    if(g_timer1CompareMatchCounter == 1){
        PORTC ^= (1<<PC0);
    } else if(g_timer1CompareMatchCounter == 4){
        PORTC ^= (1<<PC0);
        g_timer1CompareMatchCounter = 0;
    }
}


