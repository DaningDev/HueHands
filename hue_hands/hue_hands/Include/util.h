/*
 * util.h
 *
 * Created: 3/20/2019 1:35:42 PM
 *  Author: danin
 */ 
#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_ON		PORTD |= (1 << PORTD3)
#define LED_OFF		PORTD &= ~(1 << PORTD3)

#define TRIGGER_ON	PORTD |= (1 << PORTD2)
#define TRIGGER_OFF	PORTD &= ~(1 << PORTD2)

void wait (double ms);