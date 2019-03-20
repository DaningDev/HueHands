/*
 * hue_hands.c
 *
 * Created: 2/27/2019 2:00:31 PM
 * Author : danin
 */ 
#include "Include/ultrasonic.h"
#include "Include/util.h"

int main(void)
{
	DDRD |= (1 << PORTD3); 
	DDRD |= (1 << PORTD2);
	DDRB |= (1 << PORTB6);
	
	//Does it live?
 	LED_ON;
	wait(1000);
	LED_OFF;
	
	//Just to be safe.
	TRIGGER_OFF;
	
    while (1) 
    {
		if(!(PINB & (1 << PINB0)))
		{
			double distance = 0;
			distance = calc_dist();
			
			LED_ON;
			wait(distance*100);
			LED_OFF;
		} 
		else
		LED_OFF;
    }
}
