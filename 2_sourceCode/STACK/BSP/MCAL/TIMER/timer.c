/** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** timer.c
 **************************************************************************
 **                              Includes                                **
 *************************************************************************/
#include "timer.h"
/*************************************************************************/
/*                     Static Functions Prototype                        */
/**************************************************************************
 ** getPreScaler()
 **
 ** parameter: timer_preScaler_t preScaller
 ** return    : u16_t
 ***************************************************************************
 ** this function is used to get the actual values of pre-scaller
 **************************************************************************/
static double getPreScaler(timer_preScaler_t preScaller);
/**************************************************************************
 **                              Global Variable                         **
 *************************************************************************/
timer_module_t timer_0 =
    {
        .type = TIMER_BIT_8,
        .number = TIMER_0,
        .ctr_regs_config = (timer_8_bit_ctrl_regs *){
            TCCR0A,
            TCCR0B,
            TIMSK0,
            OCR0A,
            OCR0B,
            TCNT0,
        },
        .ticks = 0,
        .overflow = 0,
        .a_ptr = NULL_PTR};

timer_module_t timer_1 =
    {
        .type = TIMER_BIT_16,
        .number = TIMER_1,
        .ctr_regs_config = (timer_16_bit_ctrl_regs *){
            TCCR1A,
            TCCR1B,
            TCCR1C,
            TIMSK1,
            OCR1AL,
            OCR1AH,
            OCR1BL,
            OCR1BH,
            TCNT1L,
            TCNT1H},
        .ticks = 0,
        .overflow = 0,
        .a_ptr = NULL_PTR};

timer_module_t timer_2 =
    {
        .type = TIMER_BIT_8,
        .number = TIMER_2,
        .ctr_regs_config = (timer_8_bit_ctrl_regs *){
            TCCR2A,
            TCCR2B,
            TIMSK2,
            OCR2A,
            OCR2B,
            TCNT2,
        },
        .ticks = 0,
        .overflow = 0,
        .a_ptr = NULL_PTR};

timer_module_t timer_3 =
    {
        .type = TIMER_BIT_16,
        .number = TIMER_3,
        .ctr_regs_config = (timer_16_bit_ctrl_regs *){
            TCCR3A,
            TCCR3B,
            TCCR3C,
            TIMSK3,
            OCR3AL,
            OCR3AH,
            OCR3BL,
            OCR3BH,
            TCNT3L,
            TCNT3H},
        .ticks = 0,
        .overflow = 0,
        .a_ptr = NULL_PTR};

timer_device_t timer_device =
    {
        .timers[TIMER_0] = &timer_0,
        .timers[TIMER_2] = &timer_2,
        .timers[TIMER_1] = &timer_1,
        .timers[TIMER_3] = &timer_3};
/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

