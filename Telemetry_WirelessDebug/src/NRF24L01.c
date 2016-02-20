/*
 * NRF24L01.c
 *
 * Created: 2014-01-28 11:46:05
 *  Author: Fred Lamer
 */ 
#define		F_CPU	1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "NRF24L01.h"
#include "SPI_COM_328P.h"
#include "SERIAL_COM_328P.h"





void NRF_WriteRegister(uint8_t Register, uint8_t Data)
{
	uint8_t RegTemp = Register | 0x20;
	SPI_Start();
	SPI_transferBasic(RegTemp);
	SPI_transferBasic(Data);
	SPI_Stop();
}

uint8_t NRF_ReadRegister(uint8_t Register)
{
	uint8_t Data;
	SPI_Start();
	SPI_transferBasic(Register);
	Data = SPI_transferBasic(NOP);
	SPI_Stop();
	return Data;
}

uint8_t NRF_ReadStatusRegister()
{
	uint8_t Status;
	SPI_Start();
	Status = SPI_transferBasic(NOP);
	SPI_Stop();
	return Status;
}

void NRF_PrintRegister(uint8_t Register)
{
	uint8_t RegValue;
	SPI_Start();
	SPI_transferBasic(Register);
	RegValue = SPI_transferBasic(NOP);
	SPI_Stop();
	SERIAL_SendCaracter(RegValue);
}

void NRF_PrintStatusRegister()
{
	uint8_t Status;
	SPI_Start();
	Status = SPI_transferBasic(NOP);
	SPI_Stop();
	SERIAL_SendCaracter(Status);
}

/*		**********************************************************************************		*/
/*		**********************************************************************************		*/

void NRF_WriteTXADDR(uint8_t Adress0, uint8_t Adress1, uint8_t Adress2, uint8_t Adress3, uint8_t Adress4)
{
	SPI_Start();
	SPI_transferBasic(0x20 | TX_ADDR);				// Select register
	SPI_transferBasic(Adress0);
	SPI_transferBasic(Adress1);
	SPI_transferBasic(Adress2);
	SPI_transferBasic(Adress3);
	SPI_transferBasic(Adress4);
	SPI_Stop();
}

void NRF_WriteTXADDR3byte(uint8_t Adress0, uint8_t Adress1, uint8_t Adress2)
{
	SPI_Start();
	SPI_transferBasic(0x20 | TX_ADDR);
	SPI_transferBasic(Adress0);
	SPI_transferBasic(Adress1);
	SPI_transferBasic(Adress2);
	SPI_Stop();
}

void NRF_PrintTXADDR()
{	
	uint8_t Address0, Address1, Address2, Address3, Address4;
	SPI_Start();
	SPI_transferBasic(TX_ADDR);
	Address0 = SPI_transferBasic(TX_ADDR);
	Address1 = SPI_transferBasic(TX_ADDR);
	Address2 = SPI_transferBasic(TX_ADDR);
	Address3 = SPI_transferBasic(TX_ADDR);
	Address4 = SPI_transferBasic(TX_ADDR);
	SPI_Stop();
	SERIAL_SendCaracter(Address0);
	SERIAL_SendCaracter(Address1);
	SERIAL_SendCaracter(Address2);
	SERIAL_SendCaracter(Address3);
	SERIAL_SendCaracter(Address4);
}

void NRF_WriteRXADDR_P0(uint8_t Adress0, uint8_t Adress1, uint8_t Adress2, uint8_t Adress3, uint8_t Adress4)
{
	SPI_Start();
	SPI_transferBasic(0x20 | RX_ADDR_P0);
	SPI_transferBasic(Adress0);
	SPI_transferBasic(Adress1);
	SPI_transferBasic(Adress2);
	SPI_transferBasic(Adress3);
	SPI_transferBasic(Adress4);
	SPI_Stop();
}

