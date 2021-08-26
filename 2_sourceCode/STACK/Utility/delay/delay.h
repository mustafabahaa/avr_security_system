/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** std_library.h
 **************************************************************************/
#ifndef _DELAY_H
#define _DELAY_H
#define F_CPU 1000000UL
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "types.h"
/**************************************************************************/
/*                           Public Functions                             */
/***************************************************************************
 ** delay_ms()
 **
 ** parameter: double ms
 ** return    : void
 ***************************************************************************
 ** this function is used to halt the processor with ms value
 **************************************************************************/
void delay_ms(double ms);

#endif /* _DELAY_H */

