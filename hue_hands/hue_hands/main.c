/*
 * hue_hands.c
 *
 * Created: 2/27/2019 2:00:31 PM
 * Author : danin
 */ 

#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_ON		PORTD &= ~(1 << PORTD3)
#define LED_OFF		PORTD |= (1 << PORTD3)

#define TRIGGER_ON	PORTD |= (1 << PORTD2)
#define TRIGGER_OFF	PORTD &= ~(1 << PORTD2)

double calc_dist(void);
void wait (double ms);

int main(void)
{
	DDRD |= (1 << PORTD3); 
	DDRD |= (1 << PORTD2);
	
	LED_OFF;
	TRIGGER_OFF;
	
	double distance = 0;
	distance = calc_dist();
	
	//check if there is difference in distance by having varying how long the LED is turned on.
	LED_ON;
	wait(distance*100);
	LED_OFF;
	
    while (1) 
    {			
    }
}

double calc_dist(void)
{
	//test.
	TCNT1H = 0;
	TCNT1L = 0;
	
	//send trigger to ultra sonic sensor.
	TRIGGER_ON;
	_delay_us(15);
	TRIGGER_OFF;
	
	//set clock no pre-scaler when echo signal is high (1).
	while(!(PIND & (1 << PIND4)));
	
	TCCR1B |= ((1 << CS10) | (1 << CS12));
	
	//stop when echo signal is low (0).
	while((PIND & (1 << PIND4)));
	
	
	//read the clock value and do calculations. TODO
	return TCNT1;
}

void wait (double ms) {
	for (int i = 0; i<ms; i++){
		_delay_ms(1);
	}
}
