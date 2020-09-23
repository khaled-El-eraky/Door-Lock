/*
 * USART.h
 *
 * Created: 4/20/2020 11:57:04 AM
 *  Author: Khaled Osama Eraky
 */

#ifndef USART_H_
#define USART_H_

#include "Microcontroller_config.h"
#include "Macros.h"
#include "StdTypes.h"

#define UBRR   F_CPU/16/Buad_Rate-1
#define PASS 0

void	UART_init(void);
void	UART_sendByte(uint8_t Data);
void    UART_Send_string(uint8_t string[]);
uint8_t UART_ReadByte(void);
uint8_t UART_ReadString(uint8_t*RecivedPacket);



#endif /* USART_H_ */