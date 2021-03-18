/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** e_interrupt.h
 **************************************************************************/
#ifndef E_INTERRUPT_H_
#define E_INTERRUPT_H_

/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "./../../includes/types.h"
#include "../../includes/atmega16.h"
/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/

typedef enum
{
	RISING_EDGE,
	FALLING_EDGE,
	CHANGING_EDGE
} interrupt_mode_t;

typedef enum
{
	INTERRUPT_STATE_SUCCESS,
	INTERRUPT_STATE_INVALID_OPERATION_MODE,
	INTERRUPT_STATE_INVAILD_INTERRUPT_NUMBER
} interrupt_error;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** mcal_interrupt_initialize()
 **
 ** parameters: u8_t interruptNo
 ** parameters: interrupt_mode_t mode
 ** return    : interrupt_error
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for interrupt
 **************************************************************************/
interrupt_error mcal_interrupt_initialize(u8_t interruptNo,
		interrupt_mode_t mode);
/**************************************************************************
 ** mcal_interrupt_read_flag()
 **
 ** parameters: u8_t flag
 ** parameters: u8_t *result
 ** return    : interrupt_error
 ***************************************************************************
 ** this function is used read a interrupts flags from GIFR register
 **************************************************************************/
interrupt_error mcal_interrupt_read_flag(u8_t flag , u8_t *result);

/**************************************************************************
 ** mcal_interrupt_clear_flag()
 **
 ** parameters: u8_t flag
 ** return    : interrupt_error
 ***************************************************************************
 ** this function is used to clear flag from GIFR register
 **************************************************************************/
interrupt_error mcal_interrupt_clear_flag(u8_t flag);

#endif /* E_INTERRUPT_H_ */