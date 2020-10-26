/*	Author: jshwe001
 *  Partner(s) Name: Ryan Giron
 *	Lab Section: 024
 *	Assignment:1 Lab #4  Exercise # 1
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States
{
	init,
	first,
	second,
	third,
	fourth
} state;

static unsigned char button = 0;

void tick()
{
	button = PINA & 0x01;

	switch (state) // State transitions
	{
	case init:
		state = first;
		break;
	case first:
		if (button == 1)
		{
			state = second;
		}
		break;
	case second:
		if (button == 0)
		{
			state = third;
		}
		break;
	case third:
		if (button == 1)
		{
			state = fourth;
		}
		break;
	case fourth:
		break;
	default:
		state = init;
		break;
	}

	switch (state) // State actions
	{
	case init:
		PORTB = 0;
		break;

	case first:
		PORTB = 1;
		break;

	case second:
		PORTB = 2;
		break;

	case third:
		PORTB = 2;
		break;

	case fourth:
		PORTB = 1;
		break;

	default:
		PORTB = 0;
		break;
	}
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	state = init;
	while (1)
	{
		tick();
	}
}
