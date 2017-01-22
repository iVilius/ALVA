/*
 * motor.c
 *
 * Created: 24-Oct-16 17:36:34
 *  Author: Vilius
 */ 

#include "motor.h"

int dist_heddles = 0;
int dist_garage_primary = 0;
int dist_garage_secondary = 0;
int dist_rapier = 0;
int dist_reed = 0;

// Speed constants. The lower the constant - the faster the rotation
const int speed_garage = 4;
const int speed_rapier = 6;
const int speed_reed = 15;
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
	set_bit(DDRD, DDD4);		// DIR  REED
	/*-------Set to 0---------*/
	set_bit(PORTB, PB6);		// PIN 8
	set_bit(PORTD, PD4);		// PIN 15 EXT 2
	
	/*------Set output--------*/
	set_bit(DDRD, DDD5);		// STEP PRIMARY GARAGE
	set_bit(DDRE, DDE5);		// DIR PRIMARY GARAGE
	/*-------Set to 0---------*/
	set_bit(PORTD, PD5);		// PIN 10
	set_bit(PORTE, PE5);		// PIN 9
	
	/*------Set output--------*/
	set_bit(DDRF, DDF3);		// STEP SECONDARY GARAGE 
	set_bit(DDRG, DDG5);		// DIR SECONDARY GARAGE
	/*-------Set to 0---------*/
	set_bit(PORTF, PF3);		// PIN 3 EXT 3
	set_bit(PORTG, PG5);		// PIN 4 EXT 4
	
	/*------Set output--------*/
	set_bit(DDRB, DDB7);		// STEP RAPIER
	set_bit(DDRE, DDE7);		// DIR RAPIER
	/*-------Set to 0---------*/
	set_bit(PORTB, PB7);		// PIN 5 EXT 3
	set_bit(PORTE, PE7);		// PIN 9 EXT 3
}

void motor_garage_primary_step( void) {
	while (1) {
		set_bit(PORTD, PD5);
		_delay_us(speed_garage);
		clear_bit(PORTD, PD5);
		_delay_us(speed_garage);
		dist_garage_primary = dist_garage_primary +1;
		//6400 is 15 degrees for 51200 steps per rev with 1:3 ratio
		//51200 steps causes overflow and instability.
		//In order to revolute fully, use fewer-step config.
		if(dist_garage_primary>6400) { 
			clear_bit(PORTD, PD5);
			dist_garage_primary = 0;
			return;
		}
	}
}

void motor_garage_secondary_step( void) {
	while (1) {
		set_bit(PORTF, PF3);
		_delay_us(speed_garage);
		clear_bit(PORTF, PF3);
		_delay_us(speed_garage);
		dist_garage_secondary = dist_garage_secondary +1;
		if(dist_garage_secondary>6400) {
			clear_bit(PORTF, PF3);
			dist_garage_secondary = 0;
			return;
		}
	}
}

void motor_garage_primary_cw( void) {
	set_bit(PORTE, PE5);		// clockwise direction
	motor_garage_primary_step();
}

void motor_garage_primary_ccw( void) {
	clear_bit(PORTE, PE5);		// counter-clockwise direction
	motor_garage_primary_step();
}

void motor_garage_secondary_cw( void) {
	clear_bit(PORTG, PG5);		// clockwise direction
	motor_garage_secondary_step();
}

void motor_garage_secondary_ccw( void) {
	set_bit(PORTG, PG5);		// counter-clockwise direction
	motor_garage_secondary_step();
}


void motor_rapier_step( void) {
	while(1) {
		set_bit(PORTB, PB7);
		_delay_us(speed_rapier);
		clear_bit(PORTB, PB7);
		_delay_us(speed_rapier);
		dist_rapier = dist_rapier+1;
		if(dist_rapier>1000) { // ADJUST THIS ONE
			clear_bit(PORTB, PB7);
			dist_rapier = 0;
			break;
		}
	}
	toggle_bit(PORTE, PE7);
}

void motor_reed_step( void) {
	while(1) {
		set_bit(PORTB, PB6);
		_delay_us(speed_reed);
		clear_bit(PORTB, PB6);
		_delay_us(speed_reed);
		dist_reed = dist_reed +1;
		if(dist_reed>9000) {		// 12800 steps is 360 degrees
			clear_bit(PORTB, PB6);
			dist_reed = 0;
			break;
		}
	}
	toggle_bit(PORTD, PD4);			// switch direction
}

void motor_rapier_step_ccw_cw( void) {
	clear_bit(PORTD, PD4);
	while(1) {
		set_bit(PORTB, PB6);
		_delay_us(speed_rapier);
		clear_bit(PORTB, PB6);
		_delay_us(speed_rapier);
		dist_reed = dist_reed +1;
		if(dist_reed>6700) {		// 12800 steps is 360 degrees
			clear_bit(PORTB, PB6);
			dist_reed = 0;
			break;
		}
	}
	set_bit(PORTD, PD4);			// switch direction
	while(1) {
		set_bit(PORTB, PB6);
		_delay_us(speed_rapier);
		clear_bit(PORTB, PB6);
		_delay_us(speed_rapier);
		dist_reed = dist_reed +1;
		if(dist_reed>6700) {		// 12800 steps is 360 degrees
			clear_bit(PORTB, PB6);
			dist_reed = 0;
			break;
		}
	}
}

void motor_rapier_step_cw_ccw( void) {
	set_bit(PORTD, PD4);
	while(1) {
		set_bit(PORTB, PB6);
		_delay_us(speed_rapier);
		clear_bit(PORTB, PB6);
		_delay_us(speed_rapier);
		dist_reed = dist_reed +1;
		if(dist_reed>6900) {		// 12800 steps is 360 degrees
			clear_bit(PORTB, PB6);
			dist_reed = 0;
			break;
		}
	}
	clear_bit(PORTD, PD4);			// switch direction
	while(1) {
		set_bit(PORTB, PB6);
		_delay_us(speed_rapier);
		clear_bit(PORTB, PB6);
		_delay_us(speed_rapier);
		dist_reed = dist_reed +1;
		if(dist_reed>6900) {		// 12800 steps is 360 degrees
			clear_bit(PORTB, PB6);
			dist_reed = 0;
			break;
		}
	}
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