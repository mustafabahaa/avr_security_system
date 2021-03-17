/*************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** main.c
 *************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "./../BSP/includes/types.h"
#include "./../BSP/includes/atmega16.h"
#include "./../BSP/HAL/KEYPAD/keypad.h"
#include "./../BSP/HAL/LCD/lcd.h"
/*************************************************************************/
/*                     Static Functions Prototypes                       */
/*************************************************************************/

/**************************************************************************
 ** systemInit()
 **
 ** parameters: void
 ** return    : system_error_t
 **************************************************************************
 ** this function is used to initialize all the system peripherals
 *************************************************************************/
static system_error_t systemInit();

/**************************************************************************
 ** keypadInit()
 **
 ** parameters: void
 ** return    : system_error_t
 **************************************************************************
 ** this function is used to initialize keypad peripheral
 *************************************************************************/
static system_error_t keypadInit();

/**************************************************************************
 ** LCDInit()
 **
 ** parameters: void
 ** return    : system_error_t
 **************************************************************************
 ** this function is used to initialize LCD peripheral
 *************************************************************************/
static system_error_t LCDInit();

/*************************************************************************/
/*                            Global variables                           */
/*************************************************************************/
keypad_t keypad ;
lcd_t lcd;
/*************************************************************************/
/*                               Main test                               */
/*************************************************************************/
int main(void)
{
	systemInit();
	s8_t keyPressed = 0 ;
	while(1)
	{
		if( KEYPAD_SUCCESS != hal_keypad_getKey(&keypad,&keyPressed))
		{
			/* LOGGER : error in keypad get key */
		}
		else
		{
			if (NO_KEY_PRESSED != keyPressed)
			{
				if ( LCD_SUCCESS != hal_lcd_sendData(&lcd,DISPLAY,keyPressed))
				{
					/* LOGGER : Printing Value on LCD */
				}
				else
				{
					/* LOGGER : Failed to send data to LCD */
				}
			}
			else
			{
				/* LOGGER : Pending Keypad Input */
			}
		}
	}
	return 0;
}

static system_error_t systemInit()
{
	system_error_t error = SYSTEM_SUCSUSS;
	error = keypadInit();
	error = LCDInit();
	return error;
}

static system_error_t keypadInit()
{
	system_error_t error = SYSTEM_SUCSUSS;

	keypad.keypadColsNo = 4;
	keypad.keypadRowsNo = 4;

	keypad.keypadPORT = BASE_A;
	keypad.keypadPIN = BASE_A;

	keypad.keypadRowsGPIOS[0] = 0;
	keypad.keypadRowsGPIOS[1] = 1;
	keypad.keypadRowsGPIOS[2] = 2;
	keypad.keypadRowsGPIOS[3] = 3;

	keypad.keypadColumnsGPIOS[0] = 4;
	keypad.keypadColumnsGPIOS[0] = 5;
	keypad.keypadColumnsGPIOS[0] = 6;
	keypad.keypadColumnsGPIOS[0] = 7;

	if (KEYPAD_SUCCESS != hal_keypad_init(&keypad))
	{
		error = SYSTEM_FAIL;
	}
	else
	{
		/* keypad initialized */
	}

	return error;
}

static system_error_t LCDInit()
{
	system_error_t error = SYSTEM_SUCSUSS;

	lcd.lcdControlPort = BASE_D;
	lcd.lcdDataPort = BASE_C;
	lcd.lcdMode = MODE_8_BIT;
	lcd.lcdRS = 4;
	lcd.lcdRW = 5;
	lcd.lcdE = 6;

	if (LCD_SUCCESS != hal_lcd_init(&lcd))
	{
		error = SYSTEM_FAIL;
	}
	else
	{
		u8_t A = 'A';
		if (LCD_SUCCESS != hal_lcd_sendData(&lcd,DISPLAY,A))
		{
		}
		else
		{
			register(BASE_B+OFFSET_PORT) = 0xff;
			/* LCD initialized */
		}
	}

	return error;
}
