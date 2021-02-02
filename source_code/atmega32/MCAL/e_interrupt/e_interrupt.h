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
#include "standardtypes.h"

/*************************************************************************/
/*                              Macros                                   */
/*************************************************************************/

/*enable and disable interrupt by setting and clearing I bit in SREG */
#define SREG_interrupt_bit 7
#define setGlobalInterrupt set_bit(SREG, SREG_interrupt_bit)
#define clearGlobalInterrupt clr_bit(SREG, SREG_interrupt_bit)

/* define interrupt registers */
#define SREG 0X5F
#define GIFR 0x5A
#define GICR 0x5B
#define MCUCR 0x55
#define MCUCSR 0x54

/*MCUCR (MCU Control Register)*/
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
#define ISC2 6

/*Interrupts Number*/
#define INT0 6
#define INT1 7
#define INT2 5

/*Interrupts Flags*/
#define INTF0 6
#define INTF1 7
#define INTF2 5

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
