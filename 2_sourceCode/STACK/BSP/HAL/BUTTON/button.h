/***************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** button.h
 **************************************************************************/
#ifndef _BUTTON_H_
#define _BUTTON_H_
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "types.h"
#include "gpio.h"
#include "logger.h"

/**************************************************************************/
/*                                 Types                                  */
/**************************************************************************/
typedef enum
{
  PULLUP_CONNECTION = 1,
  PULLDOWN_CONNECTION
} buttonConnection_t;

typedef enum
{
  BUTTON_GPIO_STATE_SUCCESS = 1,
  BUTTON_GPIO_INVALID_CONNECTION,
  BUTTON_GPIO_STATE_ERROR
} button_error_t;

typedef enum
{
  BUTTON_NOT_PRESSED = 1,
  BUTTON_PRESSED
} button_states_t;

typedef struct button
{
  u8_t base_addr;
  u8_t pin_num;
  buttonConnection_t connection;
} button_t;

/**************************************************************************/
/*                           Public Functions                             */
/***************************************************************************
 ** hal_button_init()
 **
 ** parameter: button_t *the_button
 ** return    : button_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary
 ** sequence for button
 **************************************************************************/
button_error_t hal_button_init(button_t *the_button);

/***************************************************************************
 ** hal_button_init()
 **
 ** parameter: button_t *the_button
 ** parameter: button_states_t *result
 ** return    : button_error_t
 ***************************************************************************
 ** this function return the states of the button On or off
 **************************************************************************/
button_error_t hal_button_get_state(button_t *the_button,
                                    button_states_t *result);

#endif /*_BUTTON_H_*/
