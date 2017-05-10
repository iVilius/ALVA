/*
 * definitions.h
 *
 * Created: 02.07.2013 17:51:58
 *  Author: Vebjørn
 * Edited: Vilius 
 * Edited: 03.21.2016 15:00:00
 */ 

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define F_CPU 1000000		//16 MHz, with 1:2 prescaler and CKDIV8 programmed = 1 MHz

#include <stdio.h>

typedef char BOOL;
#define TRUE 1
#define true 1
#define FALSE 0
#define false 0

// button struct definition
typedef struct {
	uint8_t *ddrX;	//data direction
	uint8_t ddXX;	//data block
	uint8_t *portX; //port
	uint8_t *pinX;	//pin
	uint8_t pXX;	//number
} button;

//sets bit "bit" in register "reg"
#define set_bit(reg, bit)		(reg |= (1<<bit))
//same as set_bit only clears all other bits
#define set_bit_ex(reg, bit)	(reg = (1<<bit))
//clears bit "bit" in register "reg"
#define clear_bit(reg, bit)		(reg &=~ (1<<bit))
//tests if bit "bit" is set in register "reg"
#define test_bit(reg, bit)		(reg & (1<<bit))
//toggles bit "bit" in register "reg"
#define toggle_bit(reg, bit)	(reg ^= (1<<bit))


#ifndef ASSERT
//! ASSERT macro for debugging. ATMEL specific.
#ifndef RELEASE
#define ASSERT(x) if(!(x)) asm("break")
#else
#define ASSERT(x) if(!(x)) asm("jmp 0")
#endif
#endif

#endif /* DEFINITIONS_H_ */