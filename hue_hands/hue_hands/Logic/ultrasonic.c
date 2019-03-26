/*
 * ultrasonic.c
 *
 * Created: 3/20/2019 1:33:55 PM
 *  Author: danin
 */ 
#include "../Include/util.h"
#include "../Include/ultrasonic.h"

double calc_dist(int *timerOverflow)
{
	long count;
	double distance;
	
	/* send trigger to ultra sonic sensor. */
	TRIGGER_ON;
	_delay_us(15);
	TRIGGER_OFF;
	
	/* Clear Timer Counter, 
	start timer on rising edge with no prescaler, 
	clear input capture flag and 
	clear overflow flag. */
	TCNT1 = 0; 
	TCCR1B |= ((1 << ICES1) | (1 << CS10)); 
	TIFR1 = 1 << ICF1; 
	TIFR1 = 1 << TOV1;
	
	/* Wait for rising edge */
	while((TIFR1 & (1 << ICF1)) == 0);
	TCNT1 = 0;
	TCCR1B = 0x01;
	TIFR1 = 1 << ICF1;
	TIFR1 = 1 << TOV1;
	timerOverflow = 0;
	
	/* Wait for falling edge */
	while((TIFR1 & (1 << ICF1)) == 0);
	
	/* Calculate distance in cm based on 20Mhz timer frequency and the speed of sound */
	count = ICR1 + (65535 * (int)timerOverflow);
	distance = (double)count / 933;
	return distance;
}