timer_error_t mcal_timer_init(timer_t *timer)
{
  timer_error_t error = TIMER_STATE_SUCCESS;

  timer_config_t timer_config;
  timer_pwm_config_t pwm_config;

  timer_module_t *timer_module = (timer_device.timers[timer->timer_number]);

  setGlobalInterrupt;

  double preScallerValue = (double)getPreScaler(timer->preScaler);
  double resolution = (double)preScallerValue / (double)F_CPU;
  double registerMaxTime = 0;

  /*************************************************************************/
  /* configure configs for pwm and normal mode
  /*************************************************************************/

  /*************************************************************************/
  /* configure types
  /*************************************************************************/

  switch (timer->type)
  {
  case TIMER_BIT_8:
  {
    timer_8_bit_ctrl_regs *regs = (timer_8_bit_ctrl_regs *)timer_module->ctr_regs_config;
    reg_mask_write(regs->ctrl_reg_0, PRE_SCALER_MASK, timer->preScaler);
    registerMaxTime = resolution * TIMER_BIT_8_MAX * 1000;
    register(regs->counter) = 0;

    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      timer_config = *((timer_config_t *)timer->config);

      /* attach overflow value to timer so we can use it in callback */
      timer_module->overflow = timer_config.tick_ms_seconds / (double)registerMaxTime;

      clr_bit(regs->ctrl_reg_0, WGMN0);
      clr_bit(regs->ctrl_reg_0, WGMN1);
      clr_bit(regs->ctrl_reg_1, WGMN2);

      break;
    }
    case TIMER_CTC_MODE:
    {
      timer_config = *((timer_config_t *)timer->config);

      register(regs->counter) = 0;
      clr_bit(regs->ctrl_reg_0, WGMN0);
      set_bit(regs->ctrl_reg_0, WGMN1);
      clr_bit(regs->ctrl_reg_1, WGMN2);

      /* if the time we need to wait can be used with 8 bit timer in CTC mode
			 * meaning that if the value of seconds to wait converted to digital number
			 * less that 256 with the given pre-scaller */
      if (timer_config.tick_ms_seconds < (registerMaxTime))
      {
        if (timer->unit == UNIT_A)
        {
          // Set Compare Value
          register(regs->cmp_reg_A) = (u8_t)(((timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue);
        }
        else if (timer->unit == UNIT_B)
        {
          register(regs->cmp_reg_B) = (u8_t)(((timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue);
        }
        else
        {
          error = TIMER_STATE_INVALID_ARGUMENT;
        }
      }
      else
      {
        error = TIMER_STATE_INVALID_ARGUMENT;
      }
      break;
    }

    case TIMER_PWM_MODE:
    {
      pwm_config = *((timer_pwm_config_t *)timer->config);

      mcal_gpio_pin_init(pwm_config.channel_port,
                         pwm_config.channel_pin,
                         DIR_OUTPUT);

      /* choosing mode of operation fast pwm */
      set_bit(regs->ctrl_reg_0, WGMN0);
      set_bit(regs->ctrl_reg_0, WGMN1);
      clr_bit(regs->ctrl_reg_1, WGMN2);

      if (timer->unit == UNIT_A)
      {
        // Set Compare Value
        clr_bit(regs->ctrl_reg_0, COMNA0);
        set_bit(regs->ctrl_reg_0, COMNA1);
      }
      else if (timer->unit == UNIT_B)
      {
        clr_bit(regs->ctrl_reg_0, COMNB0);
        set_bit(regs->ctrl_reg_0, COMNB1);
      }
      else
      {
        error = TIMER_STATE_INVALID_ARGUMENT;
      }

      break;
    }

    default:
    {
      error = TIMER_STATE_INVALID_MODE;
      break;
    }
    }
    break;
  }

  case TIMER_BIT_16:
  {
    timer_16_bit_ctrl_regs *regs = (timer_16_bit_ctrl_regs *)timer_module->ctr_regs_config;
    reg_mask_write(regs->ctrl_reg_0, PRE_SCALER_MASK, timer->preScaler);
    registerMaxTime = resolution * TIMER_BIT_8_MAX * 1000;

    register(regs->counter_L) = 0;
    register(regs->counter_H) = 0;

    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      timer_config = *((timer_config_t *)timer->config);

      /* attach overflow value to timer so we can use it in callback */
      timer_module->overflow = timer_config.tick_ms_seconds / (double)registerMaxTime;

      clr_bit(regs->ctrl_reg_0, WGMN0);
      clr_bit(regs->ctrl_reg_0, WGMN1);
      clr_bit(regs->ctrl_reg_1, WGMN2);
      clr_bit(regs->ctrl_reg_1, WGMN3);

      break;
    }
    case TIMER_CTC_MODE:
    {
      timer_config = *((timer_config_t *)timer->config);

      clr_bit(regs->ctrl_reg_0, WGMN0);
      clr_bit(regs->ctrl_reg_0, WGMN1);
      set_bit(regs->ctrl_reg_1, WGMN2);
      clr_bit(regs->ctrl_reg_1, WGMN3);

      /* if the time we need to wait can be used with 8 bit timer in CTC mode
			 * meaning that if the value of seconds to wait converted to digital number
			 * less that 256 with the given pre-scaller */
      if (timer_config.tick_ms_seconds < (registerMaxTime))
      {
        if (timer->unit == UNIT_A)
        {
          // Set Compare Value
          register(regs->cmp_reg_A_L) = ((u8_t)(((timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue));
          register(regs->cmp_reg_A_H) = ((u16_t)(((timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue) >> 8);
        }
        else if (timer->unit == UNIT_B)
        {
          register(regs->cmp_reg_B_L) = ((u8_t)(((timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue));
          register(regs->cmp_reg_B_H) = ((u16_t)(((timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue) >> 8);
        }
        else
        {
          error = TIMER_STATE_INVALID_ARGUMENT;
        }
      }
      else
      {
        error = TIMER_STATE_INVALID_ARGUMENT;
      }
      break;
    }

    case TIMER_PWM_MODE:
    {
      pwm_config = *((timer_pwm_config_t *)timer->config);

      mcal_gpio_pin_init(pwm_config.channel_port,
                         pwm_config.channel_pin,
                         DIR_OUTPUT);

      /* choosing mode of operation fast pwm */
      set_bit(regs->ctrl_reg_0, WGMN0);
      set_bit(regs->ctrl_reg_0, WGMN1);
      set_bit(regs->ctrl_reg_1, WGMN2);
      set_bit(regs->ctrl_reg_1, WGMN3);

      if (timer->unit == UNIT_A)
      {
        // Set Compare Value
        clr_bit(regs->ctrl_reg_0, COMNA0);
        set_bit(regs->ctrl_reg_0, COMNA1);
      }
      else if (timer->unit == UNIT_B)
      {
        clr_bit(regs->ctrl_reg_0, COMNB0);
        set_bit(regs->ctrl_reg_0, COMNB1);
      }
      else
      {
        error = TIMER_STATE_INVALID_ARGUMENT;
      }
      break;
    }

    default:
    {
      error = TIMER_STATE_INVALID_MODE;
      break;
    }
    }
  }
  default:
    error = TIMER_STATE_INVALID_TIMER;
    break;
  }

  /*************************************************************************/
  /* configure modes of operations
  /*************************************************************************/

  return error;
}

timer_error_t mcal_timer_start(timer_t *timer)
{
  timer_error_t error = TIMER_STATE_SUCCESS;
  timer_module_t *timer_module = (timer_module_t *)(timer_device.timers[timer->timer_number]);

  switch (timer->type)
  {
  case TIMER_BIT_8:
  {
    timer_8_bit_ctrl_regs *regs = (timer_8_bit_ctrl_regs *)timer_module->ctr_regs_config;
    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      set_bit(regs->int_reg_0, TOIEN);
      break;
    }

    case TIMER_CTC_MODE:
    {
      switch (timer->unit)
      {
      case UNIT_A:
      {
        set_bit(regs->int_reg_0, OCIENA);
        break;
      }

      case UNIT_B:
      {
        set_bit(regs->int_reg_0, OCIENB);
        break;
      }

      default:
      {
        error = TIMER_STATE_INVALID_MODE;
        break;
      }
      }
      break;
    }

    default:
    {
      error = TIMER_STATE_INVALID_MODE;
      break;
    }
    }
    break;
  }

  case TIMER_BIT_16:
  {
    timer_16_bit_ctrl_regs *regs = (timer_16_bit_ctrl_regs *)timer_module->ctr_regs_config;

    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      set_bit(regs->int_reg_0, TOIEN);
      break;
    }

    case TIMER_CTC_MODE:
    {
      switch (timer->unit)
      {
      case UNIT_A:
      {
        set_bit(timer_16_bit->int_reg_0, OCIENA);
        break;
      }

      case UNIT_B:
      {
        set_bit(timer_16_bit->int_reg_0, OCIENB);
        break;
      }

      default:
      {
        error = TIMER_STATE_INVALID_MODE;
        break;
      }
      }
      break;
    }

    default:
    {
      error = TIMER_STATE_INVALID_MODE;
      break;
    }
    }
    break;
  }

  default:
  {
    error = TIMER_STATE_INVALID_ARGUMENT;
    break;
  }
  }

  return error;
}

timer_error_t mcal_timer_stop(timer_t *timer)
{
  timer_error_t error = TIMER_STATE_SUCCESS;
  switch (timer->type)
  {
  case TIMER_BIT_8:
  {
    timer_8_module_t *timer_8_bit = (timer_8_module_t *)(timer_device.timers[timer->timer_number]);

    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      clr_bit(timer_8_bit->int_reg_0, TOIEN);
      break;
    }

    case TIMER_CTC_MODE:
    {
      switch (timer->unit)
      {
      case UNIT_A:
      {
        clr_bit(timer_8_bit->int_reg_0, OCIENA);
        break;
      }

      case UNIT_B:
      {
        clr_bit(timer_8_bit->int_reg_0, OCIENB);
        break;
      }

      default:
      {
        error = TIMER_STATE_INVALID_MODE;
        break;
      }
      }
      break;
    }

    default:
    {
      error = TIMER_STATE_INVALID_MODE;
      break;
    }
    }
    break;
  }

  case TIMER_BIT_16:
  {
    timer_16_module_t *timer_16_bit = (timer_16_module_t *)(timer_device.timers[timer->timer_number]);

    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      clr_bit(timer_16_bit->int_reg_0, TOIEN);
      break;
    }

    case TIMER_CTC_MODE:
    {
      switch (timer->unit)
      {
      case UNIT_A:
      {
        clr_bit(timer_16_bit->int_reg_0, OCIENA);
        break;
      }

      case UNIT_B:
      {
        clr_bit(timer_16_bit->int_reg_0, OCIENB);
        break;
      }

      default:
      {
        error = TIMER_STATE_INVALID_MODE;
        break;
      }
      }
      break;
    }

    default:
    {
      error = TIMER_STATE_INVALID_MODE;
      break;
    }
    }
    break;
  }

  default:
  {
    error = TIMER_STATE_INVALID_ARGUMENT;
    break;
  }
  }

  return error;
}

