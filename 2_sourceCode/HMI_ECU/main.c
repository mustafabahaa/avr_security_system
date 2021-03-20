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
#include "./../STACK/Managers/MessagingUnit/MessagingUnit.h"

/* Service Includes */
#include "./../STACK/Services/Logger/logger.h"

/*************************************************************************/
/*                               MACROS                                  */
/*************************************************************************/
#define PASSWORD_LENGTH 4
#define MAX_INCORRECT_PASSWORD_ENTER 3
#define ENTER 'A'
/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/
typedef enum {
	ANONYMOUS,
	AUTHENTICATED,
}authentication_t;

typedef enum {
	CHECK_DEFAULT_PASSWORD_STATE,
	SET_NEW_PASSWORD_STATE,
	PASSWORD_INPUT_STATE,
	ALARM_SYSTEM_STATE,
	HOME_STATE,
	HALT,
}state_t;

/*************************************************************************/
/*                     Static Functions Prototypes                       */
/*************************************************************************/

static system_error_t systemInit();
static system_error_t keypadInit();
static system_error_t LCDInit();

static void requirePassword(u8_t* message , u8_t* password);
static void userAuthentication(authentication_t authentcated);
static void passwordInputState();
static void checkDefaultPassword();
static void firtTimePassword();
static void startAlarmSystem();
static void displayHomeSystem();

/*************************************************************************/
/*                            Global variables                           */
/*************************************************************************/

/* used for program to handle state */
state_t state;

/* HAL layer initialization devices */
keypad_t keypad ;
lcd_t lcd;

/* Authentication variables */
u8_t passwordErrorCounter = 0 ;


/*************************************************************************/
/*                               Main Program                            */
/*************************************************************************/