void NRF_WriteRXADDR_P03byte(uint8_t Adress0, uint8_t Adress1, uint8_t Adress2)
{
	SPI_Start();
	SPI_transferBasic(0x20 | RX_ADDR_P0);
	SPI_transferBasic(Adress0);
	SPI_transferBasic(Adress1);
	SPI_transferBasic(Adress2);
	SPI_Stop();
}

void NRF_PrintRXADDR_P0()
{	
	uint8_t Address0, Address1, Address2, Address3, Address4;
	SPI_Start();
	SPI_transferBasic(RX_ADDR_P0);
	Address0 = SPI_transferBasic(RX_ADDR_P0);
	Address1 = SPI_transferBasic(RX_ADDR_P0);
	Address2 = SPI_transferBasic(RX_ADDR_P0);
	Address3 = SPI_transferBasic(RX_ADDR_P0);
	Address4 = SPI_transferBasic(RX_ADDR_P0);
	SPI_Stop();
	SERIAL_SendCaracter(Address0);
	SERIAL_SendCaracter(Address1);
	SERIAL_SendCaracter(Address2);
	SERIAL_SendCaracter(Address3);
	SERIAL_SendCaracter(Address4);
}

void NRF_WriteRXADDR_P1(uint8_t Adress0, uint8_t Adress1, uint8_t Adress2, uint8_t Adress3, uint8_t Adress4)
{
	SPI_Start();
	SPI_transferBasic(0x20  | RX_ADDR_P1);
	SPI_transferBasic(Adress0);
	SPI_transferBasic(Adress1);
	SPI_transferBasic(Adress2);
	SPI_transferBasic(Adress3);
	SPI_transferBasic(Adress4);
	SPI_Stop();
}

void NRF_PrintRXADDR_P1()
{
	uint8_t Address0, Address1, Address2, Address3, Address4;
	SPI_Start();
	SPI_transferBasic(RX_ADDR_P1);
	Address0 = SPI_transferBasic(RX_ADDR_P1);
	Address1 = SPI_transferBasic(RX_ADDR_P1);
	Address2 = SPI_transferBasic(RX_ADDR_P1);
	Address3 = SPI_transferBasic(RX_ADDR_P1);
	Address4 = SPI_transferBasic(RX_ADDR_P1);
	SPI_Stop();
	SERIAL_SendCaracter(Address0);
	SERIAL_SendCaracter(Address1);
	SERIAL_SendCaracter(Address2);
	SERIAL_SendCaracter(Address3);
	SERIAL_SendCaracter(Address4);
}

void NRF_SET_PTX()
{
	NRF_Control(STANBY);
	NRF_WriteRegister(CONFIG, 0b00001010);	
	NRF_WriteRegister(EN_AA, 0b00000001);			// auto ack
	NRF_WriteRegister(EN_RXADDR, 0b00000001);		// Enable pipe: 0
	NRF_WriteRegister(SETUP_AW, 0b00000011);		// 5 bytes address
	NRF_WriteRegister(SETUP_RETR, 0b00111010);		// auto-retransmit: 1000us ||  auto-retransmit: 10 times
	NRF_WriteRegister(RF_CH, 50);					// RF channel 50
	NRF_WriteRegister(RF_SETUP, 0b00100110);		// speed: 250Kbps	|| power: 0dbm
	NRF_WriteRegister(STATUS, 0b01110000);			// reset all interrupts
	NRF_WriteRXADDR_P0('F','U','C','K','U');	// set RX_ADDR_P0 address
	//NRF_WriteRXADDR_P03byte(0x01,0x01,0x01);
	//NRF_WriteRXADDR_P1('A','L','L','O','A');		// set RX_ADDR_P1 address
	NRF_WriteTXADDR('F','U','C','K','U');		// set TX_ADDR
	//NRF_WriteTXADDR3byte(0x01,0x01,0x01);
	NRF_WriteRegister(RX_PW_P0, 1);
	//NRF_WriteRegister(RX_PW_P1, 2);
	//NRF_WriteRegister(RX_PW_P2, 5);
	//NRF_WriteRegister(RX_PW_P3, 5);
	//NRF_WriteRegister(RX_PW_P4, 5);
	//NRF_WriteRegister(RX_PW_P5, 5);
	NRF_WriteRegister(DYNPD, 0b00000000);
	NRF_WriteRegister(FEATURE, 0b00000000);
	//NRF_WriteRegister(CONFIG, 0b00000010);		// Power up
}

