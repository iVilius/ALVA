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
#include <util/delay.h>

void toggle_LED0_3_times( void);
void toggle_LED0_1s( void);
void toggle_LED0_100ms( void);
void toggle_LED0_10ms( void);
void LED0( int on);
void LED1( int on);
void LED2( int on);
void LED3( int on);
void init_LED( void);

#endif /* LED_H_ */