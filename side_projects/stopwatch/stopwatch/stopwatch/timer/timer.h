#ifndef TIMER_H_
#define TIMER_H_
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
** timer_initialization()
**
** parameter: void
** return    : void
***************************************************************************
** this function is used to initialize all the necessary sequence for timer
**************************************************************************/
void timer_initialization();

#endif /* TIMER_H_ */