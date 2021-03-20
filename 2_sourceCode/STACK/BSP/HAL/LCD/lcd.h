/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** lcd.h
 **************************************************************************/
#ifndef _LCD_H_
#define _LCD_H_
/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "./../../includes/types.h"
#include "./../../includes/atmega16.h"
#include "./../../MCAL/GPIO/gpio.h"
#include "./../../MCAL/PORT/port.h"
#include "./../../../Utility/std_library/std_library.h"
#include "./../../../Utility/delay/delay.h"
/**************************************************************************
 *                                   Macros                               *
 **************************************************************************/

/* LCD Commands */
#define CLEAR_COMMAND                 0x01
#define FOUR_BITS_DATA_MODE           0x02
#define TWO_LINE_LCD_Four_BIT_MODE    0x28
#define TWO_LINE_LCD_Eight_BIT_MODE   0x38
#define CURSOR_OFF                    0x0C
#define CURSOR_ON                     0x0E
#define SET_CURSOR_LOCATION           0x80

/*************************************************************************/
/*                                 Types                                 */
/*************************************************************************/
typedef enum
{
	LCD_SUCCESS,
	LCD_ERROR,
	LCD_command_ERROR,
	LCD_data_ERROR,
	LCD_MODE_ERROR,
	LCD_INVALID_TYPE,
} lcd_error_t;

typedef enum
{
	COMMAND,
	DISPLAY,
}lcd_data_types_t;

typedef enum
{
	MODE_4_BIT,
	MODE_8_BIT,
}lcd_mode_t;

typedef struct
{
	u8_t lcdDataPort;
	u8_t lcdControlPort;
	lcd_mode_t lcdMode;
	u8_t lcdRS;
	u8_t lcdRW;
	u8_t lcdE;
} lcd_t;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** hal_lcd_init()
 **
 ** parameters: lcd_t
 ** return    : lcd_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for LCD
 **************************************************************************/
lcd_error_t hal_lcd_init(lcd_t *lcd);
/**************************************************************************
 ** hal_lcd_sendData()
 **
 ** parameters: lcd_t , lcd_data_types_t , u8_t
 ** return    : lcd_error_t
 ***************************************************************************
 ** this function is used to send command or data for LCD
 **************************************************************************/
lcd_error_t hal_lcd_sendData(lcd_t* lcd ,lcd_data_types_t type, u8_t data );
/**************************************************************************
 ** hal_lcd_displaystring()
 **
 ** parameters: lcd_t , const u8_t
 ** return    : lcd_error_t
 ***************************************************************************
 ** this function is used to display strings for LCD
 **************************************************************************/
lcd_error_t hal_lcd_displayString(lcd_t *lcd, const u8_t *str);
/**************************************************************************
 ** hal_lcd_goToRowColumn()
 **
 ** parameters: lcd_t , u8_t,u8_t
 ** return    : lcd_error_t
 ***************************************************************************
 ** this function is used to start cursor in specific location at LCD
 **************************************************************************/
lcd_error_t hal_lcd_goToRowColumn(lcd_t *lcd , u8_t row, u8_t col);
/**************************************************************************
 ** hal_lcd_intgerToString()
 **
 ** parameters: lcd_t , u16_t
 ** return    : lcd_error_t
 ***************************************************************************
 ** this function is used to display integers as string  at LCD
 **************************************************************************/
lcd_error_t hal_lcd_intgerToString(lcd_t *lcd,u16_t data);
/**************************************************************************
 ** hal_lcd_clearScreen()
 **
 ** parameters: lcd_t
 ** return    : lcd_error_t
 ***************************************************************************
 ** this function is used to clear the LCD
 **************************************************************************/
lcd_error_t hal_lcd_clearScreen(lcd_t *lcd);


#endif /* _LCD_H_ */
