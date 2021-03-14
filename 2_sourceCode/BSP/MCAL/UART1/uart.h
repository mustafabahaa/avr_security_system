/*
 * uart.h
 *
 *  Created on: Mar 11, 2021
 *      Author: Lenovo
 */

#ifndef MCAL_UART1_H_
#define MCAL_UART1_H_

#include "./../../INCLUDE/common_macros.h"
#include "./../../INCLUDE/micro_config.h"
#include"./../../INCLUDE/std_types.h"



/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600


/**************************** Prototypes*************************/

/* UART initializing */
void UART_init(void);

/* UART function to send bytes "data" */
void UART_sendByte(uint8 data);

/* UART function to receive bytes "data" */
uint8 UART_recieveByte();

/* UART function to send String */
void UART_sendString(const uint8 *Str);

/* UART function to receive String */
void UART_recieveString (uint8 *Str);

#endif /* MCAL_UART1_H_ */
