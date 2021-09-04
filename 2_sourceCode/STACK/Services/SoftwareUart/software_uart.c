/** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** software_uart.c
 **************************************************************************
 **                              Includes                                **
 *************************************************************************/
#include "software_uart.h"
/**************************************************************************
 **                              Global Variable                         **
 *************************************************************************/
static volatile u16_t tx_shift_reg = 0;
static timer_t timer;
static timer_config_t timer_config;
static soft_uart_t *gl_soft_uart;
static u8_t port;
static u8_t pin;
/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/
void service_soft_uart_init(soft_uart_t *soft_uart)
{
  gl_soft_uart = soft_uart;
  timer.timer_number = TIMER0_UNIT_1;
  timer.mode = TIMER_CTC_MODE;
  timer.preScaler = F_CPU_CLOCK;

  timer_config.tick_ms_seconds = (double)((F_CPU / timer.preScaler) / gl_soft_uart->baud) / 1000;
  timer.config = &timer_config;

  mcal_timer_init(&timer);

  /* initialize TX pin */
  mcal_gpio_pin_init(gl_soft_uart->base, gl_soft_uart->txPin, DIR_OUTPUT);
  mcal_gpio_pin_write(gl_soft_uart->base, gl_soft_uart->txPin, HIGH);

  /* allocate port and pin for faster execution in interrupt */
  port = gl_soft_uart->base + OFFSET_PORT;
  pin = gl_soft_uart->txPin;

  setGlobalInterrupt;
}

void service_soft_uart_send_byte(u8_t txData)
{
  u16_t local_tx_shift_reg = tx_shift_reg;
  //if sending the previous character is not yet finished, return
  //transmission is finished when tx_shift_reg == 0
  if (local_tx_shift_reg)
  {
    return;
  }
  //fill the TX shift register witch the character to be sent and the start & stop bits (start bit (1<<0) is already 0)
  local_tx_shift_reg = (txData << 1) | (1 << 9); //stop bit (1<<9)
  tx_shift_reg = local_tx_shift_reg;
  //start timer0 with a prescaler of 8
  mcal_timer_start(&timer);
}

void service_soft_uart_send_string(u8_t *txData)
{
  while (*txData != '\0')
  {
    service_soft_uart_send_byte(*txData++);
    delay_ms(3);
  }
}
/*************************************************************************/
/*                     Interrupts Implementation                         */
/*************************************************************************/
void TIMER0_COMP_vect(void)
{
  u16_t local_tx_shift_reg = tx_shift_reg;
  //output LSB of the TX shift register at the TX pin
  if (local_tx_shift_reg & 0x01)
  {
    mcal_fast_set(port, pin);
  }
  else
  {
    mcal_fast_clr(port, pin);
  }
  //shift the TX shift register one bit to the right
  local_tx_shift_reg >>= 1;
  tx_shift_reg = local_tx_shift_reg;
  //if the stop bit has been sent, the shift register will be 0
  //and the transmission is completed, so we can stop & reset timer0
  if (!local_tx_shift_reg)
  {
    mcal_timer_stop(&timer);
  }
}