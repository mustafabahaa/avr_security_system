
/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** GPIO.c
 **************************************************************************
 **                              Includes                                 *
 *************************************************************************/
#include "port.h"
/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

port_error_t mcal_port_init(u8_t base, portState dir)
{
	port_error_t error = PORT_STATE_SUCCESS;

	if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
	{
		switch (dir)
		{
		case DIR_PORT_OUTPUT:
			reg_write(base + OFFSET_DIR, PORT_OUTPUT_DIR);
			reg_write(base + OFFSET_PORT, PORT_OFF);
			break;

		case DIR_PORT_INPUT_PULLDOWN:
			reg_write(base + OFFSET_DIR, PORT_INPUT_DIR);
			reg_write(base + OFFSET_PORT, PORT_OFF);
			break;

		case DIR_PORT_INPUT_PULLUP:
			reg_write(base + OFFSET_DIR, PORT_INPUT_DIR);
			reg_write(base + OFFSET_PORT, PORT_ON);
			break;

		case DIR_HIGH_ORDER_PORT_OUTPUT:
			register(base + OFFSET_DIR) = HIGH & PORT_HIGH_ORDER_OUTPUT_DIR;
			register(base + OFFSET_DIR) = HIGH & PORT_HIGH_ORDER_OFF;
			break;

		default:
			error = PORT_STATE_INVALID_DIR;
			break;
		}
	}
	else
	{
		error = PORT_STATE_INVALID_ADDR;
	}

	return error;
}

port_error_t mcal_port_write(u8_t base, u8_t value)
{
	port_error_t error = PORT_STATE_SUCCESS;

	if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
	{
		reg_write(base + OFFSET_PORT, value);
	}
	else
	{
		error = PORT_STATE_INVALID_ADDR;
	}

	return error;
}

port_error_t mcal_port_high_order_write(u8_t base, u8_t value)
{
	port_error_t error = PORT_STATE_SUCCESS;

	if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
	{
		register(base + OFFSET_PORT) = PORT_HIGH_ORDER_OUTPUT_DIR & value;
	}
	else
	{
		error = PORT_STATE_INVALID_ADDR;
	}

	return error;
}

port_error_t mcal_port_read(u8_t base, u8_t *value)
{
	port_error_t error = PORT_STATE_SUCCESS;

	if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
	{
		reg_read(base + OFFSET_PIN, value);
	}
	else
	{
		error = PORT_STATE_INVALID_ADDR;
	}
	return error;
}
