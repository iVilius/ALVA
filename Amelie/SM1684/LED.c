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

void toggle_LED0_1s( void) {
	_delay_ms(1000);
	toggle_bit(PORTB, PB4);
}

void toggle_LED0_100ms( void) {
	_delay_ms(100);
 	toggle_bit(PORTB, PB4);
}

void toggle_LED0_10ms( void) {
	_delay_ms(10);
	toggle_bit(PORTB, PB4);
}

void toggle_LED0_3_times( void) {
	clear_bit(PORTB, PB4);		//ON
	_delay_ms(50);
	toggle_bit(PORTB, PB4);		//OFF
	_delay_ms(50);
	toggle_bit(PORTB, PB4);		//ON
	_delay_ms(50);
	toggle_bit(PORTB, PB4);		//OFF
	_delay_ms(50);
	toggle_bit(PORTB, PB4);		//ON
	_delay_ms(50);
	toggle_bit(PORTB, PB4);		//OFF
	_delay_ms(50);
	toggle_bit(PORTB, PB4);		//ON
	_delay_ms(50);
	toggle_bit(PORTB, PB4);		//OFF
}