timer_error_t mcal_timer_pwm_output(timer_t *timer, u16_t duty)
{
  timer_error_t error = TIMER_STATE_SUCCESS;

  switch (timer->type)
  {
  case TIMER_BIT_8:
  {
    timer_8_module_t *timer_8_bit = (timer_8_module_t *)(timer_device.timers[timer->timer_number]);
    switch (timer->unit)
    {
    case UNIT_A:
    {
      register(timer_8_bit->cmp_reg_A) = (u8_t)duty;
      break;
    }

    case UNIT_B:
    {
      register(timer_8_bit->cmp_reg_B) = (u8_t)duty;
      break;
    }

    default:
    {
      break;
    }
    }
    break;
  }

  case TIMER_BIT_16:
  {
    timer_16_module_t *timer_16_bit = (timer_16_module_t *)(timer_device.timers[timer->timer_number]);
    switch (timer->unit)
    {
    case UNIT_A:
    {
      register(timer_16_bit->cmp_reg_A_L) = (u8_t)duty;
      register(timer_16_bit->cmp_reg_A_H) = (u8_t)duty >> 8;
      break;
    }

    case UNIT_B:
    {
      register(timer_16_bit->cmp_reg_B_L) = (u8_t)duty;
      register(timer_16_bit->cmp_reg_B_H) = (u8_t)duty >> 8;
      break;
    }

    default:
    {
      error = TIMER_STATE_INVALID_ARGUMENT;
      break;
    }
    }
    break;
  }

  default:
  {
    error = TIMER_STATE_INVALID_ARGUMENT;
    break;
  }
  }
  return error;
}

