/*
 * SPI_COM_328P.h
 *
 * Created: 2014-01-16 16:09:35
 *  Author: Fred Lamer
 */ 


#ifndef SPI_COM_328P_H_
#define SPI_COM_328P_H_

#define		MISO	4
#define		MOSI	3
#define		SCK		5
#define		SS		2

#define		SS_PORT_DIR		DDRB
#define		SS_PORT			PORTB
#define		SS				2
#define		SS_HIGH			SS_PORT |= (1<<SS)
#define		SS_LOW			SS_PORT &= ~(1<<SS);


// THE SS pin must be held high and then swtich to low for transmission, cannot be held low

void SPI_InitSlave(int data_mode, int data_order);
char SPI_SlaveReceive();
void SPI_InitMaster(int data_mode, int data_order, int clock_divider, char SS_port, int SS_pin);
void SPI_MasterSend(char data, char SS_port, int SS_pin);
char SPI_transfer(char data, char SS_port, int SS_pin);
void SPI_SlaveResponse(char response);
char SPI_transferBasic(char data);
void SPI_MasterSendBasic(char data);
void SPI_Start();
void SPI_Stop();



#endif /* SPI_COM_328P_H_ */