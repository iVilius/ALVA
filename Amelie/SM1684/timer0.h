/*
 * timer0.h
 *
 * Created: 3/25/2016 1:31:14 PM
 *  Author: Vilius
 */ 
/* 8-bit timer */

#ifndef TIMER0_H_
#define TIMER0_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#include "definitions.h"

void init_timer0( void);

#endif /* TIMER0_H_ */