/*************************************************************************/
/*                     Static Functions Implementation                   */
/*************************************************************************/
static double getPreScaler(timer_preScaler_t preScaller)
{
  double value = 0;
  switch (preScaller)
  {
  case F_CPU_CLOCK:
  {
    value = 1;
    break;
  }
  case F_CPU_8:
  {
    value = 8;
    break;
  }
  case F_CPU_64:
  {
    value = 64;
    break;
  }
  case F_CPU_256:
  {
    value = 256;
    break;
  }
  case F_CPU_1024:
  {
    value = 1024;
    break;
  }
  default:
  {
    value = 0;
  }
  }

  return value;
}

/*************************************************************************/
/*                     Interrupts Implementation                         */
/*************************************************************************/

/* TIMER2_COMP_vect */
void __vector_4(void)
{
  if (g_callBackPtr != NULL_PTR)
  {
    (*g_callBackPtr)();
  }
}

/* TIMER2_OVF_vect */
void __vector_5(void)
{
  g_ticks_timer_2++;
  if (g_callBackPtr != NULL_PTR)
  {
    if (g_ticks_timer_2 >= overflow_2)
    {
      g_ticks_timer_2 = 0;
      (*g_callBackPtr)();
    }
  }
}

/* TIMER1_CAPT_vect */
void __vector_6(void)
{
  if (g_callBackPtr != NULL_PTR)
  {
    (*g_callBackPtr)();
  }
}

/* TIMER1_COMPA_vect */
void __vector_7(void)
{
  if (g_callBackPtr != NULL_PTR)
  {
    (*g_callBackPtr)();
  }
}

/* TIMER1_COMPB_vect */
void __vector_8(void)
{
  if (g_callBackPtr != NULL_PTR)
  {
    (*g_callBackPtr)();
  }
}

/* TIMER1_OVF_vect */
void __vector_9(void)
{
  g_ticks_timer_1++;
  if (g_callBackPtr != NULL_PTR)
  {
    if (g_ticks_timer_1 >= overflow_1)
    {
      g_ticks_timer_1 = 0;
      (*g_callBackPtr)();
    }
  }
}

/* TIMER0_OVF_vect */
void __vector_11(void)
{
  g_ticks_timer_0++;
  if (g_callBackPtr != NULL_PTR)
  {
    if (g_ticks_timer_0 >= overflow_0)
    {
      g_ticks_timer_0 = 0;
      (*g_callBackPtr)();
    }
  }
}
