/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** pass_mng.h
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "pass_mng.h"
#include "MessagingUnit.h"
/**************************************************************************/
/*                     Functions Implementation                           */
/**************************************************************************/
pass_status_t comparePasswords(u8_t *firstPass, u8_t *secondPass)
{
  pass_status_t status = MATCH;

  for (u8_t i = 0; i < PASSWORD_LENGTH; i++)
  {
    if (firstPass[i] != secondPass[i])
    {
      status = DIFFERENT;
    }
  }
  return status;
}
