
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

port_error_t mcal_port_init(u8_t base, portState dir , u8_t mask)
{
	port_error_t error = PORT_STATE_SUCCESS;

	if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
	{
		switch (dir)
		{
		case DIR_PORT_OUTPUT:

			reg_mask_write(base + OFFSET_DIR, mask ,PORT_OUTPUT_DIR);
			reg_mask_write(base + OFFSET_PORT, mask ,PORT_OFF);
			break;

		case DIR_PORT_INPUT_PULLDOWN:
			reg_mask_write(base + OFFSET_DIR, mask ,PORT_INPUT_DIR);
			reg_mask_write(base + OFFSET_PORT, mask ,PORT_OFF);
			break;

		case DIR_PORT_INPUT_PULLUP:
			reg_mask_write(base + OFFSET_DIR, mask ,PORT_INPUT_DIR);
			reg_mask_write(base + OFFSET_PORT, mask ,PORT_ON);
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


port_error_t mcal_port_write(u8_t base, u8_t value , u8_t mask)
{
	port_error_t error = PORT_STATE_SUCCESS;

	if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
	{
		reg_mask_write(base + OFFSET_PORT, mask ,value );
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
