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
#include "types.h"
#include "atmega32.h"
#include "software_uart.h"
#include "std_library.h"
/**************************************************************************/
/*                               Types                                    */
/**************************************************************************/
typedef enum {
	LOGGER_DEBUG=1,
	LOGGER_ERROR,
	LOGGER_WARNING,
	LOGGER_FULL_VERBOSITY,
}logger_verbosity_t;

typedef enum {
  LOG_MCAL=1,
  LOG_HAL=2,
  LOG_APP=3,
  LOG_UTILITY=4,
  LOG_SERVICES=5,
  LOG_MANAGERS=6,
  LOG_ALL_LAYERS=7,
} logger_layers_t;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** logger_init()
 **
 ** parameter: logger_verbosity_t verbosity , logger_layers_t layer
 ** return    : void
 **************************************************************************
 ** this function is used to initialize all the necessary sequence logger
 *************************************************************************/
void logger_init(logger_verbosity_t verbosity,logger_layers_t layer);

/**************************************************************************
 ** logger_write_debug()
 **
 ** parameter: logger_layers_t layer 
 ** parameter: const u8_t* tag
 ** parameter: const u8_t* data
 ** return    : void
 **************************************************************************
 ** this function is used to send data in debug mode
 *************************************************************************/
void logger_write_debug(logger_layers_t layer,u8_t* tag ,u8_t* data);

/**************************************************************************
 ** logger_write_warning()
 **
 ** parameter: logger_layers_t layer
 ** parameter: const u8_t* tag
 ** parameter: const u8_t* data
 ** return    : void
 **************************************************************************
 ** this function is used to send data in warning mode
 *************************************************************************/
void logger_write_warning(logger_layers_t layer,u8_t* tag ,u8_t* data);

/**************************************************************************
 ** logger_write_error()
 **
 ** parameter: logger_layers_t layer
 ** parameter: const u8_t* tag
 ** parameter: const u8_t* data
 ** return    : void
 **************************************************************************
 ** this function is used to send data in error mode
 *************************************************************************/
void logger_write_error(logger_layers_t layer,u8_t* tag ,u8_t* data);

/**************************************************************************
 ** logger_write_variable()
 **
 ** parameter: u8_t data
 ** return    : void
 **************************************************************************
 ** this function is used to send data in error mode
 *************************************************************************/
void logger_write_variable(u8_t data);

#endif /*_LOGGER_H_*/
