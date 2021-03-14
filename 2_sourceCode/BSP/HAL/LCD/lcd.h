/*
 * lcd.h
 *
 *  Created on: Mar 11, 2021
 *      Author: Lenovo
 */

#ifndef HAL_LCD_H_
#define HAL_LCD_H_

#include <stdlib.h>

#include "../../includes/types.h"
#include "../../includes/atmega16.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* LCD Data bits mode configuration */
#define DATA_BITS_MODE 8

/* Use higher 4 bits in the data port */
#if (DATA_BITS_MODE == 4)
#define UPPER_PORT_PINS
#endif

#define PORTD   (0x32)

#define PD4     4
#define PD5     5
#define PD6     6

/* LCD HW Pins */
#define RS PD4
#define RW PD5
#define E  PD6
#define LCD_CTRL_PORT (BASE_D + OFFSET_PORT)
#define LCD_CTRL_PORT_DIR (BASE_D + OFFSET_DIR)

#define LCD_DATA_PORT (BASE_C + OFFSET_PORT)
#define LCD_DATA_PORT_DIR (BASE_C + OFFSET_DIR)

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_sendCommand(u8_t command);
void LCD_displayCharacter(u8_t data);
void LCD_displaystring(const char *str);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_displaystringRowColumn(u8_t row,u8_t col,const char *str);
void LCD_goToRowColumn(u8_t row,u8_t col);
void LCD_intgerToString(int data);


#endif /* HAL_LCD_H_ */
