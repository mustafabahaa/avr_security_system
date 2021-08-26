/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** e_interrupt.c
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "e_interrupt.h"
/*************************************************************************/
/*                          Global Variables                             */
/*************************************************************************/
static u8_t *TAG = (u8_t *)"E_INTERRUPT";
/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

interrupt_error mcal_interrupt_initialize(u8_t interruptNo,
                                          interrupt_mode_t mode)
{
  interrupt_error error = INTERRUPT_STATE_SUCCESS;

  /*enable global interrupts*/
  setGlobalInterrupt;

  switch (interruptNo)
  {
  case INT0:
  {
    /*enable interrupt 0 */
    set_bit(GICR, INT0);

    switch (mode)
    {
    case RISING_EDGE:
      set_bit(MCUCR, ISC00);
      set_bit(MCUCR, ISC01);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in rising edge mode , interrupt number",
          interruptNo);

      break;

    case FALLING_EDGE:
      set_bit(MCUCR, ISC01);
      clr_bit(MCUCR, ISC00);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in falling edge mode , interrupt number",
          interruptNo);

      break;

    case CHANGING_EDGE:
      set_bit(MCUCR, ISC00);
      clr_bit(MCUCR, ISC01);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in changing edge mode , interrupt number",
          interruptNo);
      break;

    default:
      error = INTERRUPT_STATE_INVALID_OPERATION_MODE;
      logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied operation mode");
    }
    break;
  }

  case INT1:
  {
    /*enable interrupt 1 */
    set_bit(GICR, INT1);

    switch (mode)
    {
    case RISING_EDGE:
      set_bit(MCUCR, ISC11);
      set_bit(MCUCR, ISC10);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in rising edge mode , interrupt number",
          interruptNo);

      break;

    case FALLING_EDGE:
      set_bit(MCUCR, ISC11);
      clr_bit(MCUCR, ISC10);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in falling edge mode , interrupt number",
          interruptNo);

      break;

    case CHANGING_EDGE:
      set_bit(MCUCR, ISC10);
      clr_bit(MCUCR, ISC11);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in changing edge mode , interrupt number",
          interruptNo);

      break;

    default:
      error = INTERRUPT_STATE_INVALID_OPERATION_MODE;
      logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied operation mode");
    }
    break;
  }

  case INT2:
  {
    /*enable interrupt 2 */
    set_bit(GICR, INT2);

    switch (mode)
    {
    case RISING_EDGE:
      set_bit(MCUCR, ISC2);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in rising edge mode , interrupt number",
          interruptNo);
      break;

    case FALLING_EDGE:
      clr_bit(MCUCSR, ISC2);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in falling edge mode , interrupt number",
          interruptNo);

      break;

    default:
      error = INTERRUPT_STATE_INVALID_OPERATION_MODE;
      logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied operation mode");
    }
    break;
  }

  default:
  {
    error = INTERRUPT_STATE_INVAILD_INTERRUPT_NUMBER;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied external interrupt number");
  }
  }
  return error;
}

interrupt_error mcal_interrupt_read_flag(u8_t flag, u8_t *result)
{
  interrupt_error error = INTERRUPT_STATE_SUCCESS;

  switch (flag)
  {
  case INTF0:
    *result = bit_is_set(GIFR, INTF0);
    break;

  case INTF1:
    *result = bit_is_set(GIFR, INTF1);
    break;

  case INTF2:
    *result = bit_is_set(GIFR, INTF2);
    break;

  default:
    error = INTERRUPT_STATE_INVAILD_INTERRUPT_NUMBER;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied external number");
    break;
  }
  return error;
}

interrupt_error mcal_interrupt_clear_flag(u8_t flag)
{
  interrupt_error error = INTERRUPT_STATE_SUCCESS;

  switch (flag)
  {
  case INTF0:
    clr_bit(GIFR, INTF0);
    break;

  case INTF1:
    clr_bit(GIFR, INTF1);
    break;

  case INTF2:
    clr_bit(GIFR, INTF2);
    break;

  default:
    error = INTERRUPT_STATE_INVAILD_INTERRUPT_NUMBER;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied external number");
    break;
  }
  return error;
}
