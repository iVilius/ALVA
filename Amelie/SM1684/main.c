/*
 * SM1684.c
 *
 * Created: 22-Oct-16 16:16:11
 * Author : Vilius
 */ 

#include "definitions.h"
#include <avr/io.h>
#include <stdio.h>
#include "timer0.h"
#include "LED.h"
#include "buttons.h"
#include "motor.h"
#include "stdint.h"


/* T0D0: Implement PID-like control on delay */

void init( void) {	
	init_motors();
	init_buttons();
	init_LED();
}

int main( void) {
	init();
    /* Replace with your application code */
    while (1) 
    {
// 		set_bit(PORTE, PE2);
// 		if(!test_bit(PINE, PE2))
// 			toggle_LED0();
		button_rapier();
		button_reed();
		button_heddles();
		button_garage_primary_cw();
		button_garage_primary_ccw();
		button_garage_secondary_cw();
		button_garage_secondary_ccw();
    }
}


