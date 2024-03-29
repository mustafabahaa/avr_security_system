/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** MessagingUnit.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "MessagingUnit.h"
#include "uart.h"
/*************************************************************************/
/*                     Static Functions Prototypes                       */
/*************************************************************************/

/**************************************************************************
 ** ()
 **
 ** parameter: void
 ** return    : system_error_t
 **************************************************************************
 **
 *************************************************************************/

/*************************************************************************/
/*                          Global Variables                             */
/*************************************************************************/
static u8_t *TAG = (u8_t *)"MESSAGING_UNIT";
static uart_t uart;
/*************************************************************************/

/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

system_error_t ms_manager_init()
{
  system_error_t error = SYSTEM_SUCCESS;

  uart.baudRate = BAUD_9600;
  uart.packetLength = BIT_8;
  uart.stopBitNo = STOP_BIT_1;
  uart.parity = DISABLE;
  uart.channel = CHANNEL_0;

  if (UART_STATE_SUCCESS != mcal_uart_init(&uart))
  {
    error = SYSTEM_FAIL;
    logger_write_error_println(LOG_MANAGERS, TAG, (u8_t *)"Failed to initialize messaging Unit");
  }
  else
  {
    logger_write_debug_println(LOG_MANAGERS, TAG, (u8_t *)"Succeed to initialize messaging Unit");
  }
  return error;
}

system_error_t ms_manager_send_signal(u8_t data)
{
  system_error_t error = SYSTEM_SUCCESS;

  if (UART_STATE_SUCCESS != mcal_uart_send_byte(&uart, data))
  {
    error = SYSTEM_FAIL;
    logger_write_error_println(LOG_MANAGERS, TAG, (u8_t *)"Failed to send data");
  }
  else
  {
    logger_write_debug_println(LOG_MANAGERS, TAG, (u8_t *)"Succeed to send data");
  }

  return error;
}

system_error_t ms_manager_send_password(u8_t *data)
{
  system_error_t error = SYSTEM_SUCCESS;

  for (int i = 0; i < PASSWORD_LENGTH; i++)
  {
    if (UART_STATE_SUCCESS != mcal_uart_send_byte(&uart, data[i]))
    {
      error = SYSTEM_FAIL;
      logger_write_error_println(LOG_MANAGERS, TAG, (u8_t *)"Failed to send string data");
    }
    else
    {
      logger_write_debug_println(LOG_MANAGERS, TAG, (u8_t *)"Succeed to send string data");
    }
  }
  return error;
}

system_error_t ms_manager_receive_signal(u8_t *data)
{
  system_error_t error = SYSTEM_SUCCESS;

  if (UART_STATE_SUCCESS != mcal_uart_recieve_byte(&uart, data))
  {
    error = SYSTEM_FAIL;
    logger_write_error_println(LOG_MANAGERS, TAG, (u8_t *)"Failed to receive data");
  }
  else
  {
    logger_write_debug_println(LOG_MANAGERS, TAG, (u8_t *)"Succeed to receive data");
  }

  return error;
}

system_error_t ms_manager_receive_password(u8_t *data)
{
  system_error_t error = SYSTEM_SUCCESS;

  for (int i = 0; i < PASSWORD_LENGTH; i++)
  {
    if (UART_STATE_SUCCESS != mcal_uart_recieve_byte(&uart, data))
    {
      error = SYSTEM_FAIL;
      logger_write_error_println(LOG_MANAGERS, TAG, (u8_t *)"Failed to receive string data");
    }
    else
    {
      logger_write_debug_println(LOG_MANAGERS, TAG, (u8_t *)"Succeed to receive string data");
    }
  }

  return error;
}
