/*
 * USART.c
 *
 * Created: 4/20/2020 11:57:28 AM
 *  Author:  Khaled Osama Eraky
 */ 


#include "USART.h"

#define PASS 0

void	UART_init(void)
{
	UBRRL = (uint8_t)(UBRR);
	UBRRH = (uint8_t)((UBRR)>>8);
	UCSRB |= (1<<3) | (1<<4);            /*Rx and Tx Enable*/
	UCSRC |= (1<<7) | (1<<2) | (1<<1);   /*select UCSRC and set the char size with 8 bit*/
}

void	UART_sendByte(uint8_t Data)
{
	while((UCSRA & (1<<5)) == 0)
	{
		
	}
	UDR = Data;
}

uint8_t UART_ReadByte(void)
{
	while((UCSRA & (1<<7)) == 0)
	{
	}
	return UDR;
}   

uint8_t UART_ReadString(uint8_t*RecivedPacket)
{
	uint8_t i =0;
	while(i<36)
	{
     *(RecivedPacket+i)= UART_ReadByte();
	 if (*(RecivedPacket+1) == '*')
	 {
		 break;
	 }
		i++;			
	}
			
	return PASS;
}
void UART_Send_string(uint8_t string[])
{
	int i=0;
	while ( string[i] > 0)
	UART_sendByte(string[i++]);
}