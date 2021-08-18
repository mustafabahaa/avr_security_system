/*************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** main.c
 *************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
/* BSP Includes */
#include "types.h"
#include "atmega16.h"
#include "timer.h"
#include "eeprom.h"
#include "buzzer.h"
#include "servo_motor.h"

/* Managers Includes */
#include "MessagingUnit.h"

/* Utility Includes */
#include "std_library.h"
#include "delay.h"

/*************************************************************************/
/*                               MACROS                                  */
/*************************************************************************/
#define PASSWORD_LENGTH 5
#define PASSWORD_LOCATION_FLAG 0x09
/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/
typedef enum {
	CHECK_PASS_EXCISTANCE_STATE = 10,
	START_DEFAULT_PASS_STATE = 5,
	START_NEW_PASS_STATE = 4,
	START_STATE = 1,
	OPEN_LOCK_STATE = 11,
	ALARM_STATE = 12,
	HALT_STATE = 100
}state_t ;

/*************************************************************************/
/*                     Static Functions Prototypes                       */
/*************************************************************************/
static system_error_t systemInit();
static system_error_t buzzerInit();
static system_error_t timerInit();
static system_error_t servoMotorInit();

static void checkDefaultPassword();
static void startPasswordFlashing();
static void validatePassword();
static void startAlarmSystem();
static void motorOpen();

/* timers callback */
static void releaseSystem();
static void closeMotor();
/*************************************************************************/
/*                            Global variables                           */
/*************************************************************************/

/* used for program to handle state */
state_t state;

/* HAL layer initialization devices */
buzzer_t buzzer;
timer_config_t timer;
servo_motor_t servo;

/*************************************************************************/
/*                               Main Program                            */
/*************************************************************************/

int main(void)
{
	state = HALT_STATE;
	systemInit();

	while(1)
	{
		ms_manager_receive_data(&state);

		switch(state)
		{

		case CHECK_PASS_EXCISTANCE_STATE:
		{
			checkDefaultPassword();
			break;
		}

		case START_DEFAULT_PASS_STATE:
		{
			startPasswordFlashing();
			break;
		}

		case START_STATE:
		{
			validatePassword();
			break;
		}

		case START_NEW_PASS_STATE:
		{
			startPasswordFlashing();
			break;
		}

		case ALARM_STATE:
		{
			startAlarmSystem();
			break;
		}

		case OPEN_LOCK_STATE:
		{
			motorOpen();
			break;
		}

		case HALT_STATE :
		{
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
static void checkDefaultPassword()
{
	u8_t passwordExistance = 0;
	hal_eeprom_readByte(PASSWORD_LOCATION_FLAG,&passwordExistance);
	if (PASSWORD_EXICTED ==  passwordExistance)
	{
		ms_manager_send_data(PASSWORD_EXICTED);
	}
	else
	{
		ms_manager_send_data(PASSWORD_NOT_EXICTED);
	}

	state = HALT_STATE;
}

static void startPasswordFlashing()
{
	u8_t password[PASSWORD_LENGTH] = {0};

	ms_manager_receive_string(password);

  /* save password in eeprom */
  for (int i = 0; i < PASSWORD_LENGTH - 1; i++)
  {
    if (EEPROM_SUCCESS != hal_eeprom_writeByte(i + 1, password[i]))
    {
      break;
    }
    else
    {
      delay_ms(10);
    }
  }

  /*write password exist flag */
	hal_eeprom_writeByte(PASSWORD_LOCATION_FLAG,PASSWORD_EXICTED);
	delay_ms(10);

	state = HALT_STATE;

}

static void validatePassword()
{
	u8_t password[PASSWORD_LENGTH] = {0};
	u8_t originalPassword[PASSWORD_LENGTH] = {0};

	/* Receive password */
	ms_manager_receive_string(password);

	/* get password from EEPROM */
	for (int i =0; i<PASSWORD_LENGTH; i++)
	{
		hal_eeprom_readByte(0x00+(i+1),&originalPassword[i]);
	}

	if(std_strcmp(password,originalPassword) == 0)
	{
		ms_manager_send_data(PASSWORD_RIGHT);
	}
	else
	{
		ms_manager_send_data(PASSWORD_WRONG);
	}

	state = HALT_STATE;
}

static void startAlarmSystem()
{
	timer_setCallBack(releaseSystem);

	mcal_timer_start(&timer);
	hal_buzzer_set_state(&buzzer,HIGH);

	state = HALT_STATE;
}

static void motorOpen()
{
	timer_setCallBack(closeMotor);

	mcal_timer_start(&timer);
	hal_servo_motor_set_degree(&servo,180);
	state = HALT_STATE;
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
  error = buzzerInit();
  error = servoMotorInit();

    /* Initialize Managers */
	error = ms_manager_init();

  error = EEPROM_SUCCESS == hal_eeprom_init() ? SYSTEM_SUCCESS : SYSTEM_FAIL;
	return error;
}

static system_error_t servoMotorInit()
{
	system_error_t error = SYSTEM_SUCCESS;

	servo.channel->channel_port = BASE_B;
	servo.channel->channel_pin = 3;

	hal_servo_motor_init(&servo);
	return error;
}

static system_error_t buzzerInit()
{
	system_error_t error = SYSTEM_SUCCESS;

	buzzer.base_addr = BASE_C;
	buzzer.pin_num = 3;
	buzzer.wiring = BUZZER_CURRENT_SOURCING;

	hal_buzzer_init(&buzzer);
	timerInit();

	return error;
}

static system_error_t timerInit()
{
	system_error_t error = SYSTEM_SUCCESS;

	timer.timer_number = TIMER0;
	timer.mode = TIMER_NORMAL_MODE ;
	timer.preScaler = F_CPU_1024;
	timer.tick_seconds = 5;

	if (TIMER_STATE_SUCCESS != mcal_timer_init(&timer))
	{
		error = SYSTEM_FAIL;
	}
	else
	{
		error = SYSTEM_SUCCESS;
	}

	return error;
}

/*************************************************************************/
/*                            Timer Callback                             */
/*************************************************************************/

static void releaseSystem()
{
	mcal_timer_stop(&timer);
	hal_buzzer_set_state(&buzzer,LOW);
	state = HALT_STATE;
}

static void closeMotor()
{
	mcal_timer_stop(&timer);
	hal_servo_motor_set_degree(&servo,0);
	state = HALT_STATE;
}

