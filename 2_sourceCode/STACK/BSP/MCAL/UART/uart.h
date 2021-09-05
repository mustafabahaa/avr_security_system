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
#include "avr.h"
#include "logger.h"
/**************************************************************************/
/*                         Registers                                      */
/**************************************************************************/
#define UCSR0A  0xC0
#define UCSR0B  0xC1
#define UCSR0C  0xC2
#define UBRR0L  0xC4
#define UBRR0H  0xC5
#define UDR0    0xC6

#define UCSR1A  0xC8
#define UCSR1B  0xC9
#define UCSR1C  0xCA
#define UBRR1L  0xCC
#define UBRR1H  0xCD
#define UDR1    0xCE

#define MPCMN   0
#define U2XN    1
#define UPEN    2
#define DORN    3
#define FEN     4
#define UDREN   5
#define TXCN    6
#define RXCN    7

#define TXB8N   0
#define RXB8N   1
#define UCSZN2  2
#define TXENN   3
#define RXENN   4
#define UDRIEN  5
#define TXCIEN  6
#define RXCIEN  7

#define UCPOLN  0
#define UCSZN0  1
#define UCSZN1  2
#define USBSN   3
#define UPMN0   4
#define UPMN1   5
#define UMSELN0 6
#define UMSELN1 7
/**************************************************************************/
/*                               Types                                    */
/**************************************************************************/
typedef enum
{
  UART_STATE_SUCCESS = 1,
  UART_STATE_ERROR,
  UART_STATE_INVALID_STOP_BIT_NUMBER,
  UART_STATE_INVALID_BAUD_RATE,
  UART_STATE_INVALID_PACKET_LENGTH,
  UART_STATE_INVALID_CHANNEL_NUMBER,
  UART_STATE_INVALID_PARITY,
  UART_STATE_INVALID_ENDIAN,
} uart_error_t;

typedef enum
{
  CHANNEL_0 = 1,
  CHANNEL_1 = 2,
} channel_t;

typedef enum
{
  BAUD_2400 = 2400,
  BAUD_4800 = 4800,
  BAUD_9600 = 9600,
} baud_rate_t;

typedef enum
{
  STOP_BIT_1 = 1,
  STOP_BIT_2,
} stop_bit_no_t;

typedef enum
{
  DISABLE = 1,
  ENABLE_EVEN,
  ENABLE_ODD
} parity_t;

typedef enum
{
  BIT_5 = 5,
  BIT_6 = 6,
  BIT_7 = 7,
  BIT_8 = 8,
  BIT_9 = 9,
} packet_length_t;

typedef enum
{
  BIG_ENDIAN = 1,
  LITTLE_ENDIAN,
} endian_type_t;

typedef struct
{
  channel_t channel;
  baud_rate_t baudRate;
  stop_bit_no_t stopBitNo;
  parity_t parity;
  packet_length_t packetLength;
} uart_t;
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
uart_error_t mcal_uart_init(uart_t *uart);

/***************************************************************************
 ** mcal_uart_send_byte()
 **
 ** parameter: uart_t *uart
 ** parameter: u8_t data
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is used to send bytes "data"
 **************************************************************************/
uart_error_t mcal_uart_send_byte(uart_t *uart, u8_t data);

/***************************************************************************
 ** mcal_uart_recieve_byte()
 **
 ** parameter: uart_t *uart
 ** parameter: u8_t* data
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is used to receive bytes "data"
 **************************************************************************/
uart_error_t mcal_uart_recieve_byte(uart_t *uart, u8_t *data);

/***************************************************************************
 ** mcal_uart_send_string()
 **
 ** parameter: uart_t *uart
 ** parameter: const u8_t *str
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is used to to send String
 **************************************************************************/
uart_error_t mcal_uart_send_string(uart_t *uart, const u8_t *str);

/***************************************************************************
 ** mcal_UART_recieveString()
 **
 ** parameter: uart_t *uart
 ** parameter: const u8_t *str
 ** return    : uart_error_t
 ***************************************************************************
 ** this function is  to receive String
 **************************************************************************/
uart_error_t mcal_UART_receive_string(uart_t *uart, u8_t *str);

#endif /* _UART_H_ */
