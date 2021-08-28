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
  switch (channel->channel_pin)
  {
  case CHANNEL_1_PIN:
  {
    /* choosing mode of operation fast pwm */
    set_bit(TCCR0, WGM00);
    set_bit(TCCR0, WGM01);

    /*choose non inverting mode of pwm */
    set_bit(TCCR0, COM01);
    clr_bit(TCCR0, COM00);

    /*choose clock no pre scalling option*/
    clr_bit(TCCR0, CS02);
    clr_bit(TCCR0, CS01);
    set_bit(TCCR0, CS00);

    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 1 is confgiured in fast PWM mode");
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 1 is confgiured in non inverted mode");
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"channel 1 no pre-scaller selected");

    break;
  }

  case CHANNEL_2_PIN:
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

  case CHANNEL_3_PIN:
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

  case CHANNEL_4_PIN:
  {
    /* choosing mode of operation fast pwm */
    set_bit(TCCR2, WGM20);
    set_bit(TCCR2, WGM21);

    /*choose non inverting mode of pwm */
    set_bit(TCCR2, COM21);
    clr_bit(TCCR2, COM20);

    /*choose clock no pre scalling option*/
    clr_bit(TCCR2, CS22);
    clr_bit(TCCR2, CS21);
    set_bit(TCCR2, CS20);

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

  switch (channel->channel_pin)
  {
  case CHANNEL_1_PIN:
  {
    /* OCR0 holds a value from 0 to 255
		       that vary the output of ON PIN PB3
		       between 0 and v maximum (5v)
		 */
    register(OCR0) = (u8_t)duty;
    break;
  }

  case CHANNEL_2_PIN:
  {
    /* OCR1A holds a value from 0 to 1023
	       that vary the output of ON PIN PD5
	       between 0 and v maximum (5v)
		 */
    register(OCR1A) = duty;
    break;
  }

  case CHANNEL_3_PIN:
  {
    /* OCR1B holds a value from 0 to 1023
		       that vary the output of ON PIN PD5
		       between 0 and v maximum (5v)
		 */

    register(OCR1BL) = duty & LSB;
    register(OCR1BH) = duty & MSB;
    break;
  }

  case CHANNEL_4_PIN:
  {
    /* OCR2 holds a value from 0 to 255
		       that vary the output of ON PIN PB3
		       between 0 and v maximum (5v)
		 */
    register(OCR2) = (u8_t)duty;
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
