/*
 * util.h
 *
 * Created: 3/20/2019 1:35:42 PM
 *  Author: danin
 */ 

#define F_CPU 16000000
#define BAUD  9600
#define BRC   ((F_CPU/16/BAUD) - 1)
#define TX_BUFFER_SIZE	128

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <string.h>

#define LED_ON		PORTD |= (1 << PORTD3)
#define LED_OFF		PORTD &= ~(1 << PORTD3)

#define TRIGGER_ON		PORTD |= (1 << PORTD2)
#define TRIGGER_OFF		PORTD &= ~(1 << PORTD2)

#define BUTTON_PRESSED		!(PIND & (1 << PIND7))
#define BUTTON_NOT_PRESSED		PIND & (1 << PIND7)

void wait (double ms);