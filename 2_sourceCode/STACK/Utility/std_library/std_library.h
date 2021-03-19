/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** std_library.h
 **************************************************************************/
#ifndef _STD_LIBS_H
#define _STD_LIBS_H
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "./../../BSP/includes/types.h"
/**************************************************************************/
/*                           Public Functions                             */
/***************************************************************************
 ** std_strcat()
 **
 ** parameters: void
 ** return    : u8_t*
 ***************************************************************************
 ** this function is the custom implementation of std-lib strcat function
 **************************************************************************/
u8_t* std_strcat(u8_t* destination,u8_t* source);

/***************************************************************************
 ** std_strlen()
 **
 ** parameters: const u8_t *s
 ** return    : u16_t
 ***************************************************************************
 ** this function is the custom implementation of std-lib strlen function
 **************************************************************************/
u16_t std_strlen(u8_t *length);

/***************************************************************************
 ** std_strlen()
 **
 ** parameters: const u8_t *s
 ** return    : u16_t
 ***************************************************************************
 ** this function is the custom implementation of std-lib itoa function
 **************************************************************************/
u8_t* std_itoa(u16_t value, u8_t* buffer, u16_t base);

#endif /* _STD_LIBS_H */

