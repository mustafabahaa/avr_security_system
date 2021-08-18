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
#include "types.h"
#include "atmega32.h"
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

// I2C write command
#define I2C_WRITE_COMMAND 0x00

// I2C read command
#define I2C_READ_COMMAND 0x01

// I2C Status register mask 
#define STATUS_REG_MASK 0xF8

/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/
typedef enum
{
	I2C_STATE_SUCCESS=1,
	I2C_STATE_ERROR,
	I2C_STATE_INVALID_BIT_RATE,
} i2c_error_t;

typedef enum
{
	RATE_100KB=1,
	RATE_400KB,
} i2c_bit_rate_t;

typedef struct
{
	i2c_bit_rate_t bitRate;
} i2c_t;
/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** mcal_TWI_init()
 **
 ** parameters: i2c_t* i2c
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for i2c
 **************************************************************************/
i2c_error_t mcal_TWI_init(i2c_t* i2c);

/**************************************************************************
 ** mcal_TWI_start()
 **
 ** parameters: void
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to send i2c start bit
 **************************************************************************/
i2c_error_t mcal_TWI_start(void);

/**************************************************************************
 ** mcal_TWI_stop()
 **
 ** parameters: void
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to send i2c stop bit
 **************************************************************************/
i2c_error_t mcal_TWI_stop(void);

/**************************************************************************
 ** mcal_TWI_write()
 **
 ** parameters: u8_t data
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to send data over i2c
 **************************************************************************/
i2c_error_t mcal_TWI_write(u8_t data);

/**************************************************************************
 ** mcal_TWI_readWithACK()
 **
 ** parameters: u8_t data
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to read with Acknowledge
 **************************************************************************/
i2c_error_t mcal_TWI_readWithACK(u8_t* data);

/**************************************************************************
 ** mcal_TWI_readWithNACK()
 **
 ** parameters: u8_t* data
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to read with NOT Acknowledge
 **************************************************************************/
i2c_error_t mcal_TWI_readWithNACK(u8_t* data);

/**************************************************************************
 ** mcal_TWI_getStatus()
 **
 ** parameters: void
 ** return    : status
 ***************************************************************************
 ** this function is used to get status of I2C
 **************************************************************************/
u8_t mcal_TWI_getStatus();


#endif /* _I2C_H_ */
