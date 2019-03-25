/*
 * hue_hands.c
 *
 * Created: 2/27/2019 2:00:31 PM
 * Author : danin
 */ 
#include "Include/util.h"
#include "Include/ultrasonic.h"
#include "Include/serial.h"

int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;
}

int main(void)
{
	DDRD |= (1 << PORTD3); 
	DDRD |= (1 << PORTD2);
	DDRB |= (1 << PORTB6);
	
	/* Just to be safe. */
	TRIGGER_OFF;
	
	/* Does it live? */
 	LED_ON;
	wait(1000);
	LED_OFF;
	
	/* Enable global interrupts and overflow interrupts. */
	sei();
	TIMSK1 |= (1 << TOIE1);
	
	initRTX();
	
    while (1) 
    {
		if(BUTTON_PRESSED)
		{
			LED_ON;
			UDR0 = '8';
			wait(calc_dist(&TimerOverflow));
			LED_OFF;
			wait(calc_dist(&TimerOverflow));
		}
		LED_OFF;
    }
}

