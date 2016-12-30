/*
 * timer0.c
 *
 * Created: 3/25/2016 1:31:06 PM
 *  Author: Vilius
 */ 

#include "timer0.h"

/* Init variables */
int counter = 0;
int distance = 0;

void timer0_init( void) {
	cli();
	/* clk/1 */
	set_bit(TCCR0B, CS00);
	set_bit(TCCR0B, CS01);
	set_bit(TCCR0B, CS02);
	/* Enable timer overflow */
	set_bit(TIMSK0, TOIE0);
	/* Enable global interrupts */
	sei();
}

ISR(TIMER0_OVF_vect) {	
	/*-------------Counter increment---------------*/
	counter = counter + 1;
	
	/*----------------Step-signal------------------*/
	if(counter > 5000){
		toggle_bit(PORTB, PB4);
		counter = 0;
		if (test_bit(PORTB, PB5))
			clear_bit(PORTB, PB5);
		else
			set_bit(PORTB, PB5);
		distance = distance + 1;
	}
	/*-------------Change direction----------------*/
	if(distance > 100) {
		toggle_bit(PORTB, PB4);
		distance = 0;
		if (test_bit(PORTE, PE2))
			clear_bit(PORTE, PE2);
		else
			set_bit(PORTE, PE2);
	}		
}