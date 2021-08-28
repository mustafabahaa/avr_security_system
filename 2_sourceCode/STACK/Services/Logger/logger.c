/***************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** logger.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "logger.h"
/**************************************************************************/
/*                            Global variables                            */
/**************************************************************************/
static logger_verbosity_t g_verbosity;
static logger_layers_t g_layers;
static soft_uart_t softUart;
/**************************************************************************/
/*                      static functions prototype                        */
/**************************************************************************/
static void send_packet(u8_t *tag, u8_t *data, u8_t *log_type, u16_t variable);
/**************************************************************************/
/*                     Functions Implementation                           */
/**************************************************************************/

void logger_init(logger_verbosity_t verbosity, logger_layers_t layers)
{
  softUart.base = BASE_B;
  softUart.baud = SOFT_BAUD_9600;
  softUart.txPin = 7;

  g_verbosity = verbosity;
  g_layers = layers;
  service_soft_uart_init(&softUart);
}

void logger_write_debug_println(logger_layers_t layer, u8_t *tag, u8_t *data)
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
    send_packet(tag, data, (u8_t *)"DEBUG", NULL);
  }
}

void logger_write_debug_println_with_variable(logger_layers_t layer, u8_t *tag, u8_t *data, u16_t variable)
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
    send_packet(tag, data, (u8_t *)"DEBUG", variable);
  }
}

void logger_write_warning_println(logger_layers_t layer, u8_t *tag, u8_t *data)
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
    send_packet(tag, data, (u8_t *)"WARNING", NULL);
  }
}

void logger_write_error_println(logger_layers_t layer, u8_t *tag, u8_t *data)
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
    send_packet(tag, data, (u8_t *)"ERROR", NULL);
  }
}

/**************************************************************************/
/*                      static functions implementation                   */
/**************************************************************************/

static void send_packet(u8_t *tag, u8_t *data, u8_t *log_type, u16_t variable)
{
  u8_t str[100] = "";
  std_strcat(str, (u8_t *)"[");
  std_strcat(str, log_type);
  std_strcat(str, (u8_t *)"]");
  std_strcat(str, (u8_t *)"[");
  std_strcat(str, (u8_t *)tag);
  std_strcat(str, (u8_t *)"] ");
  std_strcat(str, (u8_t *)data);

  if (variable != NULL)
  {
    u8_t buff[5];
    std_itoa(variable, buff, 10);
    std_strcat(str, (u8_t *)": ");
    std_strcat(str, buff);
  }

  std_strcat(str, (u8_t *)"\r\n");
  service_soft_uart_send_string(str);
}