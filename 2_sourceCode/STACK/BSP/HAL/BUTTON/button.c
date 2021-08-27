/***************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** button.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "button.h"
/*************************************************************************/
/*                          Global Variables                             */
/*************************************************************************/
static u8_t *TAG = (u8_t *)"BUTTON";
/**************************************************************************/
/*                     Functions Implementation                           */
/**************************************************************************/

button_error_t hal_button_init(button_t *the_button)
{
  button_error_t error = BUTTON_GPIO_STATE_SUCCESS;

  switch (the_button->connection)
  {
  case PULLUP_CONNECTION:
  {
    if (GPIO_STATE_SUCCESS != mcal_gpio_pin_init(
                                  the_button->base_addr,
                                  the_button->pin_num, DIR_INPUT_PULLUP))
    {
      error = BUTTON_GPIO_STATE_ERROR;
      logger_write_error_println(LOG_HAL, TAG, (u8_t *)"initialization fail");
    }
    else
    {
      logger_write_debug_println(LOG_HAL, TAG, (u8_t *)"initialization success");
    }
    break;
  }

  case PULLDOWN_CONNECTION:
  {
    if (GPIO_STATE_SUCCESS != mcal_gpio_pin_init(
                                  the_button->base_addr,
                                  the_button->pin_num, DIR_INPUT_PULLDOWN))
    {
      error = BUTTON_GPIO_STATE_ERROR;
      logger_write_error_println(LOG_HAL, TAG, (u8_t *)"initialization fail");
    }
    else
    {
      logger_write_debug_println(LOG_HAL, TAG, (u8_t *)"initialization success");
    }
    break;
  }

  default:
  {
    error = BUTTON_GPIO_INVALID_CONNECTION;
    logger_write_error_println(LOG_HAL, TAG, (u8_t *)"invalid connection type");

    break;
  }
  }
  return error;
}

button_error_t hal_button_get_state(
    button_t *the_button,
    button_states_t *result)
{
  button_error_t error = BUTTON_GPIO_STATE_SUCCESS;

  button_states_t states;

  if (GPIO_STATE_SUCCESS != mcal_gpio_pin_read(
                                the_button->base_addr,
                                the_button->pin_num, &states))
  {
    error = BUTTON_GPIO_STATE_ERROR;
    logger_write_error_println(LOG_HAL, TAG, (u8_t *)"get status failure");
  }
  else
  {
    if (the_button->connection == PULLDOWN_CONNECTION)
    {
      *result = (button_states_t)states;
    }
    else if (the_button->connection == PULLUP_CONNECTION)
    {
      *result = (button_states_t)(!states);
    }
    else
    {
      error = BUTTON_GPIO_INVALID_CONNECTION;
      logger_write_error_println(LOG_HAL, TAG, (u8_t *)"invalid connection type");
    }
  }

  return error;
}
