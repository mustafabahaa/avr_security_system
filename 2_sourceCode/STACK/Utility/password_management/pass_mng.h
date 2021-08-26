/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** pass_mng.h
 **************************************************************************/
#ifndef _PASS_MNG_H
#define _PASS_MNG_H
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "types.h"
/**************************************************************************/
/*                              Types                                     */
/**************************************************************************/
typedef enum 
{
  MATCH=1,
  DIFFERENT=2
} pass_status_t;
/**************************************************************************/
/*                           Public Functions                             */
/***************************************************************************
 ** comparePasswords()
 **
 ** parameter: 8_t* firstPass,u8_t* secondPass
 ** return    : pass_status_t
 ***************************************************************************
 ** this function is used to compare passwords strings
 **************************************************************************/
 pass_status_t comparePasswords(u8_t* firstPass,u8_t* secondPass);

#endif /* _PASS_MNG_H */

