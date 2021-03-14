/*************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** port_program.c
 **************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "port_program.h"
/*************************************************************************/
/*                   Static Functions Prototype                          */
/**************************************************************************
 ** systemInit()
 **
 ** parameters: void
 ** return    : void
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for app
 **************************************************************************/
static void systemInit();

/** init_port()
 **
 ** parameters: void
 ** return    : void
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for port
 **************************************************************************/
static void init_port();

/*************************************************************************/
/*                             Application                               */
/*************************************************************************/
void execute_port_program(void)
{
	systemInit();

	mcal_port_write(BASE_C, PORT_ON);
	while (1)
	{
	}
}

/*************************************************************************/
/*                   Static Functions Implementations                    */
/*************************************************************************/
static void systemInit()
{
	init_port();
}

static void init_port()
{
	mcal_port_init(BASE_A, DIR_PORT_OUTPUT);
	mcal_port_init(BASE_B, DIR_PORT_OUTPUT);
	mcal_port_init(BASE_C, DIR_PORT_OUTPUT);
	mcal_port_init(BASE_D, DIR_PORT_INPUT_PULLDOWN);
}
