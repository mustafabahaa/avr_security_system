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

typedef enum
{
  interrupt_unit_0 = 0,
  interrupt_unit_1 = 1,
  interrupt_unit_2 = 2,
} interrupt_unit_number_t;

typedef struct
{
  u8_t ctrl_reg;
  u8_t edge_reg;
  u8_t edge_bit_1;
  u8_t edge_bit_2;
} interrupt_reg_ctrl_t;

typedef struct
{
  interrupt_error (*init)(u8_t, interrupt_mode_t);
  interrupt_error (*read_flag)(u8_t, u8_t *);
  interrupt_error (*clear_flag)(u8_t);

} interrupt_handlers_t;

typedef struct
{
  interrupt_unit_number_t unit;
  interrupt_reg_ctrl_t ctrl_regs;
  interrupt_handlers_t handler;
} interrupt_unit_t;

typedef struct
{
  interrupt_unit_t* unit0;
  interrupt_unit_t* unit1;
  interrupt_unit_t* unit2;
} interrupt_driver_t;

interrupt_error mcal_interrupt_get_driver_info(interrupt_driver_t *driver);
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
