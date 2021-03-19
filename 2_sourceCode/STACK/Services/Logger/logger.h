/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** logger.h
 **************************************************************************/
#ifndef _LOGGER_H_
#define _LOGGER_H_
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "./../../BSP/includes/types.h"
#include "./../../BSP/includes/atmega16.h"
#include "./../../BSP/MCAL/UART/uart.h"
#include "./../../Utility/std_library/std_library.h"
/**************************************************************************/
/*                               Types                                    */
/**************************************************************************/
typedef enum {
	LOGGER_SUCCESS,
	LOGGER_FAILED,
}logger_type_t;

typedef enum {
	LOGGER_DEBUG,
	LOGGER_ERROR,
	LOGGER_WARNING,
	LOGGER_ALL,
}logger_verbosity_t;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** logger_init()
 **
 ** parameters: logger_verbosity_t verbosity
 ** return    : void
 **************************************************************************
 ** this function is used to initialize all the necessary sequence logger
 *************************************************************************/
void logger_init(logger_verbosity_t verbosity);

/**************************************************************************
 ** logger_write_debug()
 **
 ** parameters: const u8_t* tag
 ** parameters: const u8_t* data
 ** return    : void
 **************************************************************************
 ** this function is used to send data in debug mode
 *************************************************************************/
void logger_write_debug(u8_t* tag ,u8_t* data);

/**************************************************************************
 ** logger_write_warning()
 **
 ** parameters: const u8_t* tag
 ** parameters: const u8_t* data
 ** return    : void
 **************************************************************************
 ** this function is used to send data in warning mode
 *************************************************************************/
void logger_write_warning(u8_t* tag ,u8_t* data);

/**************************************************************************
 ** logger_write_error()
 **
 ** parameters: const u8_t* tag
 ** parameters: const u8_t* data
 ** return    : void
 **************************************************************************
 ** this function is used to send data in error mode
 *************************************************************************/
void logger_write_error(u8_t* tag ,u8_t* data);

#endif /*_LOGGER_H_*/
