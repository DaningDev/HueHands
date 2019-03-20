/*
 * ultrasonic.c
 *
 * Created: 3/20/2019 1:33:55 PM
 *  Author: danin
 */ 
#include "../Include/util.h"
#include "../Include/ultrasonic.h"

double calc_dist(void)
{
	//Reset last timer.
	TCCR1B &= (~(1 << CS10) | ~(1 << CS12));
	TCNT1 = 0;
	
	//send trigger to ultra sonic sensor.
	TRIGGER_ON;
	_delay_us(15);
	TRIGGER_OFF;
	
	//Wait until echo signal is high (1).
	while(!(PIND & (1 << PIND4)));
	
	//Start Timer with prescaler of 1024.
	TCCR1B |= ((1 << CS10) | (1 << CS12));
	
	//Wait until echo signal is low (0).
	while((PIND & (1 << PIND4)));
	
	//read the clock value and do calculations. TODO
	return TCNT1;
}