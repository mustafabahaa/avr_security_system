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
#include "types.h"
#include "avr.h"
#include "gpio.h"
#include "port.h"
#include "std_library.h"
#include "delay.h"
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
  LCD_INVALID_MODE,
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
 ** parameter: lcd_t
 ** return    : lcd_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for LCD
 **************************************************************************/
lcd_error_t hal_lcd_init(lcd_t *lcd);
/**************************************************************************
 ** hal_lcd_sendData()
 **
 ** parameter: lcd_t , lcd_data_types_t , u8_t
 ** return    : lcd_error_t
 ***************************************************************************
 ** this function is used to send command or data for LCD
 **************************************************************************/
lcd_error_t hal_lcd_sendData(lcd_t* lcd ,lcd_data_types_t type, u8_t data );
/**************************************************************************
 ** hal_lcd_displaystring()
 **
 ** parameter: lcd_t , const u8_t
 ** return    : lcd_error_t
 ***************************************************************************
 ** this function is used to display strings for LCD
 **************************************************************************/
lcd_error_t hal_lcd_displayString(lcd_t *lcd, const u8_t *str);
/**************************************************************************
 ** hal_lcd_goToRowColumn()
 **
 ** parameter: lcd_t , u8_t,u8_t
 ** return    : lcd_error_t
 ***************************************************************************
 ** this function is used to start cursor in specific location at LCD
 **************************************************************************/
lcd_error_t hal_lcd_goToRowColumn(lcd_t *lcd , u8_t row, u8_t col);
/**************************************************************************
 ** hal_lcd_intgerToString()
 **
 ** parameter: lcd_t , u16_t
 ** return    : lcd_error_t
 ***************************************************************************
 ** this function is used to display integers as string  at LCD
 **************************************************************************/
lcd_error_t hal_lcd_intgerToString(lcd_t *lcd,u16_t data);
/**************************************************************************
 ** hal_lcd_clearScreen()
 **
 ** parameter: lcd_t
 ** return    : lcd_error_t
 ***************************************************************************
 ** this function is used to clear the LCD
 **************************************************************************/
lcd_error_t hal_lcd_clearScreen(lcd_t *lcd);


#endif /* _LCD_H_ */
