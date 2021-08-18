
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
/*                     Functions Implementation                          */
/*************************************************************************/

i2c_error_t mcal_TWI_init(i2c_t *i2c)
{
  i2c_error_t error = I2C_STATE_SUCCESS;

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
  }

  /* Two Wire Bus address my address if any master device want to call me:
	 * 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */

  /* enable TWI */
  set_bit(TWCR, TWEN);
  set_bit(TWCR, TWEA);

  /* no prescaler used */
  reg_write(TWSR, 0x00);

  return error;
}

i2c_error_t mcal_TWI_start(void)
{
  i2c_error_t error = I2C_STATE_SUCCESS;

  /*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
  reg_write(TWCR,
            (en_bit(TWINT) |
             en_bit(TWSTA) |
             en_bit(TWEN)));

  /* Wait for TWINT flag set in TWCR Register
	 *  (start bit is send successfully) */
  while (bit_is_clr(TWCR, TWINT))
    ;

  return error;
}

i2c_error_t mcal_TWI_stop(void)
{
  i2c_error_t error = I2C_STATE_SUCCESS;

  /*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */
  set_bit(TWCR, TWINT);
  set_bit(TWCR, TWSTO);
  set_bit(TWCR, TWEN);

  return error;
}

i2c_error_t mcal_TWI_write(u8_t data)
{
  i2c_error_t error = I2C_STATE_SUCCESS;

  /* Put data On TWI data Register */
  reg_write(TWDR, data);
  /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
  reg_write(TWCR,
            (en_bit(TWINT) | en_bit(TWEN)));

  /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
  //while (bit_is_clr(TWCR,TWINT));
  while (bit_is_clr(TWCR, TWINT))
    ;

  return error;
}

i2c_error_t mcal_TWI_readWithACK(u8_t *data)
{
  i2c_error_t error = I2C_STATE_SUCCESS;

  /*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
  set_bit(TWCR, TWINT);
  set_bit(TWCR, TWEN);
  set_bit(TWCR, TWEA);

  /* Wait for TWINT flag set in TWCR Register (data received successfully) */
  while (bit_is_clr(TWCR, TWINT))
    ;

  /* Read Data */
  reg_read(TWDR, *data);

  return error;
}

i2c_error_t mcal_TWI_readWithNACK(u8_t *data)
{
  i2c_error_t error = I2C_STATE_SUCCESS;

  /*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */

  set_bit(TWCR, TWINT);
  set_bit(TWCR, TWEN);

  /* Wait for TWINT flag set in TWCR Register (data received successfully) */
  while (bit_is_clr(TWCR, TWINT))
    ;

  /* Read Data */
  reg_read(TWDR, *data);

  return error;
}

u8_t mcal_TWI_getStatus()
{
  u8_t status = 0 ;
  return reg_mask_read(TWSR, STATUS_REG_MASK, status);
}
