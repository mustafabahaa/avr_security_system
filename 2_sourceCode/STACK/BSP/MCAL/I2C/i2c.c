
/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** i2c.c
 **************************************************************************
 **                              Includes                                 *
 *************************************************************************/
#include "i2c.h"
/*************************************************************************/
/*                          Global Variables                             */
/*************************************************************************/
static u8_t *TAG = (u8_t *)"I2C";
/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

i2c_error_t mcal_i2c_init(i2c_t *i2c)
{
  i2c_error_t error = I2C_STATE_SUCCESS;

  logger_write_debug_println_with_variable(
      LOG_MCAL,
      TAG,
      (u8_t *)"I2C Bus speed is confgiured",
      (u16_t)i2c->bitRate);

  if (RATE_100KB == i2c->bitRate)
  {
    /*TWBR  = ((F_CPU / SCLfreq) – 16) / (2 * Prescaler)*/
    reg_write(TWBR, (u8_t)(((F_CPU / 100000) - 16) / 2))
  }
  else if (RATE_400KB == i2c->bitRate)
  {
    /*TWBR  = ((F_CPU / SCLfreq) – 16) / (2 * Prescaler)*/
    reg_write(TWBR, (u8_t)(((F_CPU / 400000) - 16) / 2))
  }
  else
  {
    error = I2C_STATE_INVALID_BIT_RATE;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied i2c bus speed");
  }

  /* Two Wire Bus address my address if any master device want to call me:
	 * 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */

  /* enable i2c */
  set_bit(TWCR, TWEN);
  set_bit(TWCR, TWEA);

  /* no prescaler used */
  reg_write(TWSR, 0x00);

  logger_write_debug_println(LOG_MCAL, TAG, (u8_t *)"I2C is configured");

  return error;
}

i2c_error_t mcal_i2c_start(void)
{
  i2c_error_t error = I2C_STATE_SUCCESS;

  /*
	 * Clear the i2cNT flag before sending the start bit i2cNT=1
	 * send the start bit by TWSTA=1
	 * Enable i2c Module TWEN=1
	 */
  reg_write(TWCR,
            (en_bit(i2cNT) |
             en_bit(TWSTA) |
             en_bit(TWEN)));

  /* Wait for i2cNT flag set in TWCR Register
	 *  (start bit is send successfully) */
  while (bit_is_clr(TWCR, i2cNT))
    ;

  return error;
}

i2c_error_t mcal_i2c_stop(void)
{
  i2c_error_t error = I2C_STATE_SUCCESS;

  /*
	 * Clear the i2cNT flag before sending the stop bit i2cNT=1
	 * send the stop bit by TWSTO=1
	 * Enable i2c Module TWEN=1
	 */
  set_bit(TWCR, i2cNT);
  set_bit(TWCR, TWSTO);
  set_bit(TWCR, TWEN);

  return error;
}

i2c_error_t mcal_i2c_write(u8_t data)
{
  i2c_error_t error = I2C_STATE_SUCCESS;

  /* Put data On i2c data Register */
  reg_write(TWDR, data);
  /*
	 * Clear the i2cNT flag before sending the data i2cNT=1
	 * Enable i2c Module TWEN=1
	 */
  reg_write(TWCR,
            (en_bit(i2cNT) | en_bit(TWEN)));

  /* Wait for i2cNT flag set in TWCR Register(data is send successfully) */
  //while (bit_is_clr(TWCR,i2cNT));
  while (bit_is_clr(TWCR, i2cNT))
    ;

  return error;
}

i2c_error_t mcal_i2c_read_ack(u8_t *data)
{
  i2c_error_t error = I2C_STATE_SUCCESS;

  /*
	 * Clear the i2cNT flag before reading the data i2cNT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable i2c Module TWEN=1
	 */
  set_bit(TWCR, i2cNT);
  set_bit(TWCR, TWEN);
  set_bit(TWCR, TWEA);

  /* Wait for i2cNT flag set in TWCR Register (data received successfully) */
  while (bit_is_clr(TWCR, i2cNT))
    ;

  /* Read Data */
  reg_read(TWDR, *data);

  return error;
}

i2c_error_t mcal_i2c_read_nack(u8_t *data)
{
  i2c_error_t error = I2C_STATE_SUCCESS;

  /*
	 * Clear the i2cNT flag before reading the data i2cNT=1
	 * Enable i2c Module TWEN=1
	 */

  set_bit(TWCR, i2cNT);
  set_bit(TWCR, TWEN);

  /* Wait for i2cNT flag set in TWCR Register (data received successfully) */
  while (bit_is_clr(TWCR, i2cNT))
    ;

  /* Read Data */
  reg_read(TWDR, *data);

  return error;
}

u8_t mcal_i2c_getStatus()
{
  u8_t status = 0;
  return reg_mask_read(TWSR, STATUS_REG_MASK, status);
}
