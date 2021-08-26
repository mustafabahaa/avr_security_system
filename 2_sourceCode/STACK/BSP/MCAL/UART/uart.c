
/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** uart.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "uart.h"
/*************************************************************************/
/*                          Global Variables                             */
/*************************************************************************/
static u8_t *TAG = (u8_t *)"UART";
/**************************************************************************/
/*                     Functions Implementation                           */
/**************************************************************************/
uart_error_t mcal_uart_init(uart_t *uart)
{
  uart_error_t error = UART_STATE_SUCCESS;

  /* U2X = 1 for double transmission speed */
  set_bit(UCSRA, U2X);
  logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"double transimission speed is enabled");

  set_bit(UCSRB, RXEN);
  set_bit(UCSRB, TXEN);
  logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"Transmitter and Receiver are enabled");

  /* The URSEL must be zero when writing the UBRRH */
  set_bit(UCSRC, URSEL);

  /* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
  /* Initialize baud rate */
  if (uart->baudRate == BAUD_2400 || uart->baudRate == BAUD_4800 || uart->baudRate == BAUD_9600)
  {
    register(UBRRH) = (((F_CPU / (uart->baudRate * 8UL))) - 1) >> 8;
    register(UBRRL) = (((F_CPU / (uart->baudRate * 8UL))) - 1);
    logger_write_debug_println_with_variable(LOG_MCAL, TAG, (u8_t *)"configured baud rate", uart->baudRate);
  }
  else
  {
    error = UART_STATE_INVALID_BAUD_RATE;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalid baud rate");
  }

  /* Initialize stop bit numbers */
  if (STOP_BIT_1 == uart->stopBitNo)
  {
    clr_bit(UCSRC, USBS);
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured with 1 stop bit");
  }
  else if (STOP_BIT_2 == uart->stopBitNo)
  {
    set_bit(UCSRC, USBS);
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured with 2 stop bit");
  }
  else
  {
    error = UART_STATE_INVALID_STOP_BIT_NUMBER;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalid stop bits number support only 1 or 2");
  }

  /* Initialize parity mode */
  if (DISABLE == uart->parity)
  {
    clr_bit(UCSRC, UPM0);
    clr_bit(UCSRC, UPM1);
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured to disable parity");
  }
  else if (ENABLE_EVEN == uart->parity)
  {
    clr_bit(UCSRC, UPM0);
    set_bit(UCSRC, UPM1);
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured to even parity");
  }
  else if (ENABLE_ODD == uart->parity)
  {
    set_bit(UCSRC, UPM0);
    set_bit(UCSRC, UPM1);
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured to odd parity");
  }
  else
  {
    error = UART_STATE_INVALID_PARITY;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalid parity mode");
  }

  /* Initialize packet length */
  if (BIT_5 == uart->packetLength)
  {
    clr_bit(UCSRC, UCSZ0);
    clr_bit(UCSRC, UCSZ1);
    clr_bit(UCSRB, UCSZ2);
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured to to 5 bits packet length");
  }
  else if (BIT_6 == uart->packetLength)
  {
    set_bit(UCSRC, UCSZ0);
    clr_bit(UCSRC, UCSZ1);
    clr_bit(UCSRB, UCSZ2);
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured to to 6 bits packet length");
  }
  else if (BIT_7 == uart->packetLength)
  {
    clr_bit(UCSRC, UCSZ0);
    set_bit(UCSRC, UCSZ1);
    clr_bit(UCSRB, UCSZ2);
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured to to 7 bits packet length");
  }
  else if (BIT_8 == uart->packetLength)
  {
    set_bit(UCSRC, UCSZ0);
    set_bit(UCSRC, UCSZ1);
    clr_bit(UCSRB, UCSZ2);
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured to to 8 bits packet length");
  }
  else if (BIT_9 == uart->packetLength)
  {
    set_bit(UCSRC, UCSZ0);
    set_bit(UCSRC, UCSZ1);
    set_bit(UCSRB, UCSZ2);
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured to to 9 bits packet length");
  }
  else
  {
    error = UART_STATE_INVALID_PACKET_LENGTH;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalid packet length");
  }
  return error;
}

uart_error_t mcal_uart_send_byte(const u8_t data)
{
  uart_error_t error = UART_STATE_SUCCESS;

  /* UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one */
  while (bit_is_clr(UCSRA, UDRE))
  {
  }
  /* Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now */
  register(UDR) = data;

  return error;
}

uart_error_t mcal_uart_recieve_byte(u8_t *data)
{
  uart_error_t error = UART_STATE_SUCCESS;

  /* RXC flag is set when the UART receive data so wait until this
	 * flag is set to one */
  while (bit_is_clr(UCSRA, RXC))
  {
  }
  /* Read the received data from the Rx buffer (UDR) and the RXC flag
	   will be cleared after read this data */
  *data = register(UDR);

  return error;
}

uart_error_t mcal_uart_send_string(const u8_t *str)
{

  uart_error_t error = UART_STATE_SUCCESS;

  u8_t i = 0;

  while (str[i] != '\0')
  {
    if (UART_STATE_SUCCESS == mcal_uart_send_byte(str[i]))
    {
      i++;
    }
    else
    {
      error = UART_STATE_ERROR;
    }
  }

  /*send the null of the string after finish */
  mcal_uart_send_byte('\0');

  return error;
}

uart_error_t mcal_UART_receive_string(u8_t *str)
{
  uart_error_t error = UART_STATE_SUCCESS;

  u8_t i = 0;

  while (str[i] != '\0')
  {
    if (UART_STATE_SUCCESS == mcal_uart_recieve_byte(&str[i]))
    {
      i++;
    }
    else
    {
      error = UART_STATE_ERROR;
    }
  }
  return error;
}
