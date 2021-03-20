/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** MessagingUnit.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "MessagingUnit.h"
#include "./../../BSP/MCAL/UART/uart.h"
/*************************************************************************/
/*                     Static Functions Prototypes                       */
/*************************************************************************/


/**************************************************************************
 ** ()
 **
 ** parameters: void
 ** return    : system_error_t
 **************************************************************************
 **
 *************************************************************************/

/*************************************************************************/
/*                          Global Variables                             */
/*************************************************************************/
static u8_t* TAG = (u8_t*)"[MESSAGING UNIT]";
/*************************************************************************/

/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

system_error_t ms_manager_init()
{
	system_error_t error = SYSTEM_SUCCESS;

	if(UART_STATE_SUCCESS != mcal_UART_init())
	{
		error = SYSTEM_FAIL;
		logger_write_error(TAG,(u8_t *)"Failed to initialize messaging Unit");
	}
	else
	{
		logger_write_debug(TAG,(u8_t *)"Succeed to initialize messaging Unit");
	}

	return error;
}

system_error_t ms_manager_send_data(u8_t data)
{
	system_error_t error = SYSTEM_SUCCESS;

	if(UART_STATE_SUCCESS != mcal_UART_sendByte(data))
	{
		error = SYSTEM_FAIL;
		logger_write_error(TAG,(u8_t *)"Failed to send data");
	}
	else
	{
		logger_write_debug(TAG,(u8_t *)"Succeed to send data");
	}

	return error;
}

system_error_t ms_manager_send_string(u8_t* data)
{
	system_error_t error = SYSTEM_SUCCESS;

	if(UART_STATE_SUCCESS != mcal_UART_sendString(data))
	{
		error = SYSTEM_FAIL;
		logger_write_error(TAG,(u8_t *)"Failed to send string data");
	}
	else
	{
		logger_write_debug(TAG,(u8_t *)"Succeed to send string data");
	}

	return error;
}

system_error_t ms_manager_receive_data(u8_t* data)
{
	system_error_t error = SYSTEM_SUCCESS;

	if(UART_STATE_SUCCESS != mcal_UART_recieveByte(data))
	{
		error = SYSTEM_FAIL;
		logger_write_error(TAG,(u8_t *)"Failed to receive data");
	}
	else
	{
		logger_write_debug(TAG,(u8_t *)"Succeed to receive data");
	}

	return error;
}


