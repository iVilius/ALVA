/*
 * buttons.c
 *
 * Created: 24-Oct-16 15:15:18
 *  Author: Vilius
 */ 

#include "buttons.h"

void init_buttons( void) {
	
	/*------Set input---------*/
	clear_bit(DDRE, DDE3);		// Heddles button
	clear_bit(DDRG, DDG0);		// Reed button
	clear_bit(DDRE, DDE6);		// Garage primary cw button
	clear_bit(DDRD, DDD6);		// Garage primary ccw button
	clear_bit(DDRG, DDG2);		// Garage secondary cw button
	//clear_bit();				// Garage secondary ccw button
	clear_bit(DDRD, DDD7);		// Rapier button
	/*-------Set to 1---------*/
	set_bit(PORTE, PE3);		// PIN 6
	set_bit(PORTG, PG0);		// PIN 15
	set_bit(PORTE, PE6);		// PIN 9 EXT 2
	set_bit(PORTD, PD6);		// PIN 10 EXT 2
	set_bit(PORTG, PG2);		// PIN 15 EXT 3
	set_bit(PORTD, PD7);		// PIN 10 EXT 3
}

BOOL heddles_old = FALSE;
BOOL heddles_new = FALSE;

void button_heddles( void) {
	heddles_new = !test_bit(PINE, PE3);
	if(heddles_new == TRUE && heddles_old == FALSE) {
		motor_heddles_step();
		heddles_old = TRUE;
		//toggle_bit(PORTE, PE2);
	}
	heddles_old = heddles_new;
}

BOOL reed_old = FALSE;
BOOL reed_new = FALSE;

void button_reed( void) {
	reed_new = !test_bit(PING, PG0);
	if(reed_new != reed_old) {
		motor_reed_step();
		reed_old = reed_new;
	}
	reed_old = reed_new;
}

BOOL rapier_old = FALSE;
BOOL rapier_new = FALSE;

void button_rapier( void) {
	rapier_new = !test_bit(PING, PG0); // THIS IS THE REED BUTTON
	if(rapier_new == TRUE && rapier_old == FALSE) {
		motor_rapier_step_cw_ccw();
		rapier_old = rapier_new;
	} else if (rapier_new == FALSE && rapier_old == TRUE) {
		motor_rapier_step_ccw_cw();
		rapier_old = rapier_new;
	}
}

BOOL garage_primary_old_cw = FALSE;
BOOL garage_primary_new_cw = FALSE;

void button_garage_primary_cw( void) {
	garage_primary_new_cw = !test_bit(PINE, PE6);
	if(garage_primary_new_cw == TRUE && garage_primary_old_cw == FALSE) {
		motor_garage_primary_cw();
		garage_primary_old_cw = TRUE;
	}
	garage_primary_old_cw = garage_primary_new_cw;
}

BOOL garage_primary_old_ccw = FALSE;
BOOL garage_primary_new_ccw = FALSE;

void button_garage_primary_ccw( void) {
	garage_primary_new_ccw = !test_bit(PIND, PD6);
	if(garage_primary_new_ccw == TRUE && garage_primary_old_ccw == FALSE) {
		motor_garage_primary_ccw();
		garage_primary_old_ccw = TRUE;
	}
	garage_primary_old_ccw = garage_primary_new_ccw;
}

BOOL garage_secondary_old_cw = FALSE;
BOOL garage_secondary_new_cw = FALSE;

void button_garage_secondary_cw( void) {
	garage_secondary_new_cw = !test_bit(PING, PG2);
	if(garage_secondary_new_cw == TRUE && garage_secondary_old_cw == FALSE) {
		motor_garage_secondary_cw();
		garage_secondary_old_cw = TRUE;
	}
	garage_secondary_old_cw = garage_secondary_new_cw;
}

BOOL garage_secondary_old_ccw = FALSE;
BOOL garage_secondary_new_ccw = FALSE;

void button_garage_secondary_ccw( void) {
	garage_secondary_new_ccw = !test_bit(PING, PG2); // FIND REAL BUTTON
	if(garage_secondary_new_ccw == TRUE && garage_secondary_old_ccw == FALSE) {
		motor_garage_secondary_ccw();
		garage_secondary_old_ccw = TRUE;
	}
	garage_secondary_old_ccw = garage_secondary_new_ccw;
}