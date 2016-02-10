/*
 * Telemetry_WirelessDebug.c
 *
 * Created: 2016-02-04 3:49:26 PM
 * Author : Francis Lavallee
 */ 
#define F_CPU 1000000UL

#include <avr/io.h>
#include "src/NRF24L01.h"
#include "src/SERIAL_COM_328P.h"
#include "src/SPI_COM_328P.h"
#include <util/delay.h>


int main(void)
{
    //DDRB = 0x00; //DEFINE PORTB INPUT
	//DDRB |= (1<<0);
	
	//int i=0;
	//char data[50];
	
	
	SERIAL_Init(9600,'D',1,8,'R');
	SPI_InitMaster(0,'M',8,'B',2);
	NRF_PrintRegister(SETUP_RETR);
	NRF_WriteRegister(SETUP_RETR, 0b00001010);
	NRF_PrintRegister(SETUP_RETR);
	
	
	//NRF_ReadRegister(SETUP_RETR);
	
	/*SERIAL_SendCaracter('>');
    while (1) 
    {
		PORTB |= (1<<0);
		_delay_ms(1000);
		PORTB &= ~(1<<0);
		_delay_ms(1000);
		
		
		
		
		
		
		_delay_ms(1000);
		
		
		data[i] = SERIAL_READ();
		SERIAL_SendCaracter(data[i]);
		if(data[i] == 13){
			data[i+1]=0;
			SERIAL_SendCaracter(10);
			SERIAL_SendCaracter(13);
			SERIAL_SendStringLn(data);
			SERIAL_SendCaracter('>');
			i=-1;
		}
		i++;
    }*/
}

