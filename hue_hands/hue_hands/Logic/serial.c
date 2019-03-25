/*
 * serial.c
 *
 * Created: 23-3-2019 19:35:13
 *  Author: Simon
 */ 
#include "../Include/util.h"
#include "../Include/serial.h"

void initRTX()
{
	UBRR0H = (BRC >> 8);
	UBRR0L = BRC;
	
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}