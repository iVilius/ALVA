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

void init_buttons( void);
void button_heddles( void);
void button_rapier( void);
void button_reed( void);
void button_garage_primary_cw( void);
void button_garage_primary_ccw( void);
void button_garage_secondary_cw( void);
void button_garage_secondary_ccw( void);

#endif /* BUTTONS_H_ */