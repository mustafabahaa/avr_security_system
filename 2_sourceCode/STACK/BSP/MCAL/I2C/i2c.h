/***************************************************************************
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
#include "logger.h"
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
	RATE_100KB=100,
	RATE_400KB=400,
} i2c_bit_rate_t;

typedef struct
{
	i2c_bit_rate_t bitRate;
} i2c_t;
/**************************************************************************/
/*                           Public Functions                             */
/***************************************************************************
 ** mcal_i2c_init()
 **
 ** parameter: i2c_t* i2c
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for i2c
 **************************************************************************/
i2c_error_t mcal_i2c_init(i2c_t* i2c);

/***************************************************************************
 ** mcal_i2c_start()
 **
 ** parameter: void
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to send i2c start bit
 **************************************************************************/
i2c_error_t mcal_i2c_start(void);

/***************************************************************************
 ** mcal_i2c_stop()
 **
 ** parameter: void
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to send i2c stop bit
 **************************************************************************/
i2c_error_t mcal_i2c_stop(void);

/***************************************************************************
 ** mcal_i2c_write()
 **
 ** parameter: u8_t data
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to send data over i2c
 **************************************************************************/
i2c_error_t mcal_i2c_write(u8_t data);

/***************************************************************************
 ** mcal_i2c_read_ack()
 **
 ** parameter: u8_t data
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to read with Acknowledge
 **************************************************************************/
i2c_error_t mcal_i2c_read_ack(u8_t* data);

/***************************************************************************
 ** mcal_i2c_read_nack()
 **
 ** parameter: u8_t* data
 ** return    : i2c_error_t
 ***************************************************************************
 ** this function is used to read with NOT Acknowledge
 **************************************************************************/
i2c_error_t mcal_i2c_read_nack(u8_t* data);

/***************************************************************************
 ** mcal_i2c_getStatus()
 **
 ** parameter: void
 ** return    : status
 ***************************************************************************
 ** this function is used to get status of I2C
 **************************************************************************/
u8_t mcal_i2c_getStatus();


#endif /* _I2C_H_ */
