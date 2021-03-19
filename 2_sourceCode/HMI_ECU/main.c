/*************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** main.c
 *************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
/* BSP Includes */
#include "./../STACK/BSP/includes/types.h"
#include "./../STACK/BSP/includes/atmega16.h"
#include "./../STACK/BSP/HAL/KEYPAD/keypad.h"
#include "./../STACK/BSP/HAL/LCD/lcd.h"
#include "./../STACK/BSP/MCAL/TIMER/timer.h"

/* Managers Includes */
#include "./../STACK/Managers/SystemSecurity/SystemSecurity.h"

/* Service Includes */
#include "./../STACK/Services/Logger/logger.h"

/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
typedef enum {
	PASSWORD_INPUT_STATE,
	FREEZE_STATE,
}state_t;

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

/**************************************************************************
 ** passwordInputState()
 **
 ** parameters: void
 ** return    : void
 **************************************************************************
 ** this function is used to enter password input state
 *************************************************************************/
static void passwordInputState();

/**************************************************************************
 ** freezeState()
 **
 ** parameters: void
 ** return    : void
 **************************************************************************
 ** this function is used to enter freeze state
 *************************************************************************/
static void freezeState();
/*************************************************************************/
/*                            Global variables                           */
/*************************************************************************/
u8_t* TAG = (u8_t*)"[HMI-ECU]";
keypad_t keypad ;
lcd_t lcd;
/*************************************************************************/
/*                               Main test                               */
/*************************************************************************/

int main(void)
{
	state_t state = PASSWORD_INPUT_STATE;

	systemInit();

	while(1)
	{
		switch(state)
		{
		case PASSWORD_INPUT_STATE :
		{
			passwordInputState();
			break;
		}

		case FREEZE_STATE:
		{
			freezeState();
			break;
		}

		default :
		{
			/* LOGGER : Invalid STATE */
		}

		}
	}

	return 0;
}

static void passwordInputState()
{
	s8_t keyPressed = 0;

	if( KEYPAD_SUCCESS != hal_keypad_getKey(&keypad,&keyPressed))
	{
		logger_write_error(TAG,(u8_t*)"Failed to get key from keypad");
	}
	else if (NO_KEY_PRESSED == keyPressed)
	{
		logger_write_debug(TAG,(u8_t*)"Pending Keypad Input");
	}
	else if ( LCD_SUCCESS != hal_lcd_sendData(&lcd,DISPLAY,keyPressed))
	{
		logger_write_error(TAG,(u8_t*)"Failed to send key pressed to LCD");
	}
	else
	{
		logger_write_error(TAG,(u8_t*)"keypad pressed button is printed on LCD");
	}
}

static void freezeState()
{
	if(SYSTEM_SUCCESS != manager_sc_start_freeze_timer())
	{
		/* LOGGER : Error initializing freeze timer */
	}
	else
	{
		/* LOGGER :  freeze timer initialized */
	}
}

static system_error_t systemInit()
{
	system_error_t error = SYSTEM_SUCCESS;

	/* Initialize hardware devices */
	error = keypadInit();
	error = LCDInit();

	/* Initialize Managers */
	error = manager_sc_init_freeze_timer();

	/* Initialize Services */
	logger_init(LOGGER_ALL);

	return error;
}

static system_error_t keypadInit()
{
	system_error_t error = SYSTEM_SUCCESS;

	keypad.keypadColsNo = 4;
	keypad.keypadRowsNo = 4;

	keypad.keypadPORT = BASE_A;
	keypad.keypadPIN = BASE_A;

	keypad.keypadRowsGPIOS[0] = 0;
	keypad.keypadRowsGPIOS[1] = 1;
	keypad.keypadRowsGPIOS[2] = 2;
	keypad.keypadRowsGPIOS[3] = 3;

	keypad.keypadColumnsGPIOS[0] = 4;
	keypad.keypadColumnsGPIOS[1] = 5;
	keypad.keypadColumnsGPIOS[2] = 6;
	keypad.keypadColumnsGPIOS[3] = 7;

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
	system_error_t error = SYSTEM_SUCCESS;

	lcd.lcdControlPort = BASE_D;
	lcd.lcdDataPort = BASE_C;
	lcd.lcdMode = MODE_8_BIT;
	lcd.lcdRS = 5;
	lcd.lcdRW = 6;
	lcd.lcdE = 7;

	if (LCD_SUCCESS != hal_lcd_init(&lcd))
	{
		error = SYSTEM_FAIL;
	}
	else
	{
		/* LCD initialized */
	}

	return error;
}


