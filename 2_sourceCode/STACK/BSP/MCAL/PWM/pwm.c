/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** pwm.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "pwm.h"
/*************************************************************************/
/*                          Global Variables                             */
/*************************************************************************/
static u8_t *TAG = (u8_t *)"PWM";
/**************************************************************************/
/*                     Functions Implementation                           */
/**************************************************************************/

pwm_error_t mcal_pwm_initialization(pwm_channel_t *channel)
{
  pwm_error_t error = PWM_STATE_SUCCESS;

  /* making the pin of pwm output */

  mcal_gpio_pin_init(channel->channel_port, channel->channel_pin, DIR_OUTPUT);
  switch (channel->timer_number)
  {
  case TIMER0_UNIT_1:
  case TIMER0_UNIT_2:
  {
    /* choosing mode of operation fast pwm */
    set_bit(TCCR0A, WGM00);
    set_bit(TCCR0A, WGM01);
    clr_bit(TCCR0B, WGM02);

    /*choose non inverting mode of pwm */
    set_bit(TCCR0A, COM0A1);
    clr_bit(TCCR0A, COM0A0);

    /*choose non inverting mode of pwm */
    set_bit(TCCR2A, COM0B1);
    clr_bit(TCCR2A, COM0B0);

    /*choose clock no pre scalling option*/
    clr_bit(TCCR0A, CS02);
    clr_bit(TCCR0A, CS01);
    set_bit(TCCR0A, CS00);

    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 1 is confgiured in fast PWM mode");
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 1 is confgiured in non inverted mode");
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 1 no pre-scaller selected");

    break;
  }

  case TIMER1_UNIT_1:
  {
    /* choosing mode of operation fast pwm */
    set_bit(TCCR1A, WGM11);
    set_bit(TCCR1A, WGM10);

    /*choose non inverting mode of pwm */
    set_bit(TCCR1A, COM1A1);
    clr_bit(TCCR1A, COM1A0);

    /*choose clock no pre scalling option*/
    clr_bit(TCCR1B, CS12);
    clr_bit(TCCR1B, CS11);
    set_bit(TCCR1B, CS10);

    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 2 is confgiured in fast PWM mode");
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 2 is confgiured in non inverted mode");
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 2 no pre-scaller selected");

    break;
  }

  case TIMER1_UNIT_2:
  {
    /* choosing mode of operation fast pwm */
    set_bit(TCCR1A, WGM11);
    set_bit(TCCR1A, WGM10);

    /*choose non inverting mode of pwm */
    set_bit(TCCR1A, COM1B1);
    clr_bit(TCCR1A, COM1B0);

    /*choose clock no pre scalling option*/
    clr_bit(TCCR1B, CS12);
    clr_bit(TCCR1B, CS11);
    set_bit(TCCR1B, CS10);

    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 3 is confgiured in fast PWM mode");
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 3 is confgiured in non inverted mode");
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 3 no pre-scaller selected");

    break;
  }

  case TIMER2_UNIT_1:
  case TIMER2_UNIT_2:
  {
    /* choosing mode of operation fast pwm */
    set_bit(TCCR2A, WGM20);
    set_bit(TCCR2A, WGM21);
    clr_bit(TCCR2B, WGM22);

    /*choose non inverting mode of pwm */
    set_bit(TCCR2A, COM2A1);
    clr_bit(TCCR2A, COM2A0);

    /*choose non inverting mode of pwm */
    set_bit(TCCR2A, COM2B1);
    clr_bit(TCCR2A, COM2B0);

    /*choose clock no pre scalling option*/
    clr_bit(TCCR2A, CS22);
    clr_bit(TCCR2A, CS21);
    set_bit(TCCR2A, CS20);

    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 4 is confgiured in fast PWM mode");
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 4 is confgiured in non inverted mode");
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 4 no pre-scaller selected");

    break;
  }

  default:
  {
    error = PWM_STATE_INVALID_CHANNEL;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"Invalid channel number");
    break;
  }
  }
  return error;
}

pwm_error_t mcal_pwm_output(pwm_channel_t *channel, u16_t duty)
{
  pwm_error_t error = PWM_STATE_SUCCESS;

  switch (channel->timer_number)
  {
  case TIMER0_UNIT_1:
  {
    /* OCR0 holds a value from 0 to 255
		       that vary the output of ON PIN PB3
		       between 0 and v maximum (5v)
		 */
    register(OCR0A) = (u8_t)duty;
    break;
  }

  case TIMER0_UNIT_2:
  {
    /* OCR1A holds a value from 0 to 1023
	       that vary the output of ON PIN PD5
	       between 0 and v maximum (5v)
		 */
    register(OCR0B) = duty;
    break;
  }

  case TIMER1_UNIT_1:
  {
    /* OCR1B holds a value from 0 to 1023
		       that vary the output of ON PIN PD5
		       between 0 and v maximum (5v)
		 */

    register(OCR1AL) = duty & LSB;
    register(OCR1AH) = duty & MSB;
    break;
  }

  case TIMER1_UNIT_2:
  {
    /* OCR1B holds a value from 0 to 1023
		       that vary the output of ON PIN PD5
		       between 0 and v maximum (5v)
		 */

    register(OCR1BL) = duty & LSB;
    register(OCR1BH) = duty & MSB;
    break;
  }

  case TIMER2_UNIT_1:
  {
    /* OCR2 holds a value from 0 to 255
		       that vary the output of ON PIN PB3
		       between 0 and v maximum (5v)
		 */
    register(OCR2A) = (u8_t)duty;
    break;
  }

  case TIMER2_UNIT_2:
  {
    /* OCR2 holds a value from 0 to 255
		       that vary the output of ON PIN PB3
		       between 0 and v maximum (5v)
		 */
    register(OCR2B) = (u8_t)duty;
    break;
  }

  case TIMER3_UNIT_1:
  {
    /* OCR2 holds a value from 0 to 255
		       that vary the output of ON PIN PB3
		       between 0 and v maximum (5v)
		 */
    register(OCR3AL) = duty & LSB;
    register(OCR3AH) = duty & MSB;
    break;
  }

  case TIMER3_UNIT_2:
  {
    /* OCR2 holds a value from 0 to 255
		       that vary the output of ON PIN PB3
		       between 0 and v maximum (5v)
		 */
    register(OCR3BL) = duty & LSB;
    register(OCR3BH) = duty & MSB;
    break;
  }

  default:
  {
    error = PWM_STATE_INVALID_CHANNEL;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"Invalid channel number");
    break;
  }
  }
  return error;
}
