/*
 * pwm.c
 *
 * Created: 3/20/2019 1:43:33 PM
 *  Author: danin
 */ 
#include "../Include/util.h"
#include "../Include/pwm.h"

void initTimerPWM()
{
	TCCR0A |= ((1 << FOC0A) | (1 << COM0A0) | (1 << CS00)); //Set on match, clear on TOP at 0C0A (=pd6)
	TCCR0B |= ((1 << WGM00) | (1 << CS00)); //Start timer with PWM mode

	OCR0A = 128;
}

void setPulse(unsigned char red)
{
	OCR0A = red;
}

void setPWM()
{
	int delta = 1;
	setPulse(0);
	
	for(int red = 0; red<=255; red+=delta)
	{
		setPulse(red);
		delta+=2;
		wait(100);
	}
	for(int red = 255l; red>=0; red-=delta)
	{
		setPulse(red);
		delta-=2;
		wait(100);
	}
	setPulse(0);
	delta = 1;
	wait(100);
}