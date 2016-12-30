/*
 * LED.c
 *
 * Created: 24-Oct-16 15:14:06
 *  Author: Vilius
 */ 

#include "LED.h"

void init_LED( void) {
	/*------Set input--------*/
	set_bit(DDRB, DDB4);		// LED 0
// 	set_bit(DDRB, DDB5);		// LED 1
// 	set_bit(DDRB, DDB6);		// LED 2
// 	set_bit(DDRE, DDE3);		// LED 3
	/*-------Set to 1---------*/
	set_bit(PORTB, PB4);		
// 	set_bit(PORTB, PB5);
// 	set_bit(PINB, PB6);
// 	set_bit(PINE, PE3);
	
}

void LED0( int on) {
	if(on)
	clear_bit(PORTB, PB4);
	else
	set_bit(PORTB, PB4);
}

void toggle_LED0( void) {
 	toggle_bit(PORTB, PB4);
}