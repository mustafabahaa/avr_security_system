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

	/* just initialize the I2C(TWI) module inside the MC */
	if (I2C_STATE_SUCCESS == TWI_init())
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
	if (I2C_STATE_SUCCESS == TWI_start())
	{
		TWI_getStatus(&status);
		if (status == TW_START)
		{

			/* Send the device address, we need to get A8 A9 A10 address bits from the
			 * memory location address and R/W=0 (write) */
			if (I2C_STATE_SUCCESS == TWI_write((u8_t)(0xA0 | ((u16addr & 0x0700)>>7))))
			{
				TWI_getStatus(&status);
				if ( status == TW_MT_SLA_W_ACK )
				{
					/* Send the required memory location address */
					if(I2C_STATE_SUCCESS == TWI_write((u8_t)(u16addr)))
					{
						TWI_getStatus(&status);
						if( status ==  TW_MT_DATA_ACK)
						{
							/* write byte to eeprom */
							if(I2C_STATE_SUCCESS == TWI_write(u8data))
							{
								TWI_getStatus(&status);
								if ( status == TW_MT_DATA_ACK )
								{
									/* Send the Stop Bit */
									TWI_stop();
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
eeprom_error_t EEPROM_readByte(u16_t u16addr, u8_t *u8data)
{
	eeprom_error_t error = EEPROM_SUCCESS;
	u8_t status = 0;
	/* Send the Start Bit */
	if (I2C_STATE_SUCCESS == TWI_start())
	{
		TWI_getStatus(&status);
		if (status == TW_START)
		{
			/* Send the device address, we need to get A8 A9 A10 address bits from the
			 * memory location address and R/W=0 (write) */
			if (I2C_STATE_SUCCESS == TWI_write((u8_t)((0xA0) | ((u16addr & 0x0700)>>7))))
			{
				TWI_getStatus(&status);
				if(status == TW_MT_SLA_W_ACK)
				{
					/* write byte to eeprom */
					if(I2C_STATE_SUCCESS == TWI_write((u8_t)(u16addr)))
					{
						TWI_getStatus(&status);
						if(status == TW_MT_DATA_ACK)
						{
							/* Send the Repeated Start Bit */
							if (I2C_STATE_SUCCESS ==TWI_start())
							{
								TWI_getStatus(&status);
								if(status ==TW_REP_START )
								{
									/* Send the device address, we need to get A8 A9 A10 address bits from the
									 * memory location address and R/W=1 (Read) */
									if(I2C_STATE_SUCCESS ==TWI_write((u8_t)((0xA0) | ((u16addr & 0x0700)>>7) | 1)))
									{
										TWI_getStatus(&status);
										if(status ==TW_MT_SLA_R_ACK )
										{
											/* Read Byte from Memory without send ACK */
											if ((*u8data) = TWI_readWithNACK())
											{
												TWI_getStatus(&status);
												if(status ==TW_MR_DATA_NACK )
												{
													/* Send the Stop Bit */
													TWI_stop();
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
