/*************************************************************************
** This  software  is  in  the  public  domain , furnished "as is", without
** technical support,  and with no  warranty, express or implied, as to its
** usefulness for any purpose.

** main.c
**************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "types.h"
#include "atmega32.h"

/*************************************************************************/
/*                          Programs Includes                            */
/*************************************************************************/
#include "gpio_program.h"
#include "e_interrupts_program.h"
/*************************************************************************/
/*                       Programs Configurations                         */
/*************************************************************************/
typedef enum
{
  GPIO_PROGRAM,
  INTERRUPT_PROGRAM,
} operationMode;
/*************************************************************************/
/*                               Main test                               */
/*************************************************************************/
int main(void)
{
  operationMode mode = GPIO_PROGRAM;

  switch (mode)
  {
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

  default:
  {
    /* do nothing */
  }
  }

  return 0;
}
