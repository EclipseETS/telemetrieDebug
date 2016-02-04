/*
 * SERIAL_COM_328P.c
 *
 * Created: 2014-01-16 15:34:59
 *  Author: Fred Lamer
 */ 
#define		F_CPU	1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "SERIAL_COM_328P.h"

/*int main(void)
{
	SERIAL_Init(115200,'D',1,8,'R');
    while(1)
    {
		SERIAL_SendCaracter('F');
		_delay_ms(500);
		SERIAL_SendCaracter('R');
		_delay_ms(500);
		SERIAL_SendCaracter('E');
		_delay_ms(500);
		SERIAL_SendCaracter('D');
		_delay_ms(500);      
		SERIAL_ReturnLine();
		_delay_ms(500);  
    }
}*/

void SERIAL_Init(int64_t baudRate, char parity, int stop_bit, int caracter_size, char clock_polarity)			// Initiate serial communication
{
		baudRate = F_CPU/8/baudRate-1;
		UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
		UCSR0A |= (1<<U2X0);
		
		switch (parity)
		{
			case 'D':
			UCSR0C &= ~(1<<UPM01) & ~(1<<UPM00);
			break;
			case 'E':
			UCSR0C &= ~(1<<UPM00);
			UCSR0C |= (1<<UPM01);
			break;
			case 'O':
			UCSR0C |= (1<<UPM01) | (1<<UPM00);
			break;
		}
		switch (stop_bit)
		{
			case 1:
			UCSR0C &= ~(1<<USBS0);
			break;
			case 2:
			UCSR0C |= (1<<USBS0);
			break;
		}
		switch (caracter_size)
		{
			case 5:
			UCSR0C &= (~(1<<UCSZ02) & ~(1<<UCSZ01) & ~(1<<UCSZ00));
			break;
			case 6:
			UCSR0C &= (~(1<<UCSZ02) & ~(1<<UCSZ01));
			UCSR0C |= (1<<UCSZ00);
			break;
			case 7:
			UCSR0C &= (~(1<<UCSZ02) & ~(1<<UCSZ00));
			UCSR0C |= (1<<UCSZ01);
			break;
			case 8:
			UCSR0C &= ~(1<<UCSZ02);
			UCSR0C |= (1<<UCSZ01) | (UCSZ00);		
			break;
		}
		switch (clock_polarity)
		{
			case 'R':
			UCSR0C &= ~(1<<UCPOL0);
			break;
			case 'F':
			UCSR0C |= (1<<UCPOL0);
			break;
		}
	UBRR0L = baudRate;							// Don't forget to adjust F_CPU
}
void SERIAL_SendCaracter(char data)				//***Send a single caracter***
{
	 /* Wait for empty transmit buffer */
	 while ( !( UCSR0A & (1<<UDRE0)) )
	 ;
	 /* Put data into buffer, sends the data */
	 UDR0 = data;
}
void SERIAL_SendString(char* string)			//***Send a string of caracters***
{
	int i = 0;
	while (string[i])
	{
		SERIAL_SendCaracter(string[i]);
		i++;
	}
}
void SERIAL_SendStringLn(char* string)			//***Send a string of caracter, skip a line and come back to starting point***
{
	int i = 0;
	while (string[i])
	{
		SERIAL_SendCaracter(string[i]);
		i++;
	}
	while (i > 0)
	{
		SERIAL_SendCaracter(0x08);		// Backspace
		i--;
	}
	SERIAL_SendCaracter(10);			// ascii caracter for return	
}
void SERIAL_SendCaracterLn(char data)			//***Send a caracter, skip a line and come back to starting point***
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
	SERIAL_SendCaracter(0x08);					// Backspace
	SERIAL_SendCaracter(0x0A);					// Line return
}

char SERIAL_READ()				//***Read serial data comming on the RX pin***
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;	
}
int SERIAL_CheckAvailable()		//***Check if there is valid data on the serial bus***
{
	if ( !(UCSR0A & (1<<RXC0)) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void SERIAL_ReturnLine()
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0= 0x0D;
}

