/*************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** main.c
 **************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "./includes/types.h"
#include "./includes/atmega32.h"

/*************************************************************************/
/*                          Programs Includes                            */
/*************************************************************************/
#include "./programs/port/port_program.h"
#include "./programs/gpio/gpio_program.h"
#include "./programs/eInterrupts/e_interrupts_program.h"
#include "./programs/final_project/final_project_program.h"
/*************************************************************************/
/*                       Programs Configurations                         */
/*************************************************************************/
typedef enum
{
	PORT_PROGRAM,
	GPIO_PROGRAM,
	INTERRUPT_PROGRAM,
	FINAL_PROJECT_PROGRAM,
} operationMode;
/*************************************************************************/
/*                               Main test                               */
/*************************************************************************/
int main(void)
{
	operationMode mode = FINAL_PROJECT_PROGRAM;

	switch (mode)
	{
	case PORT_PROGRAM:
	{
		execute_port_program();
		break;
	}

	case GPIO_PROGRAM:
	{
		execute_gpio_program();
		break;
	}

	case INTERRUPT_PROGRAM:
	{
		execute_interrupt_program();
		break;
	}

	case FINAL_PROJECT_PROGRAM:
	{
		execute_final_program();
		break;
	}

	default:
	{
		/* do nothing */
	}
	}

	return 0;
}
