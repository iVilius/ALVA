/*
 * buttons.c
 *
 * Created: 24-Oct-16 15:15:18
 *  Author: Vilius
 */ 

#include "buttons.h"

int old24 = 0;
int new24 = 0;

int old180 = 0;
int new180 = 0;

int old_dir = 0;
int new_dir = 0;

void init_buttons( void) {
	
	/*------Set input---------*/
	clear_bit(DDRE, DDE3);		// Heddles button
	clear_bit(DDRG, DDG0);		// Reed button
	clear_bit(DDRE, DDE6);		// Garage cw button
	clear_bit(DDRD, DDD6);		// Garage ccw button
	/*-------Set to 1---------*/
	set_bit(PORTE, PE3);		// PIN 6
	set_bit(PORTG, PG0);		// PIN 15
	set_bit(PORTE, PE6);		// PIN 9 EXT 2
	set_bit(PORTD, PD6);		// PIN 10 EXT 2
// 	/*------Set input--------*/
// 	set_bit(DDRE, DDE7);		// button 1
// 	set_bit(DDRF, DDF3);		// button 2
// 	set_bit(DDRG, DDG5);		// button 3
// 	/*-------Set to 1---------*/
// 	set_bit(PINE, PE7);
// 	set_bit(PINF, PF3);
// 	set_bit(PING, PG5);
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

BOOL garage_old_cw = FALSE;
BOOL garage_new_cw = FALSE;

void button_garage_cw( void) {
	garage_new_cw = !test_bit(PINE, PE6);
	if(garage_new_cw == TRUE && garage_old_cw == FALSE) {
		motor_garage_cw();
		garage_old_cw = TRUE;
	}
	garage_old_cw = garage_new_cw;
}

BOOL garage_old_ccw = FALSE;
BOOL garage_new_ccw = FALSE;

void button_garage_ccw( void) {
	garage_new_ccw = !test_bit(PIND, PD6);
	if(garage_new_ccw == TRUE && garage_old_ccw == FALSE) {
		motor_garage_ccw();
		garage_old_ccw = TRUE;
	}
	garage_old_ccw = garage_new_ccw;
}

/*
void button1( void) {
	// rising edge detector
	new24 = !test_bit(PINE, PE7);
	if (new24 == 1 && old24 == 0) {
		old24 = 1;
	} else {
		old24 = new24;
	}
}

void button2( void) {
	// rising edge detector
	new180 = !test_bit(PINF, PF3);
	if (new180 == 1 && old180 == 0) {
		old180 = 1;
		
	} else {
		old180 = new180;
	}
}

void button3( void) {
	// rising edge detector
	new_dir = !test_bit(PING, PG5);
	if (new_dir == 1 && old_dir == 0) {
		old_dir = 1;
		toggle_bit(PORTE, PE2); //Switch direction
		toggle_LED0();
	} else {
		old_dir = new_dir;
	}
}*/