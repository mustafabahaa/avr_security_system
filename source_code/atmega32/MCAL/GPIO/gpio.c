/**************************************************************************
** This  software  is  in  the  public  domain , furnished "as is", without
** technical support,  and with no  warranty, express or implied, as to its
** usefulness for any purpose.

** GPIO.c
***************************************************************************
**                              Includes                                 **
**************************************************************************/
#include "gpio.h"

/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

gpio_error_t mcal_gpio_pin_init(u8_t base, u8_t pin, pinState dir)
{
  gpio_error_t error = STATE_SUCCESS;

  if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
  {
    if (pin < MAX_PIN_NUMBER)
    {
      switch (dir)
      {
      case DIR_OUTPUT:
        set_bit(base + OFFSET_DIR, pin);
        break;

      case DIR_INPUT_PULLDOWN:
        clr_bit(base + OFFSET_DIR, pin);
        break;

      case DIR_INPUT_PULLUP:
        clr_bit(base + OFFSET_DIR, pin);
        set_bit(base + OFFSET_PORT, pin);
        break;

      default:
        error = STATE_INVALID_DIR;
        break;
      }
    }
    else
    {
      error = STATE_INVAILD_PIN;
    }
  }
  else
  {
    error = STATE_INVALID_ADDR;
  }
  return error;
}

gpio_error_t mcal_gpio_pin_write(u8_t base, u8_t pin, u8_t value)
{
  gpio_error_t error = STATE_SUCCESS;

  if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
  {
    switch (value)
    {
    case HIGH:
      set_bit(base + OFFSET_PORT, pin);
      break;

    case LOW:
      clr_bit(base + OFFSET_PORT, pin);
      break;

    default:
      error = STATE_INVALID_VALUE;
      break;
    }
  }
  else
  {
    error = STATE_INVALID_ADDR;
  }

  return error;
}

gpio_error_t mcal_gpio_pin_toggle(u8_t base, u8_t pin)
{
  gpio_error_t error = STATE_SUCCESS;

  if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
  {

    tog_bit(base + OFFSET_PORT, pin);
  }
  else
  {
    error = STATE_INVALID_ADDR;
  }

  return error;
}

gpio_error_t mcal_gpio_pin_read(u8_t base, u8_t pin, u8_t *value)
{
  gpio_error_t error = STATE_SUCCESS;

  if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
  {
    if (pin < MAX_PIN_NUMBER)
    {
      *value = bit_is_set(base + OFFSET_PIN, pin);
    }
    else
    {
      error = STATE_INVAILD_PIN;
    }
  }
  else
  {
    error = STATE_INVALID_ADDR;
  }
  return error;
}

gpio_error_t mcal_gpio_port_init(u8_t base, portState dir)
{
  gpio_error_t error = STATE_SUCCESS;

  if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
  {
    switch (dir)
    {
    case DIR_PORT_OUTPUT:
      reg_write(base + OFFSET_DIR, PORT_OUTPUT_DIR);
      break;

    case DIR_PORT_INPUT_PULLDOWN:
      reg_write(base + OFFSET_DIR, PORT_INPUT_DIR);
      reg_write(base + OFFSET_PORT, PORT_OFF);
      break;

    case DIR_PORT_INPUT_PULLUP:
      reg_write(base + OFFSET_DIR, PORT_INPUT_DIR);
      reg_write(base + OFFSET_PORT, PORT_ON);
      break;

    default:
      error = STATE_INVALID_DIR;
      break;
    }
  }
  else
  {
    error = STATE_INVALID_ADDR;
  }

  return error;
}

gpio_error_t mcal_gpio_port_write(u8_t base, u8_t value)
{
  gpio_error_t error = STATE_SUCCESS;

  if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
  {
    reg_write(base + OFFSET_PORT, value);
  }
  else
  {
    error = STATE_INVALID_ADDR;
  }

  return error;
}

gpio_error_t mcal_gpio_port_read(u8_t base, u8_t *value)
{
  gpio_error_t error = STATE_SUCCESS;

  if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
  {
    reg_read(base + OFFSET_PIN, value);
  }
  else
  {
    error = STATE_INVALID_ADDR;
  }
  return error;
}