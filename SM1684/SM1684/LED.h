/*
 * LED.h
 *
 * Created: 24-Oct-16 15:14:19
 *  Author: Vilius
 */ 


#ifndef LED_H_
#define LED_H_

#include "definitions.h"
#include <avr/io.h>
#include <stdio.h>

void toggle_LED0( void);
void LED0( int on);
void LED1( int on);
void LED2( int on);
void LED3( int on);
void init_LED( void);

#endif /* LED_H_ */