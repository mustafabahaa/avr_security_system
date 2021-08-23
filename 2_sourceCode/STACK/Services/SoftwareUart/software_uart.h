 
 /* --------------------------------------------------------*
 ** Copyright (C) 2016 Decrypt - All Rights Reserved You may
 ** use, distribute and modify this code under the terms and
 ** conditions of the Decrypt Team, You should have received
 ** a copy of the footbutton project license with this  file  
 ** If not, please
 ** write to: 
 ** or visit :
 **
 ** softuart.h
 ** This file contains functions prototype for softuart.c 
 ** also specifies the required enums and structures needed
 **
 ** Author: <Decrypt Technical Team>
 ** -------------------------------------------------------*/ 

 #ifndef SOFTUART_H_
 #define SOFTUART_H_

 
 /* Custom-libraries needed for this module*/
 #include "types.h"
 #include "atmega32.h"
 #include "delay.h"

  /* Choose PORT and pin configuration */
 #define UART_SOFT_DDR  (BASE_B + OFFSET_DIR)
 #define UART_SOFT_PORT (BASE_B + OFFSET_PORT)
 #define UART_SOFT_PIN  7
 
 /* Choose required baud rate */
 #define UART_SOFT_BAUD 9600UL
 
 /* Choose Data length */
 #define DATA_LENGTH 8

 /* Please don't modify this values*/
 #define UART_SOFT_DELAY_US (int) (F_CPU/((float) UART_SOFT_BAUD)) /1000
 
 
 /* -- softuartInit ---------------------------------------------**
 ** led_intialization()
 **
 ** paramters : void 
 ** return    : void 
 **
 ** -- implementation ---------------------------------------
 ** this function intialize uart configurations specifed in 
 ** softuartconfig.h file such as baudrate and clock
 ** -------------------------------------------------------*/
 void softuartInit();
 
 
 
 /* -- Global ---------------------------------------------**
 ** softUartSendChar()
 **
 ** paramters : u8_t txData 
 ** return    : void 
 **
 ** -- implementation ---------------------------------------
 ** this function send u8_t with uart bit banging technique
 ** -------------------------------------------------------*/
 void softUartSendChar (u8_t txData);
 
 
 /* -- Global ---------------------------------------------**
 ** softUartSendString()
 **
 ** paramters : *txData 
 ** return    : void 
 **
 ** -- implementation ---------------------------------------
 ** this function send string with uart bit banging technique
 ** -------------------------------------------------------*/
 void softUartSendString (u8_t *txData);



 #endif /* SOFTUART_H_ */
 
 
 
 
 
 
 
 
 
 