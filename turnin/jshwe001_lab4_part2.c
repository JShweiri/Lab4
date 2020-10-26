/*	Author: jshwe001
 *  Partner(s) Name: Ryan Giron
 *	Lab Section: 024
 *	Assignment:1 Lab #4  Exercise # 2
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
	increment,
	decrement,
	release,
	reset
} state;

static unsigned char buttons = 0;
static unsigned char tmpC = 0x07;

void tick()
{
	buttons = PINA & 0x03;

	switch (state) // Transitions
	{
	case begin:
		state = wait;
		break;
	case wait:
		if (buttons == 0)
		{
			state = wait;
			break;
		}
		else if (buttons == 1)
		{
			state = increment;
			break;
		}
		else if (buttons == 2)
		{
			state = decrement;
			break;
		}
		else if (buttons == 3)
		{
			state = reset;
			break;
		}
	case increment:
	case decrement:
		state = release;
		break;
	case release:
		if (buttons == 3)
		{
			state = reset;
			break;
		}
		else if (buttons != 0)
		{
			state = release;
			break;
		}
		else
		{
			state = wait;
			break;
		}
	case reset:
		state = wait;
		break;
	default:
		state = begin;
		break;
	}

	switch (state) // State actions
	{
	case begin:
		break;

	case wait:
		PORTC = tmpC;
		break;

	case increment:
		if (tmpC < 9)
		{
			tmpC++;
		}
		PORTC = tmpC;
		break;
	case decrement:
		if (tmpC > 0)
		{
			tmpC--;
		}
		PORTC = tmpC;
		break;
	case release:
		PORTC = tmpC;
		break;
	case reset:
		tmpC = 0;
		PORTC = tmpC;
		break;
	}
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRC = 0xFF;
	PORTC = 0x00;
	state = begin;
	while (1)
	{
		tick();
	}
}
