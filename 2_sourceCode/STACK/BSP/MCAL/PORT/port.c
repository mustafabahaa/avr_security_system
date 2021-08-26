
/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** port.c
 **************************************************************************
 **                              Includes                                 *
 *************************************************************************/
#include "port.h"
/*************************************************************************/
/*                          Global Variables                             */
/*************************************************************************/
static u8_t *TAG = (u8_t *)"PORT";
/*************************************************************************/
/*                     Static Functions Prototype                        */
/*************************************************************************/
static void print_port_char(u8_t base);

/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

port_error_t mcal_port_init(u8_t base, portState dir, u8_t mask)
{
  port_error_t error = PORT_STATE_SUCCESS;

  if (base != BASE_A && base != BASE_B && base != BASE_C && base != BASE_D)
  {
    error = PORT_STATE_INVALID_ADDR;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied port number");
  }
  else
  {
    print_port_char(base);
    switch (dir)
    {
    case DIR_PORT_OUTPUT:
      reg_mask_write(base + OFFSET_DIR, mask, PORT_OUTPUT_DIR);
      reg_mask_write(base + OFFSET_PORT, mask, PORT_OFF);
      logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"port configured as output");
      break;

    case DIR_PORT_INPUT_PULLDOWN:
      reg_mask_write(base + OFFSET_DIR, mask, PORT_INPUT_DIR);
      reg_mask_write(base + OFFSET_PORT, mask, PORT_OFF);
      logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"port configured as input pulldown");

      break;

    case DIR_PORT_INPUT_PULLUP:
      reg_mask_write(base + OFFSET_DIR, mask, PORT_INPUT_DIR);
      reg_mask_write(base + OFFSET_PORT, mask, PORT_ON);
      logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"port configured as input pull up");
      break;

    default:
      error = PORT_STATE_INVALID_DIR;
      logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied port direction");
      break;
    }
  }
  return error;
}

port_error_t mcal_port_write(u8_t base, u8_t value, u8_t mask)
{
  port_error_t error = PORT_STATE_SUCCESS;

  if (base != BASE_A && base != BASE_B && base != BASE_C && base != BASE_D)
  {
    error = PORT_STATE_INVALID_ADDR;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied port number");
  }
  else
  {
    reg_mask_write(base + OFFSET_PORT, mask, value);
  }

  return error;
}

port_error_t mcal_port_read(u8_t base, u8_t *value)
{
  port_error_t error = PORT_STATE_SUCCESS;

  if (base != BASE_A && base != BASE_B && base != BASE_C && base != BASE_D)
  {
    error = PORT_STATE_INVALID_ADDR;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied port number");
  }
  else
  {
    reg_read(base + OFFSET_PIN, *value);
  }
  return error;
}

/*************************************************************************/
/*                     Static Functions Implementation                   */
/*************************************************************************/

static void print_port_char(u8_t base)
{
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
}