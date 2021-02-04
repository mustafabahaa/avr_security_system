
/**************************************************************************
** This  software  is  in  the  public  domain , furnished "as is", without
** technical support,  and with no  warranty, express or implied, as to its
** usefulness for any purpose.

** gpio_program.h
**************************************************************************/
#ifndef E_INTERRUPTS_PROGRAM_H_
#define E_INTERRUPTS_PROGRAM_H_
/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "led.h"
#include "e_interrupt.h"
/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
** execute_gpio_program(void)
**
** parameters: void
** return    : void
***************************************************************************
** this function calls gpio program test
**************************************************************************/
void execute_interrupt_program(void);

#endif /* E_INTERRUPTS_PROGRAM_H_ */