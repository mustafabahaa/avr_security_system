
/* --------------------------------------------------------*
 ** Copyright (C) 2016 Decrypt - All Rights Reserved You may
 ** use, distribute and modify this code under the terms and
 ** conditions of the Decrypt Team, You should have received
 ** a copy of the footbutton project license with this  file  
 ** If not, please
 ** write to: 
 ** or visit :
 **
 ** softuart.c
 ** This file function implmenations for softuart.h file
 **
 ** Author: <Decrypt Technical Team>
 ** -------------------------------------------------------*/
/* --------------------------------------------------------*
 ** Copyright (C) 2016 Decrypt - All Rights Reserved You may
 ** use, distribute and modify this code under the terms and
 ** conditions of the Decrypt Team, You should have received
 ** a copy of the footbutton project license with this  file  
 ** If not, please
 ** write to: 
 ** or visit :
 **
 ** softuart.c
 ** This file function implmenations for softuart.h file
 **
 ** Author: <Decrypt Technical Team>
 ** -------------------------------------------------------*/

/* Custom-libraries needed for this module*/
#include "software_uart.h"

volatile u16_t tx_shift_reg = 0;

void __vector_10(void) __attribute__((signal, used, externally_visible));

void softuartInit()
{

  setGlobalInterrupt;
 // set up timer with no prescaling
  register(TCCR0) |= (1 << CS00);

  /*Choose CTC Mode of timer */
	register(TCCR0) &= ~(1<<WGM00);
	register(TCCR0) |=  (1<<WGM01);
  
  // initialize counter
  register(TCNT0) = 0;
  register(OCR0) = 103;

  /* initialize TX pin */
  set_bit(UART_SOFT_DDR, UART_SOFT_PIN);
  set_bit(UART_SOFT_PORT, UART_SOFT_PIN);
}
//#define delay 104
#define delay UART_SOFT_DELAY_US
void softUartSendChar(u8_t txData)
{
  #if 0
  /* Send Start Bit */
  clr_bit(UART_SOFT_PORT, UART_SOFT_PIN);

  /* delay to send the bit */
  delay_ms(delay);

  /* send data bits in 8-bit mode configurations*/
  for (u8_t i = 0; i < DATA_LENGTH; i++)
  {
    /* if 1 is needed to be transmitted then it will be
           true in the following condition and it  will set
		   the pin in order to send that one , else if zero
		   needed to be transmitted it will give  false  if
		   it anded with 1 hence a zero will be transmitted
		*/

    if (txData & 1)
      set_bit(UART_SOFT_PORT, UART_SOFT_PIN);
    else
      clr_bit(UART_SOFT_PORT, UART_SOFT_PIN);

    /* delay to send the bit */
    delay_ms(delay);
      
    /*prepare the next bit in frame to be sent*/
    txData >>= 1;

     /*then clear the pin for the incoming pin*/
    //clr_bit(UART_SOFT_PORT, UART_SOFT_PIN);
  }

  /* send stop-bit */
  set_bit(UART_SOFT_PORT, UART_SOFT_PIN);

  /* delay to send the bit */
  delay_ms(delay);
  #endif
    u16_t local_tx_shift_reg = tx_shift_reg;
   //if sending the previous character is not yet finished, return
   //transmission is finished when tx_shift_reg == 0
   if(local_tx_shift_reg){return;}
   //fill the TX shift register witch the character to be sent and the start & stop bits (start bit (1<<0) is already 0)
   local_tx_shift_reg = (txData<<1) | (1<<9); //stop bit (1<<9)
   tx_shift_reg = local_tx_shift_reg;
   //start timer0 with a prescaler of 8
  set_bit(TIMSK, OCIE0);
}

void softUartSendString(u8_t *txData)
{
  while (*txData != '\0')
    softUartSendChar(*txData++);
}

/* TIMER0_COMP_vect */
void __vector_10(void)
{
u16_t local_tx_shift_reg = tx_shift_reg;
   //output LSB of the TX shift register at the TX pin
   if( local_tx_shift_reg & 0x01 )
   {
           set_bit(UART_SOFT_PORT, UART_SOFT_PIN);
   }
   else
   {
           clr_bit(UART_SOFT_PORT, UART_SOFT_PIN);
   }
   //shift the TX shift register one bit to the right
   local_tx_shift_reg >>= 1;
   tx_shift_reg = local_tx_shift_reg;
   //if the stop bit has been sent, the shift register will be 0
   //and the transmission is completed, so we can stop & reset timer0
   if(!local_tx_shift_reg)
   {
       clr_bit(TIMSK, OCIE0);
			register(TCNT0) = 0;
   }
}