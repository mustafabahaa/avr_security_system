/***************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** spi.h
 **************************************************************************/
#ifndef SPI_H_
#define SPI_H_
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "types.h"
#include "avr.h"
#include "gpio.h"
#include "logger.h"
/**************************************************************************/
/*                              Macros                                    */
/**************************************************************************/
#define DUMB 0XFF
/**************************************************************************/
/*                               Types                                    */
/**************************************************************************/
typedef enum
{
  SPI_STATE_SUCCESS = 1,
  SPI_STATE_ERROR,
  SPI_STATE_INVALID_ENDIAN,
  SPI_STATE_INVALID_MODE,
  SPI_STATE_INVALID_CLOCK,
} spi_error_t;

typedef enum
{
  SPI_SCK_FREQUANCY_FOC_4 = 1,
  SPI_SCK_FREQUANCY_FOC_16,
  SPI_SCK_FREQUANCY_FOC_64,
  SPI_SCK_FREQUANCY_FOC_128,
} spi_clock_t;

typedef enum
{
  SPI_MODE_MASTER = 1,
  SPI_MODE_SLAVE,
} spi_mode_t;

typedef struct
{
  u8_t double_speed;
} spi_features_t;

typedef struct
{
  u8_t base_addr;
  u8_t ss_pin;
  u8_t mosi_pin;
  u8_t miso_pin;
  u8_t sck_pin;
} spi_pinning_t;

typedef struct
{
  spi_pinning_t pinning;
  spi_mode_t mode;
  spi_clock_t clock;
  spi_features_t features;
} spi_t;

/**************************************************************************/
/*                           Public Functions                             */
/**************************************************************************
 ** mcal_spi_init()
 **
 ** parameter: spi_t* spi
 ** return    : spi_error_t
 ***************************************************************************
 ** this function is used to initialize SPI if it is in master mode or slave
 **************************************************************************/
spi_error_t mcal_spi_init(spi_t *spi);

/***************************************************************************
 ** mcal_spi_send_byte()
 **
 ** parameter: u8_t data
 ** return    : spi_error_t
 ***************************************************************************
 ** this function is used to send bytes "data"
 **************************************************************************/
spi_error_t mcal_spi_send_byte(u8_t data);

/***************************************************************************
 ** mcal_spi_receive_byte()
 **
 ** parameter: u8_t* data
 ** return    : spi_error_t
 ***************************************************************************
 ** this function is used to recieve bytes "data"
 **************************************************************************/
spi_error_t mcal_spi_receive_byte(u8_t *data);

/***************************************************************************
 ** mcal_spi_swap_byte()
 **
 ** parameter: u8_t* data
 ** return    : spi_error_t
 ***************************************************************************
** this function returns the 8 bits in the slave buffer by sending 
** dumb useless 8 bits to the buffer.
 **************************************************************************/
spi_error_t mcal_spi_swap_byte(u8_t *data);

#endif /* SPI_H_ */