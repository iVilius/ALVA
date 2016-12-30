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
void button_reed( void);
void button_garage_cw( void);
void button_garage_ccw( void);
void button1( void);
void button2( void);
void button3( void);


#endif /* BUTTONS_H_ */