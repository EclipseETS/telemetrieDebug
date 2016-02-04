/*
 * SERIAL_COM_328P.h
 *
 * Created: 2014-01-16 15:35:32
 *  Author: Fred Lamer
 */ 


#ifndef SERIAL_COM_328P_H_
#define SERIAL_COM_328P_H_

void SERIAL_Init(int64_t baudRate, char parity, int stop_bit, int caracter_size, char clock_polarity);
void SERIAL_SendCaracter(char data);
void SERIAL_SendCaracterLn(char data);
void SERIAL_SendString(char* string);
void SERIAL_SendStringLn(char* string);
void SERIAL_ReturnLine();
char SERIAL_READ();




#endif /* SERIAL_COM_328P_H_ */