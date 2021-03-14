/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** i2c.h
 **************************************************************************/
#ifndef _I2C_H_
#define _I2C_H_
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "./../../includes/types.h"
#include "../../includes/atmega16.h"
/**************************************************************************/
/*                              Macros                                    */
/**************************************************************************/
/* I2C Status Bits in the TWSR Register */

// start has been sent
#define TW_START         0x08

// repeated start
#define TW_REP_START     0x10

// Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_W_ACK  0x18

// Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK  0x40

// Master transmit data and ACK has been received from Slave.
#define TW_MT_DATA_ACK   0x28

// Master received data and send ACK to slave
#define TW_MR_DATA_ACK   0x50

// Master received data but doesn't send ACK to slave
#define TW_MR_DATA_NACK  0x58

/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/
typedef enum
{
	I2C_STATE_SUCCESS,
	I2C_STATE_ERROR,
} i2c_error_t;
/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** TWI_init()
 **
 ** parameters: void
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for i2c
 **************************************************************************/
i2c_error_t TWI_init(void);

/**************************************************************************
 ** TWI_start()
 **
 ** parameters: void
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to send i2c start bit
 **************************************************************************/
i2c_error_t TWI_start(void);

/**************************************************************************
 ** TWI_stop()
 **
 ** parameters: void
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to send i2c stop bit
 **************************************************************************/
i2c_error_t TWI_stop(void);

/**************************************************************************
 ** TWI_write()
 **
 ** parameters: u8_t data
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to send data over i2c
 **************************************************************************/
i2c_error_t TWI_write(u8_t data);

/**************************************************************************
 ** TWI_readWithACK()
 **
 ** parameters: u8_t data
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to read with Acknowledge
 **************************************************************************/
i2c_error_t TWI_readWithACK(u8_t* data);

/**************************************************************************
 ** TWI_readWithNACK()
 **
 ** parameters: u8_t* data
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to read with NOT Acknowledge
 **************************************************************************/
i2c_error_t TWI_readWithNACK(u8_t* data);

/**************************************************************************
 ** TWI_getStatus()
 **
 ** parameters: u8_t* data
 ** return    : status
 ***************************************************************************
 ** this function is used to get status of I2C
 **************************************************************************/
i2c_error_t TWI_getStatus(u8_t* status);


#endif /* _I2C_H_ */
