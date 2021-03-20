/*
 * eeprom.h
 *
 *  Created on: Mar 13, 2021
 *      Author: Lenovo
 */

#ifndef HAL_EEPROM_H_
#define HAL_EEPROM_H_

#include "../../includes/types.h"
#include "../../includes/atmega16.h"
#include "../../MCAL/I2C/i2c.h"

/*******************************************************************************
 *                 					 Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

typedef enum
{
	EEPROM_FAIL,
	EEPROM_SUCCESS,
}eeprom_error_t;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
eeprom_error_t hal_eeprom_init(void);
eeprom_error_t hal_eeprom_writeByte(u16_t u16addr,u8_t u8data);
eeprom_error_t hal_eeprom_readByte(u16_t u16addr,u8_t *u8data);


#endif /* HAL_EEPROM_H_ */
