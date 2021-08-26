/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** soft_uart.h
 **************************************************************************/
 #ifndef SOFTUART_H_
 #define SOFTUART_H_
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
 #include "types.h"
 #include "atmega32.h"
 #include "delay.h"
 #include "timer.h"
 #include "gpio.h"
/**************************************************************************/
/*                              Macros                                    */
/**************************************************************************/
 /* Choose required baud rate */
 #define UART_SOFT_BAUD 9600UL

 /* Please don't modify this values , delay is in milli-seconds */
 #define UART_SOFT_DELAY_US (F_CPU / UART_SOFT_BAUD)
/**************************************************************************/
/*                              Types                                     */
/**************************************************************************/
typedef enum
{
	SOFT_BAUD_2400 = 2400,
	SOFT_BAUD_4800 = 4800,
	SOFT_BAUD_9600 = 9600,
} soft_baud_rate_t;

typedef enum 
{
  BUSY=1,
  READY
} transmission_status_t;

typedef struct
{
  soft_baud_rate_t baud;
  transmission_status_t status;
  u8_t base;
  u8_t txPin;
} soft_uart_t;
/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** service_soft_uart_init()
 **
 ** parameter: soft_uart_t *soft_uart_t
 ** return    : void
 ***************************************************************************
 ** this function intialize software uart configurations
 **************************************************************************/
 void service_soft_uart_init(soft_uart_t *soft_uart_t);
 
 
 /**************************************************************************
 ** service_soft_uart_send_byte()
 **
 ** parameter: u8_t txData
 ** return    : void
 ***************************************************************************
 ** this function send u8_t with uart bit banging technique
 **************************************************************************/
 void service_soft_uart_send_byte (u8_t txData);
 
  /**************************************************************************
 ** service_soft_uart_send_string()
 **
 ** parameter: u8_t txData
 ** return    : void
 ***************************************************************************
 ** this function send string with uart bit banging technique
 **************************************************************************/
 void service_soft_uart_send_string (u8_t *txData);

 #endif /* SOFTUART_H_ */
 
 
 
 
 
 
 
 
 
 