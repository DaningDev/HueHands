/*
 * hue_hands.c
 *
 * Created: 2/27/2019 2:00:31 PM
 * Author : danin
 */ 

#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_ON		PORTD |= (1 << PORTD3)
#define LED_OFF		PORTD &= ~(1 << PORTD3)

#define TRIGGER_ON	PORTD |= (1 << PORTD2)
#define TRIGGER_OFF	PORTD &= ~(1 << PORTD2)

double calc_dist(void);
int returnButton(void);
void wait (double ms);
void initTimerPWM(void);
void setPulse(unsigned char red);
void setPWM(void);

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

void wait (double ms) 
{
	for (int i = 0; i<ms; i++){
		_delay_ms(1);
	}
}
