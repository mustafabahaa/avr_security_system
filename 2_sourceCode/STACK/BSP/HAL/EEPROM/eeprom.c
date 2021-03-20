/*
 * eeprom.c
 *
 *  Created on: Mar 13, 2021
 *      Author: Lenovo
 */


#include "eeprom.h"

eeprom_error_t hal_eeprom_init(void)
{
	eeprom_error_t error = EEPROM_SUCCESS;

	i2c_t i2c;
	i2c.bitRate = RATE_100KB;

	/* just initialize the I2C(TWI) module inside the MC */
	if (I2C_STATE_SUCCESS == mcal_TWI_init(&i2c))
	{
		/* i2c initialized */
	}
	else
	{
		error = EEPROM_FAIL;
	}
	return error;
}

eeprom_error_t hal_eeprom_writeByte(u16_t u16addr, u8_t u8data)
{
	eeprom_error_t error = EEPROM_SUCCESS;
	u8_t status = 0;

	/* Send the Start Bit */
	if (I2C_STATE_SUCCESS == mcal_TWI_start())
	{
		mcal_TWI_getStatus(&status);

		if (status == TW_START)
		{
			/* Send the device address, we need to get A8 A9 A10 address bits from the
			 * memory location address and R/W=0 (write) */
			if (I2C_STATE_SUCCESS == mcal_TWI_write((u8_t)(0xA0 | ((u16addr & 0x0700)>>7))))
			{
				mcal_TWI_getStatus(&status);
				if ( status == TW_MT_SLA_W_ACK )
				{
					/* Send the required memory location address */
					if(I2C_STATE_SUCCESS == mcal_TWI_write((u8_t)(u16addr)))
					{
						mcal_TWI_getStatus(&status);
						if( status ==  TW_MT_DATA_ACK)
						{
							/* write byte to eeprom */
							if(I2C_STATE_SUCCESS == mcal_TWI_write(u8data))
							{
								mcal_TWI_getStatus(&status);
								if ( status == TW_MT_DATA_ACK )
								{
									/* Send the Stop Bit */
									if (I2C_STATE_SUCCESS == mcal_TWI_stop())
									{
										/* EEPROM write success */
									}
									else
									{
										error = EEPROM_FAIL;
									}
								}
								else
								{
									error=EEPROM_FAIL;
								}
							}
							else
							{
								error = EEPROM_FAIL;
							}
						}
						else
						{
							error = EEPROM_FAIL;
						}
					}
					else
					{
						error = EEPROM_FAIL;
					}
				}
				else
				{
					error = EEPROM_FAIL;
				}
			}

			else
			{
				error = EEPROM_FAIL;
			}

		}
		else
		{
			error = EEPROM_FAIL;
		}
	}
	else
	{
		error = EEPROM_FAIL;
	}
	return error;

}
eeprom_error_t hal_eeprom_readByte(u16_t u16addr, u8_t *u8data)
{
	eeprom_error_t error = EEPROM_SUCCESS;
	u8_t status = 0;

	/* Send the Start Bit */
	if (I2C_STATE_SUCCESS == mcal_TWI_start())
	{
		mcal_TWI_getStatus(&status);
		if (status == TW_START)
		{
			/* Send the device address, we need to get A8 A9 A10 address bits from the
			 * memory location address and R/W=0 (write) */
			if (I2C_STATE_SUCCESS == mcal_TWI_write((u8_t)((0xA0) | ((u16addr & 0x0700)>>7))))
			{
				mcal_TWI_getStatus(&status);
				if(status == TW_MT_SLA_W_ACK)
				{
					/* write byte to eeprom */
					if(I2C_STATE_SUCCESS == mcal_TWI_write((u8_t)(u16addr)))
					{
						mcal_TWI_getStatus(&status);
						if(status == TW_MT_DATA_ACK)
						{
							/* Send the Repeated Start Bit */
							if (I2C_STATE_SUCCESS == mcal_TWI_start())
							{
								mcal_TWI_getStatus(&status);
								if(status == TW_REP_START )
								{
									/* Send the device address, we need to get A8 A9 A10 address bits from the
									 * memory location address and R/W=1 (Read) */
									if(I2C_STATE_SUCCESS == mcal_TWI_write((u8_t)((0xA0) | ((u16addr & 0x0700)>>7) | 1)))
									{
										mcal_TWI_getStatus(&status);
										if(status ==TW_MT_SLA_R_ACK )
										{

											/* Read Byte from Memory without send ACK */
											if (I2C_STATE_SUCCESS == mcal_TWI_readWithNACK(u8data))
											{
												mcal_TWI_getStatus(&status);
												if(status ==TW_MR_DATA_NACK )
												{
													/* Send the Stop Bit */
													if (I2C_STATE_SUCCESS == mcal_TWI_stop())
													{
														/* EEPROM read success */
													}
													else
													{
														error = EEPROM_FAIL;
													}
												}
												else
												{
													error = EEPROM_FAIL;
												}

											}
											else
											{
												error = EEPROM_FAIL;
											}

										}
										else
										{
											error = EEPROM_FAIL;
										}
									}
									else
									{
										error = EEPROM_FAIL;
									}

								}
								else
								{
									error = EEPROM_FAIL;
								}

							}
							else
							{
								error = EEPROM_FAIL;
							}


						}
						else
						{
							error = EEPROM_FAIL;
						}

					}
					else
					{
						error = EEPROM_FAIL;
					}

				}
				else
				{
					error = EEPROM_FAIL;
				}
			}
			else
			{
				error= EEPROM_FAIL;
			}

		}
		else
		{
			error=EEPROM_FAIL;
		}

	}
	else
	{
		error = EEPROM_FAIL;
	}

	return error;
}
