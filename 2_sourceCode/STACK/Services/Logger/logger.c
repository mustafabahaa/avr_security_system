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

static logger_verbosity_t g_verbosity;
static logger_layers_t g_layers;
static soft_uart_t softUart;

void logger_init(logger_verbosity_t verbosity, logger_layers_t layers)
{
  softUart.base = BASE_B;
  softUart.baud = SOFT_BAUD_9600;
  softUart.txPin = 7;

  g_verbosity = verbosity;
  g_layers = layers;
  service_soft_uart_init(&softUart);
}

void logger_write_debug(logger_layers_t layer, u8_t *tag, u8_t *data)
{
  if (LOGGER_DEBUG != g_verbosity && LOGGER_FULL_VERBOSITY != g_verbosity)
  {
    /* do nothing not in scope of verbosity */
  }
  else if ((g_layers != layer) && (g_layers != LOG_ALL_LAYERS))
  {
    /* do nothing , not the required layer logging */
  }
  else
  {
    u8_t str[100] = "";
    std_strcat(str, (u8_t *)"[DEBUG] ");
    std_strcat(str, (u8_t *)"[");
    std_strcat(str, (u8_t *)tag);
    std_strcat(str, (u8_t *)"] ");
    std_strcat(str, (u8_t *)data);
    std_strcat(str, (u8_t *)"\r\n");
    while (softUart.status == BUSY)
      ;
    service_soft_uart_send_string(str);
  }
}

void logger_write_warning(logger_layers_t layer, u8_t *tag, u8_t *data)
{
  if (LOGGER_WARNING != g_verbosity && LOGGER_FULL_VERBOSITY != g_verbosity)
  {
    /* do nothing */
  }
  else if ((g_layers != layer) && (g_layers != LOG_ALL_LAYERS))
  {
    /* do nothing , not the required layer logging */
  }
  else
  {
    u8_t str[100] = "";
    std_strcat(str, (u8_t *)"[WARNING] ");
    std_strcat(str, (u8_t *)"[");
    std_strcat(str, (u8_t *)tag);
    std_strcat(str, (u8_t *)"] ");
    std_strcat(str, (u8_t *)data);
    std_strcat(str, (u8_t *)"\r\n");
    while (softUart.status == BUSY)
      ;
    service_soft_uart_send_string(str);
  }
}

void logger_write_error(logger_layers_t layer, u8_t *tag, u8_t *data)
{
  if (LOGGER_ERROR != g_verbosity && LOGGER_FULL_VERBOSITY != g_verbosity)
  {
    /* do nothing */
  }
  else if ((g_layers != layer) && (g_layers != LOG_ALL_LAYERS))
  {
    /* do nothing , not the required layer logging */
  }
  else
  {
    u8_t str[100] = "";
    std_strcat(str, (u8_t *)"[ERROR] ");
    std_strcat(str, (u8_t *)"[");
    std_strcat(str, (u8_t *)tag);
    std_strcat(str, (u8_t *)"] ");
    std_strcat(str, (u8_t *)data);
    std_strcat(str, (u8_t *)"\r\n");
    while (softUart.status == BUSY)
      ;
    service_soft_uart_send_string(str);
  }
}

void logger_write_variable(u8_t data)
{
  while (softUart.status == BUSY)
    ;
  u8_t buff[1];
  std_itoa(data, buff, 10);
  service_soft_uart_send_byte(buff[0]);
}
