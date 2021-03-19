/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** logger.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "logger.h"
/**************************************************************************/
/*                     Functions Implementation                           */
/**************************************************************************/

logger_verbosity_t g_verbosity;

void logger_init(logger_verbosity_t verbosity)
{

	g_verbosity = verbosity;

	if(UART_STATE_SUCCESS != mcal_UART_init())
	{
		/* Logger failed to initialize UART */
	}
	else
	{
		/* Logger initialized */
	}
}

void logger_write_debug(u8_t* tag ,u8_t* data)
{
	if ( LOGGER_DEBUG != g_verbosity && LOGGER_ALL != g_verbosity)
	{
		/* do nothing */
	}
	else
	{
		u8_t str[100] = "";
		std_strcat(str, (u8_t*)"[DEBUG] ");
		std_strcat(str, (u8_t*)"[");
		std_strcat(str, (u8_t*)tag);
		std_strcat(str, (u8_t*)"] ");
		std_strcat(str, (u8_t*)data);
		std_strcat(str, (u8_t*)"\r\n");
		mcal_UART_sendString(str);
	}
}

void logger_write_warning(u8_t* tag ,u8_t* data)
{
	if ( LOGGER_WARNING != g_verbosity && LOGGER_ALL != g_verbosity)
	{
		/* do nothing */
	}
	else
	{
		u8_t str[100] = "";
		std_strcat(str, (u8_t*)"[WARNING] ");
		std_strcat(str, (u8_t*)"[");
		std_strcat(str, (u8_t*)tag);
		std_strcat(str, (u8_t*)"] ");
		std_strcat(str, (u8_t*)data);
		std_strcat(str, (u8_t*)"\r\n");
		mcal_UART_sendString(str);
	}
}

void logger_write_error(u8_t* tag ,u8_t* data)
{
	if ( LOGGER_ERROR != g_verbosity && LOGGER_ALL != g_verbosity)
	{
		/* do nothing */
	}
	else
	{
		u8_t str[100] = "";
		std_strcat(str, (u8_t*)"[ERROR] ");
		std_strcat(str, (u8_t*)"[");
		std_strcat(str, (u8_t*)tag);
		std_strcat(str, (u8_t*)"] ");
		std_strcat(str, (u8_t*)data);
		std_strcat(str, (u8_t*)"\r\n");
		mcal_UART_sendString(str);
	}
}
