/*
 * timer1.c
 *
 * Created: 11-May-17 12:34:49
 *  Author: Vilius
 */ 

/*	16-bit timer with PVM. Documentation is on page 276 in the datasheet. 
	The timer is currently exclusively used for the winding button logic.*/

#include "timer1.h"

int counter;

void init_timer1( void) {
	/* Clear global interrupts */
	cli();
	/* CS1 register bits 12:10 
	0x00		No clock source (Timer/Counter stopped)
	0x01		clkIO/1
	0x02		clkIO/8
	0x03		clkIO/64
	0x04		clkIO/256
	0x05		clkIO/1024
	0x06-0x07	external clk sources
	*/
	set_bit(TCCR1B, CS00);
	set_bit(TCCR1B, CS01);
	clear_bit(TCCR1B, CS02);
	/* Enable timer overflow */
	set_bit(TIMSK1, TOIE1);			//
	/* Enable global interrupts */
	sei();
	counter = 0;
}

void disable_timer1( void) {
	clear_bit(TCCR1B, CS00);
	clear_bit(TCCR1B, CS01);
	clear_bit(TCCR1B, CS02);
	
}

ISR(TIMER1_OVF_vect) {
	//remember to set the timer stack back to 0!
	toggle_bit(PORTB, PB4);
	counter++;
	if (counter == 4) {
		counter = 0;
		clear_bit(TCCR1B, CS00);
		clear_bit(TCCR1B, CS01);
		clear_bit(TCCR1B, CS02);
	}
}