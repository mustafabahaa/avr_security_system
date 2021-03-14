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
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void EEPROM_init(void);
u8_t EEPROM_writeByte(u16_t u16addr,u8_t u8data);
u8_t EEPROM_readByte(u16_t u16addr,u8_t *u8data);


#endif /* HAL_EEPROM_H_ */
