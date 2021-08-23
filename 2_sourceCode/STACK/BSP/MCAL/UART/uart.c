
/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** uart.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "uart.h"
/**************************************************************************/
/*                     Functions Implementation                           */
/**************************************************************************/
uart_error_t mcal_UART_init(uart_t* uart)
{
	uart_error_t error = UART_STATE_SUCCESS;

	/* U2X = 1 for double transmission speed */
	set_bit(UCSRA,U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	set_bit(UCSRB,RXEN);
	set_bit(UCSRB,TXEN);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	set_bit(UCSRC,URSEL);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	/* Initialize baud rate */
	if (uart->baudRate == BAUD_2400 || uart->baudRate == BAUD_4800 || uart->baudRate == BAUD_9600)
	{
		register(UBRRH) = (((F_CPU / (uart->baudRate * 8UL))) - 1)>>8;
		register(UBRRL) = (((F_CPU / (uart->baudRate * 8UL))) - 1);
	}
	else
	{
		error = UART_STATE_INVALID_BAUD_RATE;
	}


	/* Initialize stop bit numbers */
	if (STOP_BIT_1 == uart->stopBitNo)
	{
		clr_bit(UCSRC,USBS);
	}
	else if (STOP_BIT_2 == uart->stopBitNo)
	{
		set_bit(UCSRC,USBS);
	}
	else
	{
		error = UART_STATE_INVALID_STOP_BIT_NUMBER;
	}

	/* Initialize parity mode */
	if (DISABLE == uart->parity)
	{
		clr_bit(UCSRC,UPM0);
		clr_bit(UCSRC,UPM1);
	}
	else if (ENABLE_EVEN == uart->parity)
	{
		clr_bit(UCSRC,UPM0);
		set_bit(UCSRC,UPM1);
	}
	else if (ENABLE_ODD == uart->parity)
	{
		set_bit(UCSRC,UPM0);
		set_bit(UCSRC,UPM1);
	}
	else
	{
		error = UART_STATE_INVALID_PARITY;
	}

	/* Initialize packet length */
	if (BIT_5 == uart->packetLength)
	{
		clr_bit(UCSRC,UCSZ0);
		clr_bit(UCSRC,UCSZ1);
		clr_bit(UCSRB,UCSZ2);
	}
	else if (BIT_6 == uart->packetLength)
	{
		set_bit(UCSRC,UCSZ0);
		clr_bit(UCSRC,UCSZ1);
		clr_bit(UCSRB,UCSZ2);
	}
	else if (BIT_7 == uart->packetLength)
	{
		clr_bit(UCSRC,UCSZ0);
		set_bit(UCSRC,UCSZ1);
		clr_bit(UCSRB,UCSZ2);
	}
	else if (BIT_8 == uart->packetLength)
	{
		set_bit(UCSRC,UCSZ0);
		set_bit(UCSRC,UCSZ1);
		clr_bit(UCSRB,UCSZ2);
	}
	else if (BIT_9 == uart->packetLength)
	{
		set_bit(UCSRC,UCSZ0);
		set_bit(UCSRC,UCSZ1);
		set_bit(UCSRB,UCSZ2);
	}
	else
	{
		error = UART_STATE_INVALID_PACKET_LENGTH;
	}
	return error;
}

uart_error_t mcal_UART_sendByte(const u8_t data)
{
	uart_error_t error = UART_STATE_SUCCESS;

	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one */
	while(bit_is_clr(UCSRA,UDRE)){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now */
	register(UDR) = data;

	/************************* Another Method *************************
	UDR = data;
	while(bit_is_clr(UCSRA,TXC)){}
	// Wait until the transimission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	 *******************************************************************/

	return error;
}

uart_error_t mcal_UART_recieveByte(u8_t* data)
{
	uart_error_t error = UART_STATE_SUCCESS;

	/* RXC flag is set when the UART receive data so wait until this
	 * flag is set to one */
	while(bit_is_clr(UCSRA,RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag
	   will be cleared after read this data */
	*data = register(UDR);

	return error;
}

uart_error_t mcal_UART_sendString(const u8_t *str)
{

	uart_error_t error = UART_STATE_SUCCESS;

	u8_t i = 0;

	while(str[i] != '\0')
	{
		if(UART_STATE_SUCCESS == mcal_UART_sendByte(str[i]))
		{
			i++;
		}
		else
		{
			error = UART_STATE_ERROR;
		}
	}

  /*send the null of the string after finish */
  mcal_UART_sendByte('\0');

	return error;
}

uart_error_t mcal_UART_receiveString(u8_t *str)
{
  uart_error_t error = UART_STATE_SUCCESS;

  u8_t i = 0;

  while (str[i] != '\0')
  {
    if (UART_STATE_SUCCESS == mcal_UART_recieveByte(&str[i]))
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
