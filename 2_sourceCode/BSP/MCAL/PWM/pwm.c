/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** pwm.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "pwm.h"

/**************************************************************************/
/*                     Functions Implementation                           */
/**************************************************************************/

pwm_error_t  mcal_pwm_initialization(pwm_channel_t* channel)
{
	pwm_error_t error = PWM_STATE_SUCCESS;

	/* making the pin of pwm output */
	set_bit(channel->channel_port + OFFSET_DIR,channel->channel_pin);

	switch(channel->channel_pin)
	{
	case CHANNEL_1_PIN :
	{
		/* choosing mode of operation fast pwm */
		set_bit(TCCR0,WGM00);
		set_bit(TCCR0,WGM01);

		/*choose non inverting mode of pwm */
		set_bit(TCCR0,COM01);
		clear_bit(TCCR0,COM00);

		/*choose clock no pre scalling option*/
		clear_bit(TCCR0,CS02);
		clear_bit(TCCR0,CS01);
		set_bit(TCCR0,CS00);

		break;
	}

	case CHANNEL_2_PIN :
	{
		/* choosing mode of operation fast pwm */
		set_bit(TCCR1A,WGM11);
		set_bit(TCCR1A,WGM10);

		/*choose non inverting mode of pwm */
		set_bit(TCCR1A,COM1A1);
		clear_bit(TCCR1A,COM1A0);

		/*choose clock no pre scalling option*/
		clear_bit(TCCR1B,CS12);
		clear_bit(TCCR1B,CS11);
		set_bit(TCCR1B,CS10);

		break;
	}

	case CHANNEL_3_PIN :
	{
		/* choosing mode of operation fast pwm */
		set_bit(TCCR1A,WGM11);
		set_bit(TCCR1A,WGM10);

		/*choose non inverting mode of pwm */
		set_bit(TCCR1A,COM1B1);
		clear_bit(TCCR1A,COM1B0);

		/*choose clock no pre scalling option*/
		clear_bit(TCCR1B,CS12);
		clear_bit(TCCR1B,CS11);
		set_bit(TCCR1B,CS10);

		break;
	}

	case CHANNEL_4_PIN :
	{
		/* choosing mode of operation fast pwm */
		set_bit(TCCR2,WGM20);
		set_bit(TCCR2,WGM21);

		/*choose non inverting mode of pwm */
		set_bit(TCCR2,COM21);
		clear_bit(TCCR2,COM20);

		/*choose clock no pre scalling option*/
		clear_bit(TCCR2,CS22);
		clear_bit(TCCR2,CS21);
		set_bit(TCCR2,CS20);

		break;
	}

	default:{
		error = PWM_STATE_INVALID_CHANNEL;
		break;
	}
	}
	return error;
}

pwm_error_t  mcal_pwm_output(pwm_channel_t* channel , u16_t duty)
{
	pwm_error_t error = PWM_STATE_SUCCESS;

	switch(channel->channel_pin)
	{
	case CHANNEL_1_PIN :
	{
		/* OCR0 holds a value from 0 to 255
		       that vary the output of ON PIN PB3
		       between 0 and v maximum (5v)
		 */
		register(OCR0) = (u8_t)duty;
		break;
	}

	case CHANNEL_2_PIN :
	{
		/* OCR1A holds a value from 0 to 1023
	       that vary the output of ON PIN PD5
	       between 0 and v maximum (5v)
		 */
		register(OCR1A) = duty;
		break;
	}

	case CHANNEL_3_PIN :
	{
		/* OCR1B holds a value from 0 to 1023
		       that vary the output of ON PIN PD5
		       between 0 and v maximum (5v)
		 */

		register(OCR1BL) = duty & 0x0F;
		register(OCR1BH) = duty & 0xF0;
		break;
	}

	case CHANNEL_4_PIN :
	{
		/* OCR2 holds a value from 0 to 255
		       that vary the output of ON PIN PB3
		       between 0 and v maximum (5v)
		 */
		register(OCR2) = (u8_t)duty;
		break;
	}

	default : {
		error = PWM_STATE_INVALID_CHANNEL;
		break;
	}
	}
	return error;
}





