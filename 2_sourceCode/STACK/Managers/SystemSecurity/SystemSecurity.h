/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** SystemSecurity.h
 **************************************************************************/
#ifndef _SYSTEM_SECURITY_
#define _SYSTEM_SECURITY_
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "./../../BSP/includes/types.h"
#include "./../../BSP/MCAL/gpio/gpio.h"

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** manager_sc_init_freeze_timer()
 **
 ** parameters: void
 ** return    : system_error_t
 ***************************************************************************
 ** this function is used to initialize freeze timer
 **************************************************************************/
system_error_t manager_sc_init_freeze_timer();

/**************************************************************************
 ** manager_sc_start_freeze_timer()
 **
 ** parameters: void
 ** return    : system_error_t
 ***************************************************************************
 ** this function is used to start freeze timer
 **************************************************************************/
system_error_t manager_sc_start_freeze_timer();

/**************************************************************************
 ** manager_sc_stop_freeze_timer()
 **
 ** parameters: void
 ** return    : system_error_t
 ***************************************************************************
 ** this function is used to start freeze timer
 **************************************************************************/
system_error_t manager_sc_stop_freeze_timer();

#endif /* _SYSTEM_SECURITY_ */
