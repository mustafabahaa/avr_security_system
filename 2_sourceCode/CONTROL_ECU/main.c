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
#include "./../STACK/BSP/MCAL/TIMER/timer.h"

/* Managers Includes */
#include "./../STACK/Managers/SystemSecurity/SystemSecurity.h"
#include "./../STACK/Managers/MessagingUnit/MessagingUnit.h"

/*************************************************************************/
/*                               MACROS                                  */
/*************************************************************************/
#define PASSWORD_LENGTH 4
/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/
typedef enum {

	HALT,
}state_t;

/*************************************************************************/
/*                     Static Functions Prototypes                       */
/*************************************************************************/

static system_error_t systemInit();

/*************************************************************************/
/*                            Global variables                           */
/*************************************************************************/

/* used for program to handle state */
state_t state;

/*************************************************************************/
/*                               Main Program                            */
/*************************************************************************/

int main(void)
{
	state = HALT;

	systemInit();

	while(1)
	{
		switch(state)
		{

		case HALT:
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



/*************************************************************************/
/*                           Initialization                              */
/*************************************************************************/

static system_error_t systemInit()
{
	system_error_t error = SYSTEM_SUCCESS;

	/* Initialize Services */
	//logger_init(LOGGER_ALL);

	/* Initialize hardware devices */


	/* Initialize Managers */
	error = manager_sc_init_freeze_timer();
	error = ms_manager_init();

	return error;
}


