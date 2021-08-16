
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

i2c_error_t mcal_TWI_init(i2c_t* i2c)
{
	i2c_error_t error = I2C_STATE_SUCCESS;

	register(TWBR) = 0x02;
  register(TWAR) =0x02;



#if 0
	if ( RATE_100KB == i2c->bitRate)
	{
		/*TWBR  = ((F_CPU / SCLfreq) – 16) / (2 * Prescaler)*/
		register(TWBR) = ((F_CPU / 100000) - 16) / 2;
	}
	else if (RATE_400KB == i2c->bitRate)
	{
		/*TWBR  = ((F_CPU / SCLfreq) – 16) / (2 * Prescaler)*/
		register(TWBR) = ((F_CPU / 400000) - 16) / 2;
	}
	else
	{
		error = I2C_STATE_INVALID_BIT_RATE;
	}
#endif 

	/* Two Wire Bus address my address if any master device want to call me:
	 * 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */


	/* enable TWI */
	set_bit(TWCR,TWEN);
	set_bit(TWCR,TWEA);

  register(TWSR)=0x00;	// no prescaler used 

	return error;
}

i2c_error_t mcal_TWI_start(void)
{
  static u8_t x = 0;
	i2c_error_t error = I2C_STATE_SUCCESS;

	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	set_bit(TWCR,TWINT);
	set_bit(TWCR,TWSTA);
	set_bit(TWCR,TWEN);

	/* Wait for TWINT flag set in TWCR Register
	 *  (start bit is send successfully) */
	while (!(register(TWCR) & (1 << TWINT)));

  //set_bit(TWCR,TWINT);
  if (x == 1)
  {
     // set_bit(BASE_C + OFFSET_PORT, 3);         
  }
      x++;                    
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
	set_bit(TWCR,TWINT);
	set_bit(TWCR,TWSTO);
	set_bit(TWCR,TWEN);

	return error;
}

i2c_error_t mcal_TWI_write(u8_t data)
{
	i2c_error_t error = I2C_STATE_SUCCESS;

	/* Put data On TWI data Register */
	register(TWDR) = data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	set_bit(TWCR,TWINT);
	set_bit(TWCR,TWEN);

	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while (!(register(TWCR) & (1 << TWINT)));

	return error;
}

i2c_error_t mcal_TWI_readWithACK(u8_t* data)
{
	i2c_error_t error = I2C_STATE_SUCCESS;

	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */
	set_bit(TWCR,TWINT);
	set_bit(TWCR,TWEN);
	set_bit(TWCR,TWEA);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (!(register(TWCR) & (1 << TWINT)));

	/* Read Data */
	*data = TWDR;

	return error;
}

i2c_error_t mcal_TWI_readWithNACK(u8_t* data)
{
	i2c_error_t error = I2C_STATE_SUCCESS;

	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */

	set_bit(TWCR,TWINT);
	set_bit(TWCR,TWEN);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (!(register(TWCR) & (1 << TWINT)));

	/* Read Data */
	*data = TWDR;

	return error;

}

i2c_error_t mcal_TWI_getStatus(u8_t *status)
{
	i2c_error_t error = I2C_STATE_SUCCESS;

	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	*status = register(TWSR) & 0xF8;

	return error;

}
