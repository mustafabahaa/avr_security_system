
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

i2c_error_t TWI_init(void)
{
	i2c_error_t error = I2C_STATE_SUCCESS;

	/* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
	register(TWBR) = 0x02;
	register(TWSR) = 0x00;

	/* Two Wire Bus address my address if any master device want to call me:
	 * 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */

	register(TWAR) = 0b00000010; // my address = 0x01 :)

	/* enable TWI */
	set_bit(TWCR,TWEN);

	return error;
}

i2c_error_t TWI_start(void)
{
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
	while(bit_is_clear(TWCR,TWINT));

	return error;
}

i2c_error_t TWI_stop(void)
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

i2c_error_t TWI_write(u8_t data)
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
	while(bit_is_clear(TWCR,TWINT));

	return error;
}

i2c_error_t TWI_readWithACK(u8_t* data)
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
	while(bit_is_clear(TWCR,TWINT));

	/* Read Data */
	*data = TWDR;

	return error;
}

i2c_error_t TWI_readWithNACK(u8_t* data)
{
	i2c_error_t error = I2C_STATE_SUCCESS;

	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */

	set_bit(TWCR,TWINT);
	set_bit(TWCR,TWEN);

	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while(bit_is_clear(TWCR,TWINT));

	/* Read Data */
	*data = TWDR;

	return error;

}

i2c_error_t TWI_getStatus(u8_t *status)
{
	i2c_error_t error = I2C_STATE_SUCCESS;

	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	*status = register(TWSR) & 0xF8;

	return error;

}
