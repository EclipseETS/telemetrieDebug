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


#define IRQ_PIN  4
#define IRQ_PORT_READ PIND

int main(void)
{
    //DDRB = 0x00; //DEFINE PORTB INPUT
	//DDRB |= (1<<0);
	
	//int i=0;
	//char data[50];
	
	
	//SERIAL_Init(9600,'D',1,8,'R');
	//SPI_InitMaster(0,'M',8,'B',2);
	//NRF_PrintRegister(SETUP_RETR);
	//NRF_WriteRegister(SETUP_RETR, 0b00000000);
	//NRF_PrintRegister(SETUP_RETR);
	
	
	//NRF_ReadRegister(SETUP_RETR);
	/*
	SERIAL_SendCaracter('>');
    while (1) 
    {
		//PORTB |= (1<<0);
		//_delay_ms(1000);
		//PORTB &= ~(1<<0);
		//_delay_ms(1000);
		
		
		
		
		
		
		//_delay_ms(1000);
		
		
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
    }
	*/
	char Status;
	DDRB |=(1<<CE);
	
	SERIAL_Init(9600,'D',1,8,'R');
	SPI_InitMaster(0,'M',8,'B',2);
	char data = 'A';
	NRF_SET_PTX();
	
	 
	 while(1)
	 {
		 _delay_ms(1000);
		 NRF_Control(STANBY);
		 NRF_FlushFifo(TX);
		 NRF_LoadTXPayload(&data,1);
		 NRF_ActivateTransmission();
		 while ((IRQ_PORT_READ & (1<<IRQ_PIN)))
		 {
			 Status = NRF_ReadStatusRegister();
			 if (Status & (1<<MAX_RT))				// If the maximum of retry was reached (transmission FAILED).
			 {
				 NRF_FlushFifo(TX);
				 NRF_WriteRegister(STATUS, (1<<MAX_RT));		// Reset register.
			 }
			 else if (Status & (1<<TX_DS))				// If the transmission was successful.
			 {
				 NRF_WriteRegister(STATUS, (1<<TX_DS));		// Reset register.
			 }
		 }
	 }
}

