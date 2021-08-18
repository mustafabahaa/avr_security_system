/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** i2c.c
 **************************************************************************
 **                              Includes                                 *
 *************************************************************************/
#include "eeprom.h"
/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

eeprom_error_t hal_eeprom_init(void)
{
  eeprom_error_t error = EEPROM_SUCCESS;

  i2c_t i2c;
  i2c.bitRate = RATE_400KB;

  /* just initialize the I2C(TWI) module inside the MC */
  if (I2C_STATE_SUCCESS != mcal_TWI_init(&i2c))
  {
    error = EEPROM_FAIL;
  }
  else
  {
    /* i2c initialized */
  }
  return error;
}

eeprom_error_t hal_eeprom_writeByte(u8_t address, u8_t u8data)
{
  eeprom_error_t error = EEPROM_SUCCESS;

  /* Send the Start Bit */
  if (I2C_STATE_SUCCESS != mcal_TWI_start())
  {
    error = EEPROM_FAIL;
  }
  else if (TW_START != mcal_TWI_getStatus())
  {
    error = EEPROM_FAIL;
  }
  else if (I2C_STATE_SUCCESS != mcal_TWI_write(EEPROM_ADDRESS + I2C_WRITE_COMMAND))
  {
    error = EEPROM_FAIL;
  }
  else if (TW_MT_SLA_W_ACK != mcal_TWI_getStatus())
  {
    error = EEPROM_FAIL;
  }
  /* Send the required memory location address */
  else if (I2C_STATE_SUCCESS != mcal_TWI_write(address))
  {
    error = EEPROM_FAIL;
  }
  else if (TW_MT_DATA_ACK != mcal_TWI_getStatus())
  {
    error = EEPROM_FAIL;
  }
  /* write byte to eeprom */
  else if (I2C_STATE_SUCCESS != mcal_TWI_write(u8data))
  {
    error = EEPROM_FAIL;
  }
  else if (TW_MT_DATA_ACK != mcal_TWI_getStatus())
  {
    error = EEPROM_FAIL;
  }
  /* Send the Stop Bit */
  else if (I2C_STATE_SUCCESS != mcal_TWI_stop())
  {
    error = EEPROM_FAIL;
  }
  else
  {
    /* EEPROM write success */
  }
  return error;
}

eeprom_error_t hal_eeprom_readByte(u8_t address, u8_t *u8data)
{
  eeprom_error_t error = EEPROM_SUCCESS;

  /* Send the Start Bit */
  if (I2C_STATE_SUCCESS != mcal_TWI_start())
  {
    error = EEPROM_FAIL;
  }
  else if (TW_START != mcal_TWI_getStatus())
  {
    error = EEPROM_FAIL;
  }
  else if (I2C_STATE_SUCCESS != mcal_TWI_write(EEPROM_ADDRESS + I2C_WRITE_COMMAND))
  {
    error = EEPROM_FAIL;
  }
  else if (TW_MT_SLA_W_ACK != mcal_TWI_getStatus())
  {
    error = EEPROM_FAIL;
  }
  /* write byte to eeprom */
  else if (I2C_STATE_SUCCESS != mcal_TWI_write(address))
  {
    error = EEPROM_FAIL;
  }
  else if (TW_MT_DATA_ACK != mcal_TWI_getStatus())
  {
    error = EEPROM_FAIL;
  }
  /* Send the Repeated Start Bit */
  else if (I2C_STATE_SUCCESS != mcal_TWI_start())
  {
    error = EEPROM_FAIL;
  }
  else if (TW_REP_START != mcal_TWI_getStatus())
  {
    error = EEPROM_FAIL;
  }
  else if (I2C_STATE_SUCCESS != mcal_TWI_write(EEPROM_ADDRESS + I2C_READ_COMMAND))
  {
    error = EEPROM_FAIL;
  }
  else if (TW_MT_SLA_R_ACK != mcal_TWI_getStatus())
  {
    error = EEPROM_FAIL;
  }
  /* Read Byte from Memory without send ACK */
  else if (I2C_STATE_SUCCESS != mcal_TWI_readWithNACK(u8data))
  {
    error = EEPROM_FAIL;
  }
  else if (TW_MR_DATA_NACK != mcal_TWI_getStatus())
  {
    error = EEPROM_FAIL;
  }
  /* Send the Stop Bit */
  else if (I2C_STATE_SUCCESS != mcal_TWI_stop())
  {
    error = EEPROM_FAIL;
  }
  else
  {
    /* EEPROM read success */
  }
  return error;
}
