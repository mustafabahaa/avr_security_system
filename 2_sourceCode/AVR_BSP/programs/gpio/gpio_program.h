/**************************************************************************
** This  software  is  in  the  public  domain , furnished "as is", without
** technical support,  and with no  warranty, express or implied, as to its
** usefulness for any purpose.

** gpio_program.h
**************************************************************************/
#ifndef _GPIO_PROGRAM_H_
#define _GPIO_PROGRAM_H_
/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "./../../HAL/LED/led.h"
#include "./../../HAL/BUTTON/button.h"
#include "./../../MCAL/e_interrupt/e_interrupt.h"
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
void execute_gpio_program(void);

#endif /* _GPIO_PROGRAM_H_ */
