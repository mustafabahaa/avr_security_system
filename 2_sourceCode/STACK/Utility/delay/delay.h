/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** std_library.h
 **************************************************************************/
#ifndef _DELAY_H
#define _DELAY_H
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "./../../BSP/includes/types.h"
/**************************************************************************/
/*                           Public Functions                             */
/***************************************************************************
 ** delay_ms()
 **
 ** parameters: double ms
 ** return    : void
 ***************************************************************************
 ** this function is used to halt the processor with ms value
 **************************************************************************/
void delay_ms(double ms);

#endif /* _DELAY_H */

