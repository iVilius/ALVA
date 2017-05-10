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
#include <avr/sleep.h>

// All purpose states
void LED_ON();
void LED_OFF();
// Heddles states
void HEDDLES_ON();
void HEDDLES_DOWN();
void HEDDLES_MOVE_UP();
void HEDDLES_MOVE_DOWN();
void HEDDLES_UP();
void HEDDLES_ES(); //implement

// Winding states
void WINDING_ON();
void WINDING_WAIT();
void WINDING_STEP_SINGLE();
void WINDING_STEP_HIGH_SPEED();
void WINDING_ES(); //implement

// State pointer
void (*statefunc_heddles)() = HEDDLES_ON;
void (*statefunc_winding)() = WINDING_ON;

// Variables
int *state_els1_new = FALSE;
int *state_els1_old = FALSE;
int *state_els2_new = FALSE;
int *state_els2_old = FALSE;
int *state_heddles_new = FALSE;
int *state_heddles_old = FALSE;

void WINDING_ON() {
	if(get_button_state(BUTTON_WINDING_CW) && !get_button_state(BUTTON_WINDING_CCW))
		statefunc_winding = WINDING_WAIT;
	else if (get_button_state(BUTTON_WINDING_CCW) && !get_button_state(BUTTON_WINDING_CW))
		statefunc_winding = WINDING_WAIT;
}

void WINDING_WAIT() {
	//start a timer
	//if CW has FE
		//go to single step
	//wait some ms
	//stop the timer
	//check if CW is still on
	//if CW still on
		//go to high speed stepping
	//otherwise
		//go to single step
}

void WINDING_STEP_HIGH_SPEED() {
	//
}

void WINDING_STEP_SINGLE() {
	//set the motor to run one step
	statefunc_winding = WINDING_ON;
}

void HEDDLES_ON() {
	if(get_button_state(BUTTON_END_LIMIT_1))
		statefunc_heddles = HEDDLES_DOWN;
	else if (get_button_state(BUTTON_END_LIMIT_2))
		statefunc_heddles = HEDDLES_UP;
	else {
		//This is initial movement
		//move heddles motor upwards
		motor_heddles_up();					//speed control is in timer0
		//go to next state
		statefunc_heddles = HEDDLES_MOVE_UP; 
	}
}

void HEDDLES_DOWN() {
	//if RE on heddles button
	if(rising_edge_detector(state_heddles_new, state_heddles_old, BUTTON_HEDDLES)){
		//move motor upwards
		motor_heddles_up();
		//go to next state
		statefunc_heddles = HEDDLES_MOVE_UP;
	}
}

void HEDDLES_MOVE_UP() {
	//until els2 is on
	if((get_button_state(BUTTON_END_LIMIT_2))) {
		motor_heddles_stop();				//stop the motor
		//go to next state
 		statefunc_heddles = HEDDLES_UP;
	}		
}

void HEDDLES_MOVE_DOWN() {	//here
	//until els1 is on
	if((get_button_state(BUTTON_END_LIMIT_1))) {
		motor_heddles_stop();				//stop the motor
		//go to next state
		statefunc_heddles = HEDDLES_DOWN;
	}
}

void HEDDLES_UP() {
	//if RE on heddles button 
	if(rising_edge_detector(state_heddles_new, state_heddles_old, BUTTON_HEDDLES)){
		//move motor downwards
		motor_heddles_down();
		//go to next state
		statefunc_heddles = HEDDLES_MOVE_DOWN;
	}		
}

void LED_ON() {
	toggle_LED0_3_times();
	statefunc_heddles = LED_ON;
}

void init( void) {	
	init_motors();
	init_buttons();
	init_LED();
	init_timer0();
}

int main( void) {
	
	init();
    /* Replace with your application code */
	for(;;) {
		//if(get_button_state(BUTTON_ES)) //implement later
			
		(*statefunc_heddles)();
		(*statefunc_winding)();
		_delay_ms(1000);
		button_heddles();
		//sleep_mode(); 
	}
	return 1;
}
