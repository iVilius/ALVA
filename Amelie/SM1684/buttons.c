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
	clear_bit(DDRG, DDG0);		// END LIMIT SWITCH 1
	clear_bit(DDRE, DDE6);		// Winding cw button
	clear_bit(DDRD, DDD6);		// Winding ccw button
	clear_bit(DDRD, DDD7);		// END LIMIT SWITCH 2
	/*-------Set to 1---------*/
	set_bit(PORTE, PE3);		// PIN 6
	set_bit(PORTG, PG0);		// PIN 15
	set_bit(PORTE, PE6);		// PIN 9 EXT 2
	set_bit(PORTD, PD6);		// PIN 10 EXT 2
	set_bit(PORTD, PD7);		// PIN 10 EXT 3
}

button BUTTON_HEDDLES = {
	&DDRE,
	DDE3,
	&PORTE,
	&PINE,
	PE3,
	"heddles"
};

button BUTTON_END_LIMIT_1 = {
	&DDRG,
	DDG0,
	&PORTG,
	&PING,
	PG0,
	"end limit switch 1"
};

button BUTTON_END_LIMIT_2 = {
	&DDRD,
	DDD7,
	&PORTD,
	&PIND,
	PD7,
	"end limit switch 2"
};

button BUTTON_WINDING_CW = {
	&DDRE,
	DDE6,
	&PORTE,
	&PINE,
	PE6,
	"winding cw"
};

button BUTTON_WINDING_CCW = {
	&DDRD,
	DDD6,
	&PORTD,
	&PIND,
	PD6,
	"winding ccw"
};

int get_button_state(button BUTTON) {
	if(!test_bit(*BUTTON.pinX, BUTTON.pXX)) return 1;
	return 0;
}

int falling_edge_detector(int *state_new, int *state_old, button BUTTON) {
	state_new = !test_bit(*BUTTON.pinX, BUTTON.pXX);
	if(state_new == FALSE && state_old == TRUE) {
		state_old = state_new;
		return 1;
	}
	state_old = state_new;
	return 0;
}

int rising_edge_detector(int *state_new, int *state_old, button BUTTON) {
	state_new = !test_bit(*BUTTON.pinX, BUTTON.pXX);
	if(state_new == TRUE && state_old == FALSE) {
		state_old = state_new;
		return 1;
	}
	state_old = state_new;
	return 0;
}

//------------BUTTON-SPECIFIC FUNCTIONS-----------//
BOOL heddles_old = FALSE;
BOOL heddles_new = FALSE;

void button_heddles( void) {
	heddles_new = !test_bit(PINE, PE3);
	if(heddles_new == TRUE && heddles_old == FALSE) {
		motor_heddles_step();
		heddles_old = TRUE;
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
	rapier_new = !test_bit(PIND, PD7);
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