/***************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** e_interrupt.h
 **************************************************************************/
#ifndef E_INTERRUPT_H_
#define E_INTERRUPT_H_
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "types.h"
#include "avr.h"
#include "logger.h"
/**************************************************************************/
/*                              Registers                                 */
/**************************************************************************/
#define EICRA   0x69
#define ISC00   0
#define ISC01   1
#define ISC10   2
#define ISC11   3
#define ISC20   4
#define ISC21   5

#define EIFR    0x3C
#define INTF0   0
#define INTF1   1
#define INTF2   2

#define EIMSK   0x3D
#define INT0    0
#define INT1    1
#define INT2    2
/**************************************************************************/
/*                               Types                                    */
/**************************************************************************/
typedef enum
{
  RISING_EDGE = 1,
  FALLING_EDGE,
  CHANGING_EDGE
} interrupt_mode_t;

typedef enum
{
  INTERRUPT_STATE_SUCCESS = 1,
  INTERRUPT_STATE_INVALID_OPERATION_MODE,
  INTERRUPT_STATE_INVAILD_INTERRUPT_NUMBER
} interrupt_error;

/**************************************************************************/
/*                           Public Functions                             */
/***************************************************************************
 ** mcal_interrupt_initialize()
 **
 ** parameter: u8_t interruptNo
 ** parameter: interrupt_mode_t mode
 ** return    : interrupt_error
 ***************************************************************************
 ** this function is used to initialize 
 ** all the necessary sequence for interrupt
 **************************************************************************/
interrupt_error mcal_interrupt_initialize(u8_t interruptNo,
                                          interrupt_mode_t mode);
/***************************************************************************
 ** mcal_interrupt_read_flag()
 **
 ** parameter: u8_t flag
 ** parameter: u8_t *result
 ** return    : interrupt_error
 ***************************************************************************
 ** this function is used read a interrupts flags from EIFR register
 **************************************************************************/
interrupt_error mcal_interrupt_read_flag(u8_t flag, u8_t *result);

/***************************************************************************
 ** mcal_interrupt_clear_flag()
 **
 ** parameter: u8_t flag
 ** return    : interrupt_error
 ***************************************************************************
 ** this function is used to clear flag from EIFR register
 **************************************************************************/
interrupt_error mcal_interrupt_clear_flag(u8_t flag);

#endif /* E_INTERRUPT_H_ */
