/***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "dc_motor.h"
/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

motor_error_t hal_dc_motor_init(motor_t *motor)
{
	motor_error_t error = MOTOR_STATE_SUCCESS;

	if (PWM_STATE_SUCCESS == mcal_pwm_initialization(motor->channel))
	{
		if (GPIO_STATE_SUCCESS == mcal_gpio_pin_init(
				motor->direction->dir_1_port,
				motor->direction->dir_1_pin,
				DIR_OUTPUT))
		{
			if (GPIO_STATE_SUCCESS == mcal_gpio_pin_init(
					motor->direction->dir_2_port,
					motor->direction->dir_2_pin,
					DIR_OUTPUT))
			{
				/* motor initialized */
			}
			else
			{
				error = MOTOR_STATE_ERROR;
			}
		}
		else
		{
			error = MOTOR_STATE_ERROR;
		}
	}
	else
	{
		error = MOTOR_STATE_ERROR;
	}
	return error;
}


motor_error_t hal_dc_motor_set_direction(motor_t *motor ,motor_direction_t direction)
{
	motor_error_t error = MOTOR_STATE_SUCCESS;

	if (direction == RIGHT || direction == LEFT)
	{
		if (GPIO_STATE_SUCCESS == mcal_gpio_pin_write(
				motor->direction->dir_1_port,motor->direction->dir_1_pin, direction))
		{
			if (GPIO_STATE_SUCCESS == mcal_gpio_pin_write(
					motor->direction->dir_2_port,motor->direction->dir_2_pin, !direction))
			{
				/* motor right direction set */
			}
			else
			{
				error = MOTOR_STATE_ERROR;
			}
		}
		else
		{
			error = MOTOR_STATE_ERROR;
		}
	}
	else
	{
		error = MOTOR_STATE_INVALID_DIRECTION;
	}

	return error;
}


motor_error_t hal_dc_motor_set_speed(motor_t* motor ,motor_speed_t speed)
{
	motor_error_t error = MOTOR_STATE_SUCCESS;

	if(motor->channel->channel_pin == CHANNEL_1_PIN ||
			motor->channel->channel_pin == CHANNEL_4_PIN)
	{
		if (PWM_STATE_SUCCESS == mcal_pwm_output(motor->channel,speed))
		{
			/* motor speed is updated */
		}
		else
		{
			error = MOTOR_STATE_ERROR;
		}
	}
	else if (motor->channel->channel_pin == CHANNEL_2_PIN ||
			motor->channel->channel_pin == CHANNEL_3_PIN)
	{
		if (PWM_STATE_SUCCESS == mcal_pwm_output(motor->channel,speed*4))
		{
			/* motor speed is updated */
		}
		else
		{
			error = MOTOR_STATE_ERROR;
		}
	}
	else
	{
		error = MOTOR_STATE_INVALID_MOTOR_PIN;
	}

	return error;
}



