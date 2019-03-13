/*
 * hue_hands.c
 *
 * Created: 2/27/2019 2:00:31 PM
 * Author : danin
 */ 

#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>

int calc_dist(void);
void wait (int ms);

int main(void)
{
	DDRD = 0b10110111;
	
    while (1) 
    {	
		int tijd = 0;
		tijd = calc_dist();
		if(tijd != 0)
		{
			DDRD = 0b10111111;
			_delay_ms(1000);
		}else
		DDRD = 0b10110111;
				
    }
}

int calc_dist(void)
{
	int distance = 0;
	DDRD = 0b10110011;
	_delay_us(10);
	DDRD = 0b10110111;
	
	//set clock no pre scaler when trigger signal is sent
	TCCR0B = 0b00000001;
	TCNT0 = 0;
	
	//while getting echo let timer run.
	while(PORTD6 == 1);
	
	//disable clock when signal get.
	TCCR0B = 0b00000000;
	
	//read the clock value
	distance = TCNT0;
	
	return distance;
}

void wait (int ms) {
	for (int i = 0; i<ms; i++){
		_delay_ms(1);
	}
}
