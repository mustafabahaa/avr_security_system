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

interrupt_error mcal_interrupt_get_driver_info(interrupt_driver_t *driver)
{
}

interrupt_error mcal_interrupt_initialize(u8_t interruptNo, interrupt_mode_t mode)
{
  interrupt_error error = INTERRUPT_STATE_SUCCESS;

  /*enable global interrupts*/
  setGlobalInterrupt;

  switch (interruptNo)
  {
  case INT0:
  {
    /*enable interrupt 0 */
    set_bit(EIMSK, INT0);

    switch (mode)
    {
    case RISING_EDGE:
    {
      set_bit(EICRA, ISC00);
      set_bit(EICRA, ISC01);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in rising edge mode , interrupt number",
          interruptNo);

      break;
    }

    case FALLING_EDGE:
    {
      set_bit(EICRA, ISC01);
      clr_bit(EICRA, ISC00);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in falling edge mode , interrupt number",
          interruptNo);

      break;
    }

    case CHANGING_EDGE:
    {
      set_bit(EICRA, ISC00);
      clr_bit(EICRA, ISC01);

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
    break;
  }

  case INT1:
  {
    /*enable interrupt 1 */
    set_bit(EIMSK, INT1);

    switch (mode)
    {
    case RISING_EDGE:
    {
      set_bit(EICRA, ISC11);
      set_bit(EICRA, ISC10);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in rising edge mode , interrupt number",
          interruptNo);

      break;
    }

    case FALLING_EDGE:
    {
      set_bit(EICRA, ISC11);
      clr_bit(EICRA, ISC10);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in falling edge mode , interrupt number",
          interruptNo);

      break;
    }

    case CHANGING_EDGE:
    {
      set_bit(EICRA, ISC10);
      clr_bit(EICRA, ISC11);

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
    break;
  }

  case INT2:
  {
    /*enable interrupt 2 */
    set_bit(EIMSK, INT2);

    switch (mode)
    {
    case RISING_EDGE:
    {
      set_bit(EICRA, ISC21);
      set_bit(EICRA, ISC20);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in rising edge mode , interrupt number",
          interruptNo);
      break;
    }

    case FALLING_EDGE:
    {
      set_bit(EICRA, ISC21);
      clr_bit(EICRA, ISC20);

      logger_write_debug_println_with_variable(
          LOG_MCAL,
          TAG,
          (u8_t *)"configured in falling edge mode , interrupt number",
          interruptNo);

      break;
    }

    case CHANGING_EDGE:
    {
      set_bit(EICRA, ISC20);
      clr_bit(EICRA, ISC21);

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
    break;
  }

  default:
  {
    error = INTERRUPT_STATE_INVAILD_INTERRUPT_NUMBER;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied external interrupt number");
    break;
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
  {
    *result = bit_is_set(EIFR, INTF0);
    break;
  }

  case INTF1:
  {
    *result = bit_is_set(EIFR, INTF1);
    break;
  }

  case INTF2:
  {
    *result = bit_is_set(EIFR, INTF2);
    break;
  }

  default:
  {
    error = INTERRUPT_STATE_INVAILD_INTERRUPT_NUMBER;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied external number");
    break;
  }
  }
  return error;
}

interrupt_error mcal_interrupt_clear_flag(u8_t flag)
{
  interrupt_error error = INTERRUPT_STATE_SUCCESS;

  switch (flag)
  {
  case INTF0:
  {
    clr_bit(EIFR, INTF0);
    break;
  }

  case INTF1:
  {
    clr_bit(EIFR, INTF1);
    break;
  }

  case INTF2:
  {
    clr_bit(EIFR, INTF2);
    break;
  }

  default:
  {
    error = INTERRUPT_STATE_INVAILD_INTERRUPT_NUMBER;
    logger_write_error_println(LOG_MCAL, TAG, (u8_t *)"invalied external number");
    break;
  }
  }
  return error;
}

interrupt_unit_t unit_0 =
{
  .unit = interrupt_unit_0,
  .ctrl_regs =
  {
          .ctrl_reg = EIMSK,
          .edge_reg = EICRA,
          .edge_bit_1 = ISC00,
          .edge_bit_2 = ISC01
  },
  .handler = 
  {
      .init = &mcal_interrupt_initialize,
      .read_flag = &mcal_interrupt_read_flag,
      .clear_flag = &mcal_interrupt_clear_flag
  }
};


interrupt_unit_t unit_1 =
{
  .unit = interrupt_unit_1,
  .ctrl_regs =
  {
          .ctrl_reg = EIMSK,
          .edge_reg = EICRA,
          .edge_bit_1 = ISC10,
          .edge_bit_2 = ISC11
  },
  .handler = 
  {
      .init = &mcal_interrupt_initialize,
      .read_flag = &mcal_interrupt_read_flag,
      .clear_flag = &mcal_interrupt_clear_flag
  }
};

interrupt_unit_t unit_2 =
{
  .unit = interrupt_unit_2,
  .ctrl_regs =
  {
          .ctrl_reg = EIMSK,
          .edge_reg = EICRA,
          .edge_bit_1 = ISC20,
          .edge_bit_2 = ISC21
  },
  .handler = 
  {
      .init = &mcal_interrupt_initialize,
      .read_flag = &mcal_interrupt_read_flag,
      .clear_flag = &mcal_interrupt_clear_flag
  }
};

interrupt_driver_t driver = 
{
  .unit0 = &unit_0,
  .unit1 = &unit_1,
  .unit2 = &unit_2
};