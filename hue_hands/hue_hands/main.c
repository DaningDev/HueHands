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
char serialBuffer[TX_BUFFER_SIZE];
uint8_t serialReadPos = 0;
uint8_t serialWritePos = 0;

double distance;
char data[10];

void appendSerial(char c);
void serialWrite(char c[]);

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;
}

ISR(USART_TX_vect)
{
	if(serialReadPos != serialWritePos)
	{
		UDR0 = serialBuffer[serialReadPos];
		serialReadPos++;
		
		if(serialReadPos >= TX_BUFFER_SIZE)
		{
			serialReadPos++;
		}
	}
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
			/* Calculate the distance using ultra sonic. */
			distance = calc_dist(&TimerOverflow);
			wait(100);
			
			/* Put the result into a char array and append \n\r for python script */
			sprintf(data,"%.1lf", distance);
			strcat(data, "/n");
			
			/* Write the data */
			serialWrite(data);
			
			wait(100);
		}
		LED_OFF;
    }
}

void appendSerial(char c)
{
	serialBuffer[serialWritePos] = c;
	serialWritePos++;
	
	if(serialWritePos >= TX_BUFFER_SIZE)
	{
		serialWritePos = 0;
	}
}

void serialWrite(char c[])
{
	for(uint8_t i = 0; i < strlen(c); i++)
	{
		appendSerial(c[i]);
	}
	
	if(UCSR0A & (1 << UDRE0))
	{
		UDR0 = 0;
	}
}





