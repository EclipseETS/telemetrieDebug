/*
 * SPI_COM_328P.c
 *
 * Created: 2014-01-16 16:09:14
 *  Author: Fred Lamer
 */ 
#define		F_CPU	1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "SPI_COM_328P.h"

/*int main(void)
{
    while(1)
    {
        //TODO:: Please write your application code 
    }
}*/

void SPI_InitSlave(int data_mode, int data_order)
{
	/* Set MISO output, all others input */
	DDRB = (1<<MISO);
	DDRB &= ~(1<<SS);		// SS as input
	/* Enable SPI */
	SPCR = (1<<SPE);
	switch (data_mode)				// Set the data mode: valid value for SPI from 0 to 3
	{
		case 0:
		SPCR &= ~(1<<CPOL) & ~(1<<CPHA);
		break;
		case 1:
		SPCR &= ~(1<<CPOL);
		SPCR |= (1<<CPHA);
		break;
		case 2:
		SPCR &= ~(1<<CPHA);
		SPCR |= (1<<CPOL);
		break;
		case 3:
		SPCR |= (1<<CPHA) | (1<<CPOL);
		break;
	}
	switch(data_order)				//MSBfirst OR LSBfirst
	{
		case 'L':
		SPCR |= (1<<DORD);
		break;
		case 'M':
		SPCR &= ~(1<<DORD);
		break;
	}
}
char SPI_SlaveReceive()
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
	;
	/* Return data register */
	return SPDR;
}

void SPI_InitMaster(int data_mode, int data_order, int clock_divider, char SS_port, int SS_pin)
{
	/* Set MOSI and SCK AND SS output all others input */
	DDRB = (1<<MOSI) | (1<<SCK) | (1<<SS);
	switch(SS_port)
	{
		case 'B':
		DDRB |= (1<<SS_pin);
		break;
		case 'C':
		DDRC |= (1<<SS_pin);
		break;
		case 'D':
		DDRD |= (1<<SS_pin);
		break;
	}
	SPCR = (1<<SPE)|(1<<MSTR);
	//DDRB = 0b00101100;
	/* Enable SPI, Master*/
	switch (data_mode)				// Set the data mode: valid value for SPI from 0 to 3
	{
		case 0:
		SPCR &= ~(1<<CPOL) & ~(1<<CPHA);
		break;
		case 1:
		SPCR &= ~(1<<CPOL);
		SPCR |= (1<<CPHA);
		break;
		case 2:
		SPCR &= ~(1<<CPHA);
		SPCR |= (1<<CPOL);
		break;
		case 3:
		SPCR |= (1<<CPHA) | (1<<CPOL);
		break;
	}
	switch(data_order)				//MSBfirst OR LSBfirst
	{
		case 'L':
		SPCR |= (1<<DORD);
		break;
		case 'M':
		SPCR &= ~(1<<DORD);
		break;
	}
	switch (clock_divider)				// Set the clock_divider: valid value are:2,4,8,16,32,64,128
	{
		case 2:
		SPCR &= ~(1<<SPR1) & ~(1<<SPR0);
		SPCR |= (1<<SPI2X);
		break;
		case 4:
		SPCR &= ~(1<<SPI2X) & ~(SPR0) & ~(SPR1);
		break;
		case 8:
		SPCR &= ~(1<<SPR1);
		SPCR |= (1<<SPI2X) | (1<<SPR0);
		break;
		case 16:
		SPCR &= ~(1<<SPI2X) & ~(1<<SPR1);
		SPCR |= (1<<SPR0);
		break;
		case 32:
		SPCR &= ~(1<<SPR0);
		SPCR |= (1<<SPR1) | (1<<SPI2X);
		break;
		case 64:
		SPCR &= ~(1<<SPI2X) & ~(1<<SPR0);
		SPCR |= (1<<SPR1);
		break;
		case 128:
		SPCR &= ~(1<<SPI2X);
		SPCR |= (1<<SPR0) | (1<<SPR1);
		break;
	}
}
void SPI_MasterSend(char data, char SS_port, int SS_pin)
{
	switch(SS_port)
	{
		case 'B':
		PORTB &= ~(1<<SS_pin);
		break;
		case 'C':
		PORTC &= ~(1<<SS_pin);
		break;
		case 'D':
		PORTD &= ~(1<<SS_pin);
		break;
	}
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}
char SPI_transfer(char data, char SS_port, int SS_pin)
{
	switch(SS_port)
	{
		case 'B':
		PORTB &= ~(1<<SS_pin);
		break;
		case 'C':
		PORTC &= ~(1<<SS_pin);
		break;
		case 'D':
		PORTD &= ~(1<<SS_pin);
		break;
	}
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	
	return SPDR;
}
void SPI_SlaveResponse(char response)
{
	SPDR = response;
}
void SPI_MasterSendBasic(char data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}
char SPI_transferBasic(char data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	
	return SPDR;
}

void SPI_Start()
{
	SS_HIGH;
	_delay_us(10);
	SS_LOW;
}

void SPI_Stop()
{
	SS_HIGH;
}