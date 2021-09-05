
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

  switch (uart->channel)
  {

  case CHANNEL_0:
  {
    /* U2X = 1 for double transmission speed */
    set_bit(UCSR0A, U2X0);

    set_bit(UCSR0B, RXEN0);
    set_bit(UCSR0B, TXEN0);

    /* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
    /* Initialize baud rate */
    if (uart->baudRate == BAUD_2400 || uart->baudRate == BAUD_4800 || uart->baudRate == BAUD_9600)
    {
      register(UBRR0H) = (((F_CPU / (uart->baudRate * 8UL))) - 1) >> 8;
      register(UBRR0L) = (((F_CPU / (uart->baudRate * 8UL))) - 1);
    }
    else
    {
      error = UART_STATE_INVALID_BAUD_RATE;
    }

    /* Initialize stop bit numbers */
    if (STOP_BIT_1 == uart->stopBitNo)
    {
      clr_bit(UCSR0C, USBS0);
    }
    else if (STOP_BIT_2 == uart->stopBitNo)
    {
      set_bit(UCSR0C, USBS0);
    }
    else
    {
      error = UART_STATE_INVALID_STOP_BIT_NUMBER;
    }

    /* Initialize parity mode */
    if (DISABLE == uart->parity)
    {
      clr_bit(UCSR0C, UPM00);
      clr_bit(UCSR0C, UPM01);
    }
    else if (ENABLE_EVEN == uart->parity)
    {
      clr_bit(UCSR0C, UPM00);
      set_bit(UCSR0C, UPM01);
    }
    else if (ENABLE_ODD == uart->parity)
    {
      set_bit(UCSR0C, UPM00);
      set_bit(UCSR0C, UPM01);
    }
    else
    {
      error = UART_STATE_INVALID_PARITY;
    }

    /* Initialize packet length */
    if (BIT_5 == uart->packetLength)
    {
      clr_bit(UCSR0C, UCSZ00);
      clr_bit(UCSR0C, UCSZ10);
      clr_bit(UCSR0C, UCSZ02);
    }
    else if (BIT_6 == uart->packetLength)
    {
      set_bit(UCSR0C, UCSZ00);
      clr_bit(UCSR0C, UCSZ10);
      clr_bit(UCSR0B, UCSZ02);
    }
    else if (BIT_7 == uart->packetLength)
    {
      clr_bit(UCSR0C, UCSZ00);
      set_bit(UCSR0C, UCSZ10);
      clr_bit(UCSR0B, UCSZ02);
    }
    else if (BIT_8 == uart->packetLength)
    {
      set_bit(UCSR0C, UCSZ00);
      set_bit(UCSR0C, UCSZ10);
      clr_bit(UCSR0B, UCSZ02);
    }
    else if (BIT_9 == uart->packetLength)
    {
      set_bit(UCSR0C, UCSZ00);
      set_bit(UCSR0C, UCSZ10);
      set_bit(UCSR0B, UCSZ02);
    }
    else
    {
      error = UART_STATE_INVALID_PACKET_LENGTH;
    }

    break;
  }

  case CHANNEL_1:
  {
    /* U2X = 1 for double transmission speed */
    set_bit(UCSR1A, U2X1);

    set_bit(UCSR1B, RXEN1);
    set_bit(UCSR1B, TXEN1);

    /* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
    /* Initialize baud rate */
    if (uart->baudRate == BAUD_2400 || uart->baudRate == BAUD_4800 || uart->baudRate == BAUD_9600)
    {
      register(UBRR1H) = (((F_CPU / (uart->baudRate * 8UL))) - 1) >> 8;
      register(UBRR1L) = (((F_CPU / (uart->baudRate * 8UL))) - 1);
    }
    else
    {
      error = UART_STATE_INVALID_BAUD_RATE;
    }

    /* Initialize stop bit numbers */
    if (STOP_BIT_1 == uart->stopBitNo)
    {
      clr_bit(UCSR1C, USBS1);
    }
    else if (STOP_BIT_2 == uart->stopBitNo)
    {
      set_bit(UCSR1C, USBS1);
    }
    else
    {
      error = UART_STATE_INVALID_STOP_BIT_NUMBER;
    }

    /* Initialize parity mode */
    if (DISABLE == uart->parity)
    {
      clr_bit(UCSR1C, UPM10);
      clr_bit(UCSR1C, UPM11);
    }
    else if (ENABLE_EVEN == uart->parity)
    {
      clr_bit(UCSR1C, UPM10);
      set_bit(UCSR1C, UPM11);
    }
    else if (ENABLE_ODD == uart->parity)
    {
      set_bit(UCSR1C, UPM10);
      set_bit(UCSR1C, UPM11);
    }
    else
    {
      error = UART_STATE_INVALID_PARITY;
    }

    /* Initialize packet length */
    if (BIT_5 == uart->packetLength)
    {
      clr_bit(UCSR1C, UCSZ00);
      clr_bit(UCSR1C, UCSZ10);
      clr_bit(UCSR1C, UCSZ02);
    }
    else if (BIT_6 == uart->packetLength)
    {
      set_bit(UCSR1C, UCSZ00);
      clr_bit(UCSR1C, UCSZ10);
      clr_bit(UCSR1B, UCSZ02);
    }
    else if (BIT_7 == uart->packetLength)
    {
      clr_bit(UCSR1C, UCSZ00);
      set_bit(UCSR1C, UCSZ10);
      clr_bit(UCSR1B, UCSZ02);
    }
    else if (BIT_8 == uart->packetLength)
    {
      set_bit(UCSR1C, UCSZ00);
      set_bit(UCSR1C, UCSZ10);
      clr_bit(UCSR1B, UCSZ02);
    }
    else if (BIT_9 == uart->packetLength)
    {
      set_bit(UCSR1C, UCSZ00);
      set_bit(UCSR1C, UCSZ10);
      set_bit(UCSR1B, UCSZ02);
    }
    else
    {
      error = UART_STATE_INVALID_PACKET_LENGTH;
    }

    break;
  }

  default:
  {
    error = UART_STATE_INVALID_CHANNEL_NUMBER;
    break;
  }
  }

  return error;
}

