/*
 * NRF24L01.h
 *
 * Created: 2014-01-28 11:51:32
 *  Author: Fred Lamer
 */ 

#define		SS_PORT_DIR		DDRB
#define		SS_PORT			PORTB
#define		SS				2
#define		SS_HIGH			SS_PORT |= (1<<SS)
#define		SS_LOW			SS_PORT &= ~(1<<SS);

#define		CE_PORT_DIR		DDRB
#define		CE_PORT			PORTB
#define		CE				1
#define		CE_LOW			CE_PORT &= ~(1<<CE);
#define		CE_HIGH			CE_PORT |= (1<<CE);

#define		ACTIVE			1
#define		STANBY			0

#define		TX				0
#define		RX				1

#define		HIGH			1
#define		LOW				0

// define the SPI commands

#define		R_REGISTER				0b00000000
#define		W_REGISTER				0b00100000
#define		R_RX_PAYLOAD			0b01100001
#define		W_TX_PAYLOAD			0b10100000
#define		FLUSH_TX				0b11100001
#define		FLUSH_RX				0b11100010
#define		REUSE_TX_PL				0b11100011
#define		R_RX_PL_WID				0b01100000
#define		W_ACK_PAYLOAD			0b10101000
#define		W_TX_PAYLOAD_NO_ACK		0b10110000
#define		NOP						0b11111111
/*		*/


//defines of register map
#define		CONFIG			0x00
#define		EN_AA			0x01
#define		EN_RXADDR		0x02
#define		SETUP_AW		0x03
#define		SETUP_RETR		0x04
#define		RF_CH			0x05
#define		RF_SETUP		0x06
#define		STATUS			0x07
#define		OBSERVE_TX		0x08
#define		RPD				0x09
#define		RX_ADDR_P0		0x0A
#define		RX_ADDR_P1		0x0B
#define		RX_ADDR_P2		0x0C
#define		RX_ADDR_P3		0x0D
#define		RX_ADDR_P4		0x0E
#define		RX_ADDR_P5		0x0F
#define		TX_ADDR			0x10
#define		RX_PW_P0		0x11
#define		RX_PW_P1		0x12
#define		RX_PW_P2		0x13
#define		RX_PW_P3		0x14
#define		RX_PW_P4		0x15
#define		RX_PW_P5		0x16
#define		FIFO_STATUS		0x17
#define		DYNPD			0x1C
#define		FEATURE			0x1D
/*		*/

//  Definitions of the bits
// CONFIG
#define		MASK_RX_DR				6
#define		MASK_TX_DS				5
#define		MASK_MAX_RT				4
#define		EN_CRC					3
#define		CRCO					2
#define		PWR_UP					1
#define		PRIM_RX					0
/*		*/

// EN_AA
#define		ENAA_P5					5
#define		ENAA_P4					4
#define		ENAA_P3					3
#define		ENAA_P2					2
#define		ENAA_P1					1
#define		ENAA_P0					0
/*		*/

//EN_RXADDR
#define		ERX_P5					5
#define		ERX_P4					4
#define		ERX_P3					3
#define		ERX_P2					2
#define		ERX_P1					1
#define		ERX_P0					0
/*		*/

//SETUP_AW	
#define		AW						0		// 1:0
/*		*/

//SETUP_RETR
#define		ARD						4		// 7:4
#define		ARC						0		// 3:0
/*		*/


// RF_SETUP
#define		CONT_WAVE				7
#define		RF_DR_LOW				5
#define		PLL_LOCK				4
#define		RF_DR_HIGH				3
#define		RF_PWR					1		// 2:1
/*		*/

// STATUS	
#define		RX_DR					6
#define		TX_DS					5
#define		MAX_RT					4
#define		RX_P_NO					1		// 3:1
#define		TX_FULL					0
/*		*/

// OBSERVE_TX
#define		PLOS_CNT				4		// 7:4
#define		ARC_CNT					0		// 3:0
/*		*/


// FIFO_STATUS
#define		TX_REUSE				6
//#define		TX_FULL					5
#define		TX_EMPTY				4
#define		RX_FULL					1
#define		RX_EMPTY				0
/*		*/

// DYNPD
#define		DPL_P5					5
#define		DPL_P4					4
#define		DPL_P3					3
#define		DPL_P2					2
#define		DPL_P1					1
#define		DPL_P0					0
/*		*/

// FEATURE
#define		EN_DPL					2				
#define		EN_ACK_PAY				1
#define		EN_DYN_ACK				0
/*		*/

/*	Function to write in any NRF24L01+ register		*/
void NRF_WriteRegister(uint8_t Register, uint8_t Data);

/*	Function to read any register in NRF24L01+		*/
uint8_t NRF_ReadRegister(uint8_t Register);

/*	Function to read the STATUS register in the NRF24L01+		*/
uint8_t NRF_ReadStatusRegister();

/*	Function to display the STATUS register of the NRF24L01+ in the serial monitor	*/
void NRF_PrintStatusRegister();

/*	Function to display any register of the NRF24L01+ in the serial monitor		*/
void NRF_PrintRegister(uint8_t Register);

/*	Function to write the address in TX_ADDR register	*/
void NRF_WriteTXADDR(uint8_t Adress0, uint8_t Adress1, uint8_t Adress2, uint8_t Adress3, uint8_t Adress4);

/*	Function to display the TX_ADDR	 REGISTER on the serial monitor	*/
void NRF_PrintTXADDR();

/*	Function to write the address in RX_ADDR_P0 register	*/
void NRF_WriteRXADDR_P0(uint8_t Adress0, uint8_t Adress1, uint8_t Adress2, uint8_t Adress3, uint8_t Adress4);

/*	Function to display the RX_ADDR_P0 address in the serial monitor	*/
void NRF_PrintRXADDR_P0();

/*	Function to write the address in the RX_ADDR_P1 register	*/
void NRF_WriteRXADDR_P1(uint8_t Adress0, uint8_t Adress1, uint8_t Adress2, uint8_t Adress3, uint8_t Adress4);

/*	Function to display the RX_ADDR_P1 register on the serial monitor	*/
void NRF_PrintRXADDR_P1();

/*	Function to set the NRF24L01+ module as TX		*/
void NRF_SET_PTX();

/*	Function to set the NRF24L01+ module as RX		*/
void NRF_SET_PRX();

/*	Function to activate the transmission (pulse) on the NRF24L01+		*/
void NRF_ActivateTransmission();

/*	Function to load the wanted lenght of data in the TX_PAYLOAD	*/
void NRF_LoadTXPayload(char* Data, uint8_t NumByte);

/*	Function to read the wanted number of bytes in the RX_PAYLOAD	*/
char * NRF_ReadRXPayload(uint8_t NumByte);

/*	Function to start listenning when in PRX mode	*/
void NRF_Listen();

/*	Function to Flush the wanted FIFO	*/
void NRF_FlushFifo(uint8_t Fifo);

/*	Function to set the STATE of the NRF24L01+		*/
void NRF_Control(uint8_t State);

void NRF_WriteTXADDR3byte(uint8_t Adress0, uint8_t Adress1, uint8_t Adress2);

void NRF_WriteRXADDR_P03byte(uint8_t Adress0, uint8_t Adress1, uint8_t Adress2);

/*	Function to load data in the ack payload	*/	//PRX device only
void NRF_LoadAckPayload(char * Data, uint8_t NumByte);

