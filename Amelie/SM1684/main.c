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
#include "timer1.h"
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
void WINDING_WAIT_CW();
void WINDING_WAIT_CCW();
void WINDING_STEP_SINGLE_CW();
void WINDING_STEP_SINGLE_CCW();
void WINDING_STEP_HIGH_SPEED_CW();
void WINDING_STEP_HIGH_SPEED_CCW();
void WINDING_ES(); //implement

// State pointer
void (*statefunc_heddles)(void) = HEDDLES_ON;
void (*statefunc_winding)(void) = WINDING_ON;

// Variables
int state_els1_new = FALSE;
int state_els1_old = TRUE;
int state_els2_new = FALSE;
int state_els2_old = TRUE;
int state_heddles_new = FALSE;
int state_heddles_old = TRUE;

void WINDING_ON() {
	//stop the motor if it is running
	motor_winding_stop();
	if(get_button_state(BUTTON_WINDING_CW) && !get_button_state(BUTTON_WINDING_CCW)) {
		//start the 16-bit timer
		set_bit(TCCR1B, CS00);
		set_bit(TCCR1B, CS01);
		clear_bit(TCCR1B, CS02);
		statefunc_winding = WINDING_WAIT_CW;
		return;
	}
	else if (get_button_state(BUTTON_WINDING_CCW) && !get_button_state(BUTTON_WINDING_CW)) {
		//start the 16-bit timer
		set_bit(TCCR1B, CS00);
		set_bit(TCCR1B, CS01);
		clear_bit(TCCR1B, CS02);
		statefunc_winding = WINDING_WAIT_CCW;
		return;
	}
}

void WINDING_WAIT_CW() {
	//wait some ms and stop it in ISR
	//check if CW is still on
	if(!test_bit(TCCR1B, CS00)) {		//check if the timer has stopped;
		if(get_button_state(BUTTON_WINDING_CW)) {	//if CW still on
			statefunc_winding = WINDING_STEP_HIGH_SPEED_CW;//go to high speed stepping
			return;
		}
		//otherwise
// 		statefunc_winding = WINDING_STEP_SINGLE_CW;//go to single step
// 		return;
	}
	//if CW has FE
	//go to single step
	if(!get_button_state(BUTTON_WINDING_CW)) {
		//remember to set the timer stack back to 0!
		clear_bit(TCCR1B, CS00);
		clear_bit(TCCR1B, CS01);
		clear_bit(TCCR1B, CS02);
		statefunc_winding = WINDING_STEP_SINGLE_CW;
		return;
	}
}

void WINDING_WAIT_CCW() {
	//wait some ms and stop it in ISR
	//check if CW is still on
	if(!test_bit(TCCR1B, CS00)) {		//check if the timer has stopped;
		if(get_button_state(BUTTON_WINDING_CCW)) {	//if CW still on
			statefunc_winding = WINDING_STEP_HIGH_SPEED_CCW;//go to high speed stepping
			return;
		}
		//otherwise
// 		statefunc_winding = WINDING_STEP_SINGLE_CCW;//go to single step
// 		return;
	}
	//if CW has FE
	//go to single step
	if(!get_button_state(BUTTON_WINDING_CCW)) {
		//remember to set the timer stack back to 0!
		clear_bit(TCCR1B, CS00);
		clear_bit(TCCR1B, CS01);
		clear_bit(TCCR1B, CS02);
		statefunc_winding = WINDING_STEP_SINGLE_CCW;
		return;
	}
}

void WINDING_STEP_HIGH_SPEED_CW() {
	toggle_LED0_3_times();
	if(get_button_state(BUTTON_WINDING_CW))
		motor_winding_cw();
	else if(!get_button_state(BUTTON_WINDING_CW))
		statefunc_winding = WINDING_ON;
}

void WINDING_STEP_HIGH_SPEED_CCW() {
	if(get_button_state(BUTTON_WINDING_CCW))
		motor_winding_ccw();
	else if(!get_button_state(BUTTON_WINDING_CCW))
		statefunc_winding = WINDING_ON;
}

void WINDING_STEP_SINGLE_CW() {
	//set the motor to run one step
	motor_winding_cw();
	statefunc_winding = WINDING_ON;
}

void WINDING_STEP_SINGLE_CCW() {
	//set the motor to run one step
	motor_winding_ccw();
	statefunc_winding = WINDING_ON;
}

void HEDDLES_ON() {
	if(!get_button_state(BUTTON_END_LIMIT_1))
		motor_heddles_up();
		//statefunc_heddles = HEDDLES_DOWN;
	else if (!get_button_state(BUTTON_END_LIMIT_2))
		motor_heddles_down();
		//statefunc_heddles = HEDDLES_UP;
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
	state_heddles_new = get_button_state(BUTTON_HEDDLES);
	if(state_heddles_new == TRUE && state_heddles_old == FALSE) {
		state_heddles_old = state_heddles_new;
		//move motor upwards
		motor_heddles_up();
		//go to next state
		statefunc_heddles = HEDDLES_MOVE_UP;
	}
	state_heddles_old = state_heddles_new;
}

void HEDDLES_MOVE_UP() {
	//indicate motor is ON
	//toggle_LED0_3_times();
	//until els2 is on
	if((!get_button_state(BUTTON_END_LIMIT_2))) {
		motor_heddles_stop();				//stop the motor
		//go to next state
 		statefunc_heddles = HEDDLES_UP;
	}		
}

void HEDDLES_MOVE_DOWN() {
	//indicate motor is ON
	//toggle_LED0_3_times();
	//until els1 is on
	if((!get_button_state(BUTTON_END_LIMIT_1))) {
		motor_heddles_stop();				//stop the motor
		//go to next state
		statefunc_heddles = HEDDLES_DOWN;
	}
}

void HEDDLES_UP() {
	//if RE on heddles button 
	state_heddles_new = get_button_state(BUTTON_HEDDLES);
	if(state_heddles_new == TRUE && state_heddles_old == FALSE) {
		state_heddles_old = state_heddles_new;
		//move motor downwards
		motor_heddles_down();
		//go to next state
		statefunc_heddles = HEDDLES_MOVE_DOWN;
	}
	state_heddles_old = state_heddles_new;		
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
	init_timer1();
}

int main( void) {
 	set_bit(DDRB, DDB4);
	init();
	for(;;) {
		//if(get_button_state(BUTTON_ES))	//implement later
			
 		(*statefunc_heddles)();			// WORKING FINE
		//motor_heddles_down();
		//(*statefunc_winding)();
		//_delay_ms(1000);
		//toggle_LED0_1s();
		//set_bit(PORTB, PB4);	
		//button_heddles();
	}
	return 1;
}
