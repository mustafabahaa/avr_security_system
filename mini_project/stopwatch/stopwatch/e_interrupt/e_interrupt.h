#ifndef E_INTERRUPT_H_
#define E_INTERRUPT_H_
/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "atmega16.h"
#include "types.h"
/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
** e_interrupt_initialization()
**
** parameter: void
** return    : void
***************************************************************************
** this function is used to initialize the sequence for external interrupt
**************************************************************************/
void e_interrupt_initialization();


#endif /* E_INTERRUPT_H_ */