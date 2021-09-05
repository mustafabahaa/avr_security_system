/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** gpio.c
 **************************************************************************
 **                              Includes                                **
 *************************************************************************/
#include "gpio.h"
/*************************************************************************/
/*                          Global Variables                             */
/*************************************************************************/
static u8_t *TAG = (u8_t *)"GPIO";
/*************************************************************************/
/*                     Static Functions Prototype                        */
/*************************************************************************/
static void print_port_char(u8_t base);

/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

gpio_state_error_t mcal_gpio_pin_init(u8_t base, u8_t pin, pinState_t dir)
{
  gpio_state_error_t error = GPIO_STATE_SUCCESS;

  if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
  {
    if (pin < ECU_PORT_PINS_NUMBER)
    {
      print_port_char(base);
      switch (dir)
      {
      case DIR_OUTPUT:
      {
        set_bit(base + OFFSET_DIR, pin);
        logger_write_debug_println_with_variable(LOG_MCAL, TAG, (u8_t *)"pin configured as output", pin);
        break;
      }
      case DIR_INPUT_PULLDOWN:
      {
        clr_bit(base + OFFSET_DIR, pin);
        logger_write_debug_println_with_variable(LOG_MCAL, TAG, (u8_t *)"pin configured as input pulldown", pin);
        break;
      }

      case DIR_INPUT_PULLUP:
      {
        clr_bit(base + OFFSET_DIR, pin);
        set_bit(base + OFFSET_PORT, pin);
        logger_write_debug_println_with_variable(LOG_MCAL, TAG, (u8_t *)"pin configured as input pullup", pin);
        break;
      }

      default:
      {
        error = GPIO_STATE_INVALID_DIR;
        logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied pin direction");
        break;
      }
      }
    }
    else
    {
      error = GPIO_STATE_INVAILD_PIN;
      logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied pin number");
    }
  }
  else
  {
    error = GPIO_STATE_INVALID_ADDR;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied port number");
  }
  return error;
}

gpio_state_error_t mcal_gpio_pin_write(u8_t base, u8_t pin, u8_t value)
{
  gpio_state_error_t error = GPIO_STATE_SUCCESS;

  if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
  {
    if (pin < ECU_PORT_PINS_NUMBER)
    {
      switch (value)
      {
      case HIGH:
      {
        set_bit(base + OFFSET_PORT, pin);
        logger_write_debug_println_with_variable(LOG_MCAL, TAG, (u8_t *)"pin logic level HIGH", pin);
        break;
      }

      case LOW:
      {
        clr_bit(base + OFFSET_PORT, pin);
        logger_write_debug_println_with_variable(LOG_MCAL, TAG, (u8_t *)"pin logic level LOW", pin);
        break;
      }

      default:
      {
        error = GPIO_STATE_INVALID_VALUE;
        logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalid logic level");
        break;
      }
      }
    }
    else
    {
      error = GPIO_STATE_INVAILD_PIN;
      logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied pin number");
    }
    print_port_char(base);
  }
  else
  {
    error = GPIO_STATE_INVALID_ADDR;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied port number");
  }

  return error;
}

gpio_state_error_t mcal_gpio_pin_toggle(u8_t base, u8_t pin)
{
  gpio_state_error_t error = GPIO_STATE_SUCCESS;

  if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
  {
    if (pin < ECU_PORT_PINS_NUMBER)
    {
      tog_bit(base + OFFSET_PORT, pin);
      print_port_char(base);
      logger_write_debug_println_with_variable(LOG_MCAL, TAG, (u8_t *)"pin is toggled", pin);
    }
    else
    {
      error = GPIO_STATE_INVAILD_PIN;
      logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied pin number");
    }
  }
  else
  {
    error = GPIO_STATE_INVALID_ADDR;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied port number");
  }

  return error;
}

gpio_state_error_t mcal_gpio_pin_read(u8_t base, u8_t pin, u8_t *value)
{
  gpio_state_error_t error = GPIO_STATE_SUCCESS;

  if (base == BASE_A || base == BASE_B || base == BASE_C || base == BASE_D)
  {
    if (pin >= ECU_PORT_PINS_NUMBER)
    {
      *value = bit_is_set(base + OFFSET_PIN, pin);
      logger_write_debug_println_with_variable(LOG_MCAL, TAG, (u8_t *)"pin read logic level ", *value);
    }
    else
    {
      error = GPIO_STATE_INVAILD_PIN;
      logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied pin number");
    }
  }
  else
  {
    error = GPIO_STATE_INVALID_ADDR;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied port number");
  }
  return error;
}

/*************************************************************************/
/*                     Static Functions Implementation                   */
/*************************************************************************/

static void print_port_char(u8_t base)
{
  /*
  u8_t str[6] = "";
  if (base == BASE_A)
    std_strcat(str, (u8_t *)"PORT A");
  else if (base == BASE_B)
    std_strcat(str, (u8_t *)"PORT B");
  else if (base == BASE_C)
    std_strcat(str, (u8_t *)"PORT C");
  else
    std_strcat(str, (u8_t *)"PORT D");

  logger_write_debug_println(LOG_MCAL, TAG, str);
  */
}