uart_error_t mcal_uart_send_byte(uart_t *uart, const u8_t data)
{
  uart_error_t error = UART_STATE_SUCCESS;

  switch (uart->channel)
  {
  case CHANNEL_0:
  {
    while (bit_is_clr(UCSR0A, UDRE0))
      ;
    register(UDR0) = data;
    break;
  }

  case CHANNEL_1:
    while (bit_is_clr(UCSR1A, UDRE1))
      ;
    register(UDR1) = data;
    break;

  default:
    error = UART_STATE_INVALID_CHANNEL_NUMBER;
    break;
  }

  return error;
}

uart_error_t mcal_uart_recieve_byte(uart_t *uart, u8_t *data)
{
  uart_error_t error = UART_STATE_SUCCESS;

  switch (uart->channel)
  {
  case CHANNEL_0:
  {
    while (bit_is_clr(UCSR0A, RXC0))
      ;
    *data = register(UDR0);
    break;
  }

  case CHANNEL_1:
    while (bit_is_clr(UCSR1A, RXC1))
      ;
    *data = register(UDR1);
    break;

  default:
    error = UART_STATE_INVALID_CHANNEL_NUMBER;
    break;
  }
  return error;
}

uart_error_t mcal_uart_send_string(uart_t *uart, const u8_t *str)
{

  uart_error_t error = UART_STATE_SUCCESS;

  u8_t i = 0;

  while (str[i] != '\0')
  {
    if (UART_STATE_SUCCESS == mcal_uart_send_byte(uart, str[i]))
    {
      i++;
    }
    else
    {
      error = UART_STATE_ERROR;
    }
  }

  /*send the null of the string after finish */
  mcal_uart_send_byte(uart,'\0');

  return error;
}

uart_error_t mcal_UART_receive_string(uart_t *uart, u8_t *str)
{
  uart_error_t error = UART_STATE_SUCCESS;

  u8_t i = 0;

  while (str[i] != '\0')
  {
    if (UART_STATE_SUCCESS == mcal_uart_recieve_byte(uart, &str[i]))
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
