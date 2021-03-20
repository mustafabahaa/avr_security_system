/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** buzzer.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "buzzer.h"

/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

buzzer_error_t hal_buzzer_init(buzzer_t *the_buzzer)
{
	buzzer_error_t error = BUZZER_GPIO_STATE_SUCCESS;

	if (the_buzzer->wiring == BUZZER_CURRENT_SOURCING ||
			the_buzzer->wiring == BUZZER_CURRENT_SINKING)
	{
		if (GPIO_STATE_SUCCESS == mcal_gpio_pin_init(
				the_buzzer->base_addr,
				the_buzzer->pin_num, DIR_OUTPUT))
		{
			/* buzzer initialized */
		}
		else
		{
			error = BUZZER_GPIO_STATE_ERROR;
		}
	}
	else
	{
		error = BUZZER_GPIO_INVALID_CURRENT;
	}
	return error;
}

buzzer_error_t hal_buzzer_set_state(buzzer_t *the_buzzer, u8_t value)
{
	buzzer_error_t error = BUZZER_GPIO_STATE_SUCCESS;

	if (the_buzzer->wiring == BUZZER_CURRENT_SOURCING)
	{
		if (GPIO_STATE_SUCCESS == mcal_gpio_pin_write(
				the_buzzer->base_addr,
				the_buzzer->pin_num, value))
		{
			/* buzzer value is written */
		}
		else
		{
			error = BUZZER_GPIO_STATE_ERROR;
		}
	}
	else if (the_buzzer->wiring == BUZZER_CURRENT_SINKING)
	{
		if (GPIO_STATE_SUCCESS == mcal_gpio_pin_write(
				the_buzzer->base_addr,
				the_buzzer->pin_num, !value))
		{
			/* buzzer value is written */
		}
		else
		{
			error = BUZZER_GPIO_STATE_ERROR;
		}
	}
	else
	{
		error = BUZZER_GPIO_INVALID_CURRENT;
	}
	return error;
}

buzzer_error_t hal_buzzer_toggle_state(buzzer_t *the_buzzer)
{
	buzzer_error_t error = BUZZER_GPIO_STATE_SUCCESS;

	if (the_buzzer->wiring == BUZZER_CURRENT_SOURCING)
	{
		if (GPIO_STATE_SUCCESS == mcal_gpio_pin_toggle(
				the_buzzer->base_addr,
				the_buzzer->pin_num))
		{
			/* buzzer value is written */
		}
		else
		{
			error = BUZZER_GPIO_STATE_ERROR;
		}
	}
	return error;
}

buzzer_error_t hal_buzzer_get_state(buzzer_t *the_buzzer, u8_t *result)
{
	buzzer_error_t error = BUZZER_GPIO_STATE_SUCCESS;

	u8_t pin;

	if (GPIO_STATE_SUCCESS == mcal_gpio_pin_read(
			the_buzzer->base_addr,
			the_buzzer->pin_num, &pin))
	{
		if (the_buzzer->wiring == BUZZER_CURRENT_SOURCING)
		{
			*result = pin;
		}
		else if (the_buzzer->wiring == BUZZER_CURRENT_SINKING)
		{
			*result = !pin;
		}
		else
		{
			error = BUZZER_GPIO_INVALID_CURRENT;
		}
	}
	else
	{
		error = BUZZER_GPIO_STATE_ERROR;
	}

	return error;
}
