/*
 * motor.h
 *
 * Created: 24-Oct-16 17:36:42
 *  Author: Vilius
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "definitions.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>
#include "LED.h"

void init_motors( void);
void motor_heddles_step( void);
void motor_rapier_step( void);
void motor_reed_step( void);
void motor_garage_primary_cw( void);
void motor_garage_primary_ccw( void);
void motor_garage_secondary_cw( void);
void motor_garage_secondary_ccw( void);

#endif /* MOTOR_H_ */