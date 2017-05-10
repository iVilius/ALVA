/*
 * buttons.h
 *
 * Created: 24-Oct-16 15:15:31
 *  Author: Vilius
 */ 


#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "definitions.h"
#include "LED.h"
#include <avr/io.h>
#include <stdio.h>
#include "motor.h"

//struct button BUTTON_HEDDLES;

button BUTTON_HEDDLES;
button BUTTON_END_LIMIT_1;
button BUTTON_END_LIMIT_2;
button BUTTON_WINDING_CW;
button BUTTON_WINDING_CCW;
	
void init_buttons( void);
void button_heddles( void);
void button_rapier( void);
void button_reed( void);
void button_garage_primary_cw( void);
void button_garage_primary_ccw( void);
int get_button_state(button BUTTON);
int falling_edge_detector(int *state_new, int *state_old, button BUTTON);
int rising_edge_detector(int *state_new, int *state_old, button BUTTON);

#endif /* BUTTONS_H_ */