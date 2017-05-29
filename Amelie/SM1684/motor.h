/*
 * motor.h
 *
 * Created: 24-Oct-16 17:36:42
 *  Author: Vilius
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

//#include "definitions.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "LED.h"

#include "buttons.h"

void init_motors( void);
void motor_heddles_step( void);
void motor_heddles_up( void);
void motor_heddles_stop( void);
void motor_heddles_down( void);

void motor_winding_stop( void);
void motor_winding_ccw( void);
void motor_winding_cw( void);

#endif /* MOTOR_H_ */