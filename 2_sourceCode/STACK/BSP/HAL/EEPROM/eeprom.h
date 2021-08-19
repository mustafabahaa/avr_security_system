/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** eeprom.h
 **************************************************************************/
#ifndef HAL_EEPROM_H_
#define HAL_EEPROM_H_
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "types.h"
#include "atmega32.h"
#include "i2c.h"
/***************************************************************************
 *                 					 Macros                                        *
 **************************************************************************/
#define EEPROM_ADDRESS 0xa0

/***************************************************************************
 *                 					 Types                                         *
 **************************************************************************/
typedef enum
{
	EEPROM_FAIL,
	EEPROM_SUCCESS,
}eeprom_error_t;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** hal_eeprom_init()
 **
 ** parameters: void
 ** return    : eeprom_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for eeprom
 **************************************************************************/
eeprom_error_t hal_eeprom_init(void);

/**************************************************************************
 ** hal_eeprom_writeByte()
 **
 ** parameters: u8_t address,u8_t u8data
 ** return    : eeprom_error_t
 ***************************************************************************
 ** this function is used to write 8bit data to specific address in eeprom
 **************************************************************************/
eeprom_error_t hal_eeprom_writeByte(u8_t address,u8_t u8data);

/**************************************************************************
 ** hal_eeprom_readByte()
 **
 ** parameters: u8_t address,u8_t *u8data
 ** return    : eeprom_error_t
 ***************************************************************************
 ** this function is used to read 8bit data to specific address from eeprom
 **************************************************************************/
eeprom_error_t hal_eeprom_readByte(u8_t address,u8_t *u8data);


#endif /* HAL_EEPROM_H_ */
