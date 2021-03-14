/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** uart.h
 **************************************************************************/
#ifndef MCAL_UART_H_
#define MCAL_UART_H_
/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "./../../includes/types.h"
#include "./../../includes/atmega32.h"
/*************************************************************************/
/*                              Macros                                   */
/*************************************************************************/

#define UCSRA 0x2B
#define MPCM    0
#define U2X     1
#define PE      2
#define DOR     3
#define FE      4
#define UDRE    5
#define TXC     6
#define RXC     7

#define UCSRB 0x2A
#define TXB8    0
#define RXB8    1
#define UCSZ2   2
#define TXEN    3
#define RXEN    4
#define UDRIE   5
#define TXCIE   6
#define RXCIE   7

#define UCSRC 0x40
#define UCPOL   0
#define UCSZ0   1
#define UCSZ1   2
#define USBS    3
#define UPM0    4
#define UPM1    5
#define UMSEL   6
#define URSEL   7

#define UBRRH   0x40
#define URSEL   7

#define UBRRL   0x29

#define UDR 0x2c


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
uart_error_t mcal_UART_recieveString (u8_t *str);

#endif /* MCAL_UART_H_ */
