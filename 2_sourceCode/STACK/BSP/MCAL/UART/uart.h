/***************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** uart.h
 **************************************************************************/
#ifndef _UART_H_
#define _UART_H_
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "types.h"
#include "atmega32.h"
#include "logger.h"
/**************************************************************************/
/*                               Types                                    */
/**************************************************************************/
typedef enum
{
	UART_STATE_SUCCESS=1,
	UART_STATE_ERROR,
	UART_STATE_INVALID_STOP_BIT_NUMBER,
	UART_STATE_INVALID_BAUD_RATE,
	UART_STATE_INVALID_PACKET_LENGTH,
  UART_STATE_INVALID_PARITY,
	UART_STATE_INVALID_ENDIAN,
} uart_error_t;

typedef enum
{
	BAUD_2400 = 2400,
	BAUD_4800 = 4800,
	BAUD_9600 = 9600,
}baud_rate_t;

typedef enum
{
	STOP_BIT_1=1,
	STOP_BIT_2,
}stop_bit_no_t;

typedef enum
{
	DISABLE=1,
	ENABLE_EVEN,
	ENABLE_ODD
}parity_t;

typedef enum
{
	BIT_5=5,
	BIT_6=6,
	BIT_7=7,
	BIT_8=8,
	BIT_9=9,
}packet_length_t;

typedef enum
{
	BIG_ENDIAN=1,
	LITTLE_ENDIAN,
}endian_type_t;

typedef struct
{
	baud_rate_t baudRate;
	stop_bit_no_t stopBitNo;
	parity_t parity;
	packet_length_t packetLength;
}uart_t;
/**************************************************************************/
/*                           Public Functions                             */
/**************************************************************************
 ** mcal_uart_init()
 **
 ** parameter: uart_t* uart
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for uart
 **************************************************************************/
uart_error_t mcal_uart_init(uart_t* uart);


/***************************************************************************
 ** mcal_uart_send_byte()
 **
 ** parameter: u8_t data
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is used to send bytes "data"
 **************************************************************************/
uart_error_t mcal_uart_send_byte(u8_t data);

/***************************************************************************
 ** mcal_uart_recieve_byte()
 **
 ** parameter: u8_t* data
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is used to receive bytes "data"
 **************************************************************************/
uart_error_t mcal_uart_recieve_byte(u8_t* data);

/***************************************************************************
 ** mcal_uart_send_string()
 **
 ** parameter: const u8_t *str
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is used to to send String
 **************************************************************************/
uart_error_t mcal_uart_send_string(const u8_t *str);


/***************************************************************************
 ** mcal_UART_recieveString()
 **
 ** parameter: const u8_t *str
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is  to receive String
 **************************************************************************/
uart_error_t mcal_UART_receive_string (u8_t *str);

#endif /* _UART_H_ */
