/*	Author: jshwe001
 *  Partner(s) Name: Ryan Giron
 *	Lab Section: 024
 *	Assignment:1 Lab #4  Exercise # 5
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
	checking,
	correct,
	locks
} state;

static unsigned char array[4] = {1, 2, 3, 4};
static unsigned char tmpA = 0x00;
static unsigned char tmpB = 0x00;

void tick()
{

	unsigned char counts = 0;
	unsigned char _isValid = 0;
	tmpA = PINA;

	switch (state) // Transitions
	{
	case begin:
		state = wait;
		break;
	case wait:
		if (tmpA == 0x80)
		{
			state = locks;
			break;
		}
		else if (tmpA == 0x04)
		{
			state = checking;
			break;
		}

		else
		{
			state = wait;
			break;
		}
	case checking:
		for (char i = 0; i < 4; i++)
			_isValid = array[i];
		tmpA = PINA; //this is made to have the breakpoint in the code
		if (tmpA == _isValid)
		{
			++counts;
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
		if (counts == 4)
		{
			state = correct;
			break;
		}
	case correct:
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

	switch (state) //Actions
	{
	case begin:
		PORTC = state;
		break;

	case wait:
		PORTC = state;
		break;

	case checking:
		PORTC = state;
		break;

	case correct:
		if (tmpB == 0)
			tmpB = 1;
		else if (tmpB == 1)
			tmpB = 0;
		PORTB = tmpB;
		PORTC = state;
		break;
	case locks:
		tmpB = 0;
		PORTB = tmpB;
		PORTC = state;
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
