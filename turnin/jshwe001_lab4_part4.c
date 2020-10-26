/*	Author: jshwe001
 *  Partner(s) Name: Ryan Giron
 *	Lab Section: 024
 *	Assignment:1 Lab #4  Exercise # 4
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
	begin,
	wait,
	X_state,
	Y_state,
	locks
} state;

static unsigned char tmpA = 0x00;
static unsigned char tmpB = 0x00;

void tick()
{

	tmpA = PINA;

	switch (state) // Transitions
	{
	case begin:
		state = wait;
		break;
	case wait:
		if (tmpA == 0x04)
		{
			state = X_state;
			break;
		}
		else if (tmpA == 0x80)
		{
			state = locks;
			break;
		}

		else
		{
			state = wait;
			break;
		}
	case X_state:
		if (tmpA == 0x02)
		{
			state = Y_state;
			break;
		}
		else if (tmpA == 0x80)
		{
			state = locks;
			break;
		}
		else
		{
			state = wait;
			break;
		}
	case Y_state:
		if (tmpA == 0x80)
		{
			state = locks;
			break;
		}
		else
		{
			state = wait;
			break;
		}
	case locks:
		state = wait;
		break;
	default:
		state = begin;
		break;
	}

	switch (state) // Actions
	{
	case begin:
		PORTC = begin;
		break;

	case wait:
		PORTC = wait;
		break;

	case X_state:
		PORTC = X_state;
		break;

	case Y_state:
		if (tmpB == 0)
		{
			tmpB = 1;
			PORTB = tmpB;
			PORTC = Y_state;
			break;
		}
		else if (tmpB == 1)
		{
			tmpB = 0;
			PORTB = tmpB;
			PORTC = Y_state;
			break;
		}
	case locks:
		tmpB = 0;
		PORTB = tmpB;
		PORTC = locks;
		break;
	}
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;
	DDRC = 0xFF;
	PORTC = 0x00;
	state = begin;
	while (1)
	{
		tick();
	}
}
