/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** uart.h
 **************************************************************************/
#ifndef _UART_H_
#define _UART_H_
/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "./../../includes/types.h"
#include "./../../includes/atmega16.h"
/*************************************************************************/
/*                              Macros                                   */
/*************************************************************************/
/* UART Driver Baud Rate */
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)
/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/
typedef enum
{
	UART_STATE_SUCCESS,
	UART_STATE_ERROR,
} uart_error_t;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** mcal_UART_init()
 **
 ** parameters: void
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for uart
 **************************************************************************/
uart_error_t mcal_UART_init(void);


/**************************************************************************
 ** mcal_UART_sendByte()
 **
 ** parameters: u8_t data
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is used to send bytes "data"
 **************************************************************************/
uart_error_t mcal_UART_sendByte(u8_t data);

/**************************************************************************
 ** mcal_UART_recieveByte()
 **
 ** parameters: u8_t* data
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is used to receive bytes "data"
 **************************************************************************/
uart_error_t mcal_UART_recieveByte(u8_t* data);

/**************************************************************************
 ** mcal_UART_sendString()
 **
 ** parameters: const u8_t *str
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is used to to send String
 **************************************************************************/
uart_error_t mcal_UART_sendString(const u8_t *str);


/**************************************************************************
 ** mcal_UART_recieveString()
 **
 ** parameters: const u8_t *str
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is  to receive String
 **************************************************************************/
uart_error_t mcal_UART_receiveString (u8_t *str);

#endif /* _UART_H_ */
