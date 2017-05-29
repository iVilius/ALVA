/*
 * timer0.c
 *
 * Created: 3/25/2016 1:31:06 PM
 *  Author: Vilius
 */ 

/*	8-bit timer with PVM. Documentation is on page 258 in the datasheet. 
	The timer is currently exclusively used for the heddles motor.*/

#include "timer0.h"


/* Speed control										*/
/* Lowest possible delay between PVM pulses are ~10us.	*/
/* speed 1 == 1 MHz / 256 == 256us.						*/
/* speed 2 == 1 MHz / 256 * 2 == 512us					*/
/* etc.													*/
int speed_heddles = 1;
int counter_heddles = 0;
int speed_winding = 10;
int counter_winding = 0;

/* Init variables */
void init_timer0( void) {
	/* Clear global interrupts */
	cli();
	/* CS0 register bits 02:00 
	0x00		No clock source (Timer/Counter stopped)
	0x01		clkIO/1
	0x02		clkIO/8
	0x03		clkIO/64
	0x04		clkIO/256
	0x05		clkIO/1024
	0x06-0x07	external clk sources
	*/
	set_bit(TCCR0B, CS00);
	clear_bit(TCCR0B, CS01);
	clear_bit(TCCR0B, CS02);
	/* Enable timer overflow */
	set_bit(TIMSK0, TOIE0);			//
	/* Enable global interrupts */
	sei();
}

ISR(TIMER0_OVF_vect) {
	/* Increment counter */
	counter_heddles = counter_heddles+1;
	counter_winding = counter_winding+1;
	if(counter_heddles == speed_heddles){
		/* Reset the counter */
		counter_heddles = 0;
		
		/* PWM to motor */
		toggle_bit(PORTB, PB5);
		
		//toggle_bit(PORTB, PB4);
	}
	if(counter_winding == speed_winding) {
		/* Reset the counter */
		counter_winding = 0;
		
		/* PWM to motor */
		toggle_bit(PORTD, PD5);
		
		//toggle_bit(PORTB, PB4);
	}
}