void NRF_SET_PRX()
{
	NRF_Control(STANBY);
	NRF_WriteRegister(CONFIG, 0b00001011);		
	NRF_WriteRegister(EN_AA, 0b00000001);			// auto ack
	NRF_WriteRegister(EN_RXADDR, 0b00000001);		// Enable pipe: 0 
	NRF_WriteRegister(SETUP_AW, 0b00000011);		// 5 bytes address
	NRF_WriteRegister(SETUP_RETR, 0b00111010);		// auto-retransmit: 1000us ||  auto-retransmit: 10 times
	NRF_WriteRegister(RF_CH, 50);					// RF channel 50
	NRF_WriteRegister(RF_SETUP, 0b00100110);		// speed: 250KMbps	|| power: 0dbm
	NRF_WriteRegister(STATUS, 0b01110000);			// reset all interrupts
	NRF_WriteRXADDR_P0('F','U','C','K','U');	// set RX_ADDR_P0 address
	//NRF_WriteRXADDR_P03byte(0x01,0x01,0x01);
	//NRF_WriteRXADDR_P1('A','L','L','O','A');		// set RX_ADDR_P1 address
	//NRF_WriteTXADDR('A','L','L','O','A');			// set TX_ADDR
	NRF_WriteRegister(RX_PW_P0, 2);
	//NRF_WriteRegister(RX_PW_P1, 2);
	//NRF_WriteRegister(RX_PW_P2, 5);
	//NRF_WriteRegister(RX_PW_P3, 5);
	//NRF_WriteRegister(RX_PW_P4, 5);
	//NRF_WriteRegister(RX_PW_P5, 5);
	NRF_WriteRegister(DYNPD, 0x00000000);
	NRF_WriteRegister(FEATURE, 0b00000000);
	//NRF_WriteRegister(CONFIG, 0b00000011);		// Power up
}

void NRF_ActivateTransmission()
{
	NRF_Control(ACTIVE);
	_delay_us(20);
	NRF_Control(STANBY);
}

void NRF_Listen()
{
	NRF_Control(ACTIVE);
}

void NRF_LoadTXPayload(char * Data, uint8_t NumByte)
{
	uint8_t i = 0;
	SPI_Start();
	SPI_transferBasic(W_TX_PAYLOAD);
	while (i < NumByte)
	{
		SPI_transferBasic(Data[i]);
		i++;
	}
	SPI_Stop();
}

char * NRF_ReadRXPayload(uint8_t NumByte)
{
	uint8_t i = 0;
	static char Data[32];
	SPI_Start();
	SPI_transferBasic(R_RX_PAYLOAD);
	while (i < NumByte)
	{
		Data[i] = SPI_transferBasic(NOP);		// Maybe NOP
		i++;
	}
	SPI_Stop();
	return Data;
}

void NRF_FlushFifo(uint8_t Fifo)
{
	switch (Fifo)
	{
		case TX:
		SPI_Start();
		SPI_transferBasic(FLUSH_TX);
		SPI_Stop();
		break;
		case RX:
		SPI_Start();
		SPI_transferBasic(FLUSH_RX);
		SPI_Stop();
		break;
	}
}

void NRF_Control(uint8_t State)
{
	switch (State)
	{
		case ACTIVE: 
		CE_HIGH;
		break;
		case STANBY:
		CE_LOW;
		break;
	}
}

void NRF_LoadAckPayload(char * Data, uint8_t NumByte)
{
	uint8_t i = 0;
	SPI_Start();
	SPI_transferBasic(W_ACK_PAYLOAD);
	while (i < NumByte)
	{
		SPI_transferBasic(Data[i]);
		i++;
	}
	SPI_Stop();
}




