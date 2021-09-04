/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** e_interrupt.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "e_interrupt.h"
/**************************************************************************/
/*                          Global Variables                              */
/**************************************************************************/
static u8_t *TAG = (u8_t *)"E_INTERRUPT";
/**************************************************************************/
/*                     Functions Implementation                           */
/**************************************************************************/

interrupt_error mcal_interrupt_initialize(u8_t interruptNo, interrupt_mode_t mode)
{
  interrupt_error error = INTERRUPT_STATE_SUCCESS;

  /*enable global interrupts*/
  setGlobalInterrupt;

  set_bit(EIMSK, interruptNo);

  switch (mode)
  {

  /*
  ISC00   0 INT_0
  ISC01   1 INT_0
  ISC10   2 INT_1
  ISC11   3 INT_1
  ISC20   4 INT_2
  ISC21   5 INT_2
 */

  case RISING_EDGE:
  {
    /* bits needed is 0 and 1 for int 0
       bits needed is 1 and 2 for int 1
       bits needed is 2 and 4 for int 2
      so the following equation satisfy this requirment */
    set_bit(EICRA, (2 * interruptNo));
    set_bit(EICRA, ((2 * interruptNo) + 1));

    logger_write_debug_println_with_variable(
        LOG_MCAL,
        TAG,
        (u8_t *)"configured in rising edge mode , interrupt number",
        interruptNo);

    break;
  }

  case FALLING_EDGE:
  {
    /* bits needed is 0 and 1 for int 0
       bits needed is 1 and 2 for int 1
       bits needed is 2 and 4 for int 2
      so the following equation satisfy this requirment */
    set_bit(EICRA, (2 * interruptNo));
    clr_bit(EICRA, ((2 * interruptNo) + 1));

    logger_write_debug_println_with_variable(
        LOG_MCAL,
        TAG,
        (u8_t *)"configured in falling edge mode , interrupt number",
        interruptNo);

    break;
  }

  case CHANGING_EDGE:
  {
    /* bits needed is 0 and 1 for int 0
       bits needed is 1 and 2 for int 1
       bits needed is 2 and 4 for int 2
      so the following equation satisfy this requirment */
    clr_bit(EICRA, (2 * interruptNo));
    set_bit(EICRA, ((2 * interruptNo) + 1));

    logger_write_debug_println_with_variable(
        LOG_MCAL,
        TAG,
        (u8_t *)"configured in changing edge mode , interrupt number",
        interruptNo);
    break;
  }

  default:
  {
    error = INTERRUPT_STATE_INVALID_OPERATION_MODE;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied operation mode");
    break;
  }
  }

  return error;
}

interrupt_error mcal_interrupt_read_flag(u8_t flag, u8_t *result)
{
  interrupt_error error = INTERRUPT_STATE_SUCCESS;

  /* INTF0 results to 0 so the 0 bit is needed to be checked */
  /* INTF1 results to 1 so the 1 bit is needed to be checked */
  /* INTFN results to N so the N bit is needed to be checked */

  if (flag == INTF0 || flag == INTF1 || flag == INTF2)
  {
    *result = bit_is_set(EIFR, flag);
  }
  else
  {
    error = INTERRUPT_STATE_INVAILD_INTERRUPT_NUMBER;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied external number");
  }

  return error;
}

interrupt_error mcal_interrupt_clear_flag(u8_t flag)
{
  interrupt_error error = INTERRUPT_STATE_SUCCESS;

  /* INTF0 results to 0 so the 0 bit is needed to be cleared */
  /* INTF1 results to 1 so the 1 bit is needed to be cleared */
  /* INTFN results to N so the N bit is needed to be cleared */

  if (flag == INTF0 || flag == INTF1 || flag == INTF2)
  {
    clr_bit(EIFR, flag);
  }
  else
  {
    error = INTERRUPT_STATE_INVAILD_INTERRUPT_NUMBER;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied external number");
  }
  return error;
}