int main(void)
{
	state = CHECK_DEFAULT_PASSWORD_STATE;

	systemInit();

	while(1)
	{
		switch(state)
		{

		case CHECK_DEFAULT_PASSWORD_STATE:
		{
			checkDefaultPassword();
			break;
		}

		case SET_NEW_PASSWORD_STATE:
		{
			firtTimePassword();
			break;
		}

		case PASSWORD_INPUT_STATE :
		{
			passwordInputState();
			break;
		}

		case HOME_STATE:
		{
			displayHomeSystem();
			break;
		}

		case ALARM_SYSTEM_STATE:
		{
			startAlarmSystem();
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

/*************************************************************************/
/*                           System Functions                            */
/*************************************************************************/

static void requirePassword(u8_t* message , u8_t* password)
{
	s8_t keyPressed = NO_KEY_PRESSED;
	s8_t buffer[4] ={0};

	hal_lcd_goToRowColumn(&lcd,0,0);
	hal_lcd_displayString(&lcd,message);

	/*insert new line for password entering */
	hal_lcd_goToRowColumn(&lcd,1,0);

	/*take password from user*/
	for (int i = 0 ; i < PASSWORD_LENGTH ; i++)
	{
		/* stay in loop until any key is pressed */
		while(NO_KEY_PRESSED == keyPressed)
		{
			hal_keypad_getKey(&keypad,&keyPressed);
		}

		/* print * on LCD every time keypad is pressed*/
		hal_lcd_sendData(&lcd,DISPLAY,'*');

		buffer[i] = keyPressed;
	}

	/* wait for user to press enter */
	while(ENTER != keyPressed)
	{
		hal_keypad_getKey(&keypad,&keyPressed);
	}

	/* copy the password buffer to the passed array*/
	for(int i = 0 ; i < PASSWORD_LENGTH ; i++)
	{
		password[i] = buffer[i];
	}

	hal_lcd_goToRowColumn(&lcd,0,0);
	hal_lcd_clearScreen(&lcd);
}

static void passwordInputState()
{
	u8_t password[4] = {0};
	u8_t buffer=0;

	requirePassword((u8_t*)"Enter password",password);

	/* send data to Control ECU to be validated */
	ms_manager_send_data(START);

	/* receive response from Control ECU */
	ms_manager_receive_data(&buffer);

	switch(buffer)
	{
	case PASSWORD_WRONG:
	{
		userAuthentication(ANONYMOUS);
		break;
	}
	case PASSWORD_RIGHT:
	{
		userAuthentication(AUTHENTICATED);
		break;
	}
	default :
	{
		/* ECU didn't response in right way */
	}
	}

}

static void checkDefaultPassword()
{
	u8_t buffer = 0 ;
	ms_manager_send_data(CHECK_PASS_EXCISTANCE);
	ms_manager_receive_data(&buffer);

	if (buffer == PASSWORD_NOT_EXICTED)
	{
		state = SET_NEW_PASSWORD_STATE;
	}
	else
	{
		state = PASSWORD_INPUT_STATE;
	}
}

static void firtTimePassword()
{
	u8_t password[4] = {0};
	u8_t confirmPassword[4] = {0};

	requirePassword((u8_t*)"Enter new password",password);
	requirePassword((u8_t*)"Confirm password",confirmPassword);

	if (std_strcmp(password,confirmPassword) == 0)
	{
		// send password to control unit to save it in EEPROM
		ms_manager_send_data(START_DEFAULT_PASS);
		ms_manager_send_string(password);
		state = PASSWORD_INPUT_STATE;
	}
	else
	{
		hal_lcd_displayString(&lcd,"Passwords Doesn't");
		hal_lcd_goToRowColumn(&lcd,1,0);
		hal_lcd_displayString(&lcd,"Match");

		delay_ms(10000);

		hal_lcd_clearScreen(&lcd);

		state = SET_NEW_PASSWORD_STATE;
	}
}

static void userAuthentication(authentication_t authentcated)
{
	if (authentcated)
	{
		state = HOME_STATE;
		passwordErrorCounter = 0;
	}
	else if (MAX_INCORRECT_PASSWORD_ENTER == passwordErrorCounter)
	{
		state = ALARM_SYSTEM_STATE;
	}
	else
	{
		passwordErrorCounter++;
	}
}

static void startAlarmSystem()
{
	/* start buzzer , hang system for a while
	 * 7alet tawre2 gem
	 * wewaaweewaaaaaaaaaa
	 * atsl bel3yal */
	passwordErrorCounter = 0;

	state = PASSWORD_INPUT_STATE;
}

static void displayHomeSystem()
{
	s8_t keyPressed = NO_KEY_PRESSED;

	hal_lcd_displayString(&lcd,"1-Open  2-Close");
	hal_lcd_goToRowColumn(&lcd,1,0);
	hal_lcd_displayString(&lcd,"3-Change password");

	/* stay in loop until any key is pressed */
	while(NO_KEY_PRESSED == keyPressed)
	{
		hal_keypad_getKey(&keypad,&keyPressed);
	}

	switch(keyPressed)
	{
	case '1' :
	{
		break;
	}
	case '2' :
	{
		break;
	}
	case '3' :
	{
		break;
	}
	default:
	{
		hal_lcd_goToRowColumn(&lcd,0,0);
		hal_lcd_clearScreen(&lcd);

		hal_lcd_displayString(&lcd,"Wrong Input");
		hal_lcd_goToRowColumn(&lcd,1,0);
		hal_lcd_displayString(&lcd,"Try Again");
		delay_ms(10000);

		hal_lcd_goToRowColumn(&lcd,0,0);
		hal_lcd_clearScreen(&lcd);
		break;
	}
	}
}

/*************************************************************************/
/*                           Initialization                              */
/*************************************************************************/

static system_error_t systemInit()
{
	system_error_t error = SYSTEM_SUCCESS;

	/* Initialize Services */
	//logger_init(LOGGER_ALL);

	/* Initialize hardware devices */
	error = keypadInit();
	error = LCDInit();

	/* Initialize Managers */
	error = manager_sc_init_freeze_timer();
	error = ms_manager_init();

	return error;
}

static system_error_t keypadInit()
{
	system_error_t error = SYSTEM_SUCCESS;

	/*define the port of the cols and rows */
	keypad.keypadColsPORT = BASE_A;
	keypad.keypadRowsPort = BASE_A;

	/*define the number of rows and cols */
	keypad.keypadRowsNo = 4;
	keypad.keypadColsNo = 4;

	/* Locate keypad rows gpios */
	static u8_t keypadRowsGPIOS[] = {0,1,2,3};

	/* Locate keypad columns gpios */
	static u8_t keypadColumnsGPIOS[] = {4,5,6,7};

	/* insert the correct keypad mapping */
	static s8_t keypadMapping[4][4] =
	{
			{'7', '8' , '9' , '/' },
			{'4', '5' , '6' , '*' },
			{'1', '2' , '3' , '-' },
			{'A', '0' , '=' , '+' }
	};

	/* attach the keypad rows and cols and mapping to keypad*/
	keypad.keypadRowsGPIOS = &keypadRowsGPIOS;
	keypad.keypadColumnsGPIOS = &keypadColumnsGPIOS;
	keypad.keypadMapping = &keypadMapping;

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


