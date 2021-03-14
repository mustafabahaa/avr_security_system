/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** GPIO.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "gpio.h"

/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

GPIO_STATE_ERROR_t mcal_gpio_pin_init(u8_t base, u8_t pin, pinState dir)
{
	GPIO_STATE_ERROR_t error = GPIO_STATE_SUCCESS;

	if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
	{
		if (pin < ECU_PORT_PINS_NUMBER)
		{
			switch (dir)
			{
			case DIR_OUTPUT:
				set_bit(base + OFFSET_DIR, pin);
				break;

			case DIR_INPUT_PULLDOWN:
				clr_bit(base + OFFSET_DIR, pin);
				break;

			case DIR_INPUT_PULLUP:
				clr_bit(base + OFFSET_DIR, pin);
				set_bit(base + OFFSET_PORT, pin);
				break;

			default:
				error = GPIO_STATE_INVALID_DIR;
				break;
			}
		}
		else
		{
			error = GPIO_STATE_INVAILD_PIN;
		}
	}
	else
	{
		error = GPIO_STATE_INVALID_ADDR;
	}
	return error;
}

GPIO_STATE_ERROR_t mcal_gpio_pin_write(u8_t base, u8_t pin, u8_t value)
{
	GPIO_STATE_ERROR_t error = GPIO_STATE_SUCCESS;

	if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
	{
		if (pin < ECU_PORT_PINS_NUMBER)
		{
			switch (value)
			{
			case HIGH:
				set_bit(base + OFFSET_PORT, pin);
				break;

			case LOW:
				clr_bit(base + OFFSET_PORT, pin);
				break;

			default:
				error = GPIO_STATE_INVALID_VALUE;
				break;
			}
		}
		else
		{
			error = GPIO_STATE_INVAILD_PIN;
		}
	}
	else
	{
		error = GPIO_STATE_INVALID_ADDR;
	}

	return error;
}

GPIO_STATE_ERROR_t mcal_gpio_pin_toggle(u8_t base, u8_t pin)
{
	GPIO_STATE_ERROR_t error = GPIO_STATE_SUCCESS;

	if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
	{

		tog_bit(base + OFFSET_PORT, pin);
	}
	else
	{
		error = GPIO_STATE_INVALID_ADDR;
	}

	return error;
}

GPIO_STATE_ERROR_t mcal_gpio_pin_read(u8_t base, u8_t pin, u8_t *value)
{
	GPIO_STATE_ERROR_t error = GPIO_STATE_SUCCESS;

	if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
	{
		if (pin < ECU_PORT_PINS_NUMBER)
		{
			*value = bit_is_set(base + OFFSET_PIN, pin);
		}
		else
		{
			error = GPIO_STATE_INVAILD_PIN;
		}
	}
	else
	{
		error = GPIO_STATE_INVALID_ADDR;
	}
	return error;
}
