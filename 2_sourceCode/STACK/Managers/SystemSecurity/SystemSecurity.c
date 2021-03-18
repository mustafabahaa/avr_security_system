/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** SystemSecurity.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "SystemSecurity.h"
#include "./../../BSP/MCAL/TIMER/timer.h"

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
static system_error_t timerInit();

/*************************************************************************/
/*                          Global Variables                             */
/*************************************************************************/
timer_config_t timer;

/**************************************************************************/
/*                     Functions Implementation                           */
/**************************************************************************/

static void timerTick()
{
	tog_bit(BASE_B+OFFSET_PORT,7);
}

system_error_t manager_sc_init_freeze_timer()
{
	tog_bit(BASE_B+OFFSET_DIR,7);

	system_error_t error = SYSTEM_SUCCESS;

	error = timerInit();

	/* function to be executed every timer->tick_seconds */
	timer_setCallBack(timerTick);

	return error;
}

system_error_t manager_sc_start_freeze_timer()
{
	system_error_t error = SYSTEM_SUCCESS;

	if (TIMER_STATE_SUCCESS != mcal_timer_start(&timer))
	{
		error = SYSTEM_FAIL;
	}
	else
	{
		error = SYSTEM_SUCCESS;
	}

	return error;
}

system_error_t manager_sc_stop_freeze_timer()
{
	system_error_t error = SYSTEM_SUCCESS;

	if (TIMER_STATE_SUCCESS != mcal_timer_stop(&timer))
	{
		error = SYSTEM_FAIL;
	}
	else
	{
		error = SYSTEM_SUCCESS;
	}

	return error;
}


static system_error_t timerInit()
{
	system_error_t error = SYSTEM_SUCCESS;

	timer.inital_value = 0 ;
	timer.timer_number = TIMER0;
	timer.mode = TIMER_NORMAL_MODE ;
	timer.preScaler = PRESCALER_1024;
	timer.tick_seconds = 1;

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

