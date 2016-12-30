/*
 * motor.c
 *
 * Created: 24-Oct-16 17:36:34
 *  Author: Vilius
 */ 

#include "motor.h"

int dist_heddles = 0;
int dist_garage = 0;
int dist_reed = 0;

// Speed constants. The lower the constant - the faster the rotation
const int speed_garage = 4;
const int speed_reed = 50;
const int speed_heddles = 3;

void init_motors( void) {
	/*------Set output--------*/
	set_bit(DDRB, DDB5);		// STEP HEDDLES
	set_bit(DDRE, DDE2);		// DIR  HEDDLES
	/*-------Set to 0---------*/
	set_bit(PORTB, PB5);		// PIN 7
	set_bit(PORTE, PE2);		// PIN 5
	
	/*------Set output--------*/
	set_bit(DDRB, DDB6);		// STEP REED
	set_bit(DDRE, DDE3);		// DIR  REED
	/*-------Set to 0---------*/
	set_bit(PORTB, PB6);		// PIN 8
	set_bit(PORTE, PE3);		// PIN 6
	
	/*------Set output--------*/
	set_bit(DDRD, DDD5);		// STEP GARAGE
	set_bit(DDRE, DDE5);		// DIR  GARAGE
	/*-------Set to 0---------*/
	set_bit(PORTD, PD5);		// PIN 10
	set_bit(PORTE, PE5);		// PIN 9
}

void motor_garage_step( void) {
	while (1) {
		set_bit(PORTD, PD5);
		_delay_us(speed_garage);
		clear_bit(PORTD, PD5);
		_delay_us(speed_garage);
		dist_garage = dist_garage +1;
		//6400 is 15 degrees for 51200 steps per rev with 1:3 ratio
		//51200 steps causes overflow and instability.
		//In order to revolute fully, use fewer-step config.
		if(dist_garage>6400/*6400*/) { 
			clear_bit(PORTD, PD5);
			dist_garage = 0;
			return;
		}
	}
}

void motor_garage_cw( void) {
	set_bit(PORTE, PE5);		// clockwise direction
	motor_garage_step();
}

void motor_garage_ccw( void) {
	clear_bit(PORTE, PE5);		// counter-clockwise direction
	motor_garage_step();
}

void motor_reed_step( void) {
	while(1) {
		set_bit(PORTB, PB6);
		_delay_us(speed_reed);
		clear_bit(PORTB, PB6);
		_delay_us(speed_reed);
		dist_reed = dist_reed +1;
		if(dist_reed>12800) {		// 12800 steps is 360 degrees
			clear_bit(PORTB, PB6);
			dist_reed = 0;
			return;
		}
	}
	toggle_bit(PORTE, PE3);			// switch direction
}

void motor_heddles_step( void) {
	toggle_LED0();
	while(1) {
		set_bit(PORTB, PB5);
		_delay_us(speed_heddles);
		clear_bit(PORTB, PB5);
		_delay_us(speed_heddles);
		dist_heddles = dist_heddles +1;
		if(dist_heddles>6400) {		// 6400 steps is 180 degrees
			clear_bit(PORTB, PB5);
			dist_heddles = 0;
			break;
		}
	}
	toggle_bit(PORTE, PE2);			// switch direction
}