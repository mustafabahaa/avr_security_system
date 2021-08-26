
/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** spi.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "spi.h"
/*************************************************************************/
/*                          Global Variables                             */
/*************************************************************************/
static u8_t *TAG = (u8_t *)"SPI";
/**************************************************************************/
/*                     Functions Implementation                           */
/**************************************************************************/
spi_error_t mcal_spi_init(spi_t *spi)
{
  spi_error_t error = SPI_STATE_SUCCESS;

  switch (spi->mode)
  {
  case SPI_MODE_MASTER:
  {
    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured in master mode");
    switch (spi->clock)
    {
    case SPI_SCK_FREQUANCY_FOC_4:
    {
      /* default */
      logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured clock is CLK/4");
      break;
    }

    case SPI_SCK_FREQUANCY_FOC_16:
    {
      set_bit(SPCR, SPR0);
      logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured clock is CLK/16");

      break;
    }

    case SPI_SCK_FREQUANCY_FOC_64:
    {
      set_bit(SPCR, SPR1);
      logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured clock is CLK/64");
      break;
    }

    case SPI_SCK_FREQUANCY_FOC_128:
    {
      set_bit(SPCR, SPR0);
      set_bit(SPCR, SPR1);
      logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"configured clock is CLK/128");
      break;
    }

    default:
    {
      error = SPI_STATE_INVALID_CLOCK;
      logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalid clock");
      break;
    }
    }

    if (spi->features.double_speed)
    {
      logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"double speed feature is enabled");
      set_bit(SPSR, SPI2X);
    }
    else
    {
      logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"double speed feature is disabled");
      clr_bit(SPSR, SPI2X);
    }

    mcal_gpio_pin_init(spi->pinning.base_addr, spi->pinning.mosi_pin, DIR_OUTPUT);
    mcal_gpio_pin_init(spi->pinning.base_addr, spi->pinning.sck_pin, DIR_OUTPUT);
    mcal_gpio_pin_init(spi->pinning.base_addr, spi->pinning.ss_pin, DIR_OUTPUT);
    mcal_gpio_pin_init(spi->pinning.base_addr, spi->pinning.miso_pin, DIR_INPUT_PULLDOWN);
    reg_write(SPCR, en_bit(SPE) | en_bit(MSTR));

    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"port and pins is configured for master mode");

    break;
  }

  case SPI_MODE_SLAVE:
  {
    mcal_gpio_pin_init(spi->pinning.base_addr, spi->pinning.mosi_pin, DIR_INPUT_PULLDOWN);
    mcal_gpio_pin_init(spi->pinning.base_addr, spi->pinning.sck_pin, DIR_INPUT_PULLDOWN);
    mcal_gpio_pin_init(spi->pinning.base_addr, spi->pinning.ss_pin, DIR_INPUT_PULLDOWN);
    mcal_gpio_pin_init(spi->pinning.base_addr, spi->pinning.miso_pin, DIR_OUTPUT);
    reg_write(SPCR, en_bit(SPE));

    /*enable global interrupts*/
    setGlobalInterrupt;
    set_bit(SPCR, SPIE);

    logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"port and pins is configured for slave mode");

    break;
  }

  default:
  {
    error = SPI_STATE_INVALID_MODE;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalid mode");
    break;
  }
  }

  return error;
}

spi_error_t mcal_spi_send_byte(u8_t data)
{
  spi_error_t error = SPI_STATE_SUCCESS;

  reg_write(SPDR, data);

  /* check if operation of transmit or receive is running */
  while (bit_is_clr(SPSR, SPIF))
    ;

  return error;
}

spi_error_t mcal_spi_receive_byte(u8_t *data)
{
  spi_error_t error = SPI_STATE_SUCCESS;

  /* check if operation of transmit or receive is running */
  while (bit_is_clr(SPSR, SPIF))
    ;

  reg_read(SPDR, *data);

  return error;
}

spi_error_t mcal_spi_swap_byte(u8_t *data)
{
  spi_error_t error = SPI_STATE_SUCCESS;

  /* send 0XFF to salve to shift all the 8 bits in the data buffer
	    in the slave and receive it at the master , if you don't 
		understand this please read more on SPI communication protocol */
  if (SPI_STATE_SUCCESS != mcal_spi_send_byte(DUMB))
  {
    error = SPI_STATE_ERROR;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"send byte failed");
  }
  else
  {
    reg_read(SPDR, *data);
  }
  /* receive the value you wanted from slave */
  return error;
}
