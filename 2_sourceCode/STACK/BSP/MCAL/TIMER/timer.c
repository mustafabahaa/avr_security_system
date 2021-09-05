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

typedef struct
{
  timer_number_t number;
  double ticks;
  double overflow;
  void (*ovf_callback)(void);
  void (*unit_a_callback)(void);
  void (*unit_b_callback)(void);
} timer_manage_t;

/**************************************************************************
 **                              Global Variable                         **
 *************************************************************************/
static timer_manage_t timer_manager[TIMERS_MAX_COUNT];
/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

timer_error_t mcal_timer_init(timer_t *timer)
{
  timer_error_t error = TIMER_STATE_SUCCESS;

  setGlobalInterrupt;

  double preScallerValue = (double)getPreScaler(timer->preScaler);
  double resolution = (double)preScallerValue / (double)F_CPU;
  double registerMaxTime = 0;

  switch (timer->number)
  {
  case TIMER_0:
  {
    reg_mask_write(TCCR0A, PRE_SCALER_MASK, timer->preScaler);
    registerMaxTime = resolution * TIMER_BIT_8_MAX * 1000;
    register(TCNT0) = 0;

    timer_manager[TIMER_0].ticks = 0;
    timer_manager[TIMER_0].overflow = 0;
    timer_manager[TIMER_0].number = TIMER_0;
    timer_manager[TIMER_0].ovf_callback = NULL_PTR;
    timer_manager[TIMER_0].unit_a_callback = NULL_PTR;
    timer_manager[TIMER_0].unit_b_callback = NULL_PTR;

    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      /* attach overflow value to timer so we can use it in unit_a_callback */
      timer_manager[TIMER_0].overflow = timer->timer_config.tick_ms_seconds / (double)registerMaxTime;
      timer_manager[TIMER_0].ovf_callback = timer->ovf_callback;

      clr_bit(TCCR0A, WGMN0);
      clr_bit(TCCR0A, WGMN1);
      clr_bit(TCCR0B, WGMN2);

      break;
    }
    case TIMER_CTC_MODE:
    {
      clr_bit(TCCR0A, WGMN0);
      set_bit(TCCR0A, WGMN1);
      clr_bit(TCCR0B, WGMN2);

      /* if the time we need to wait can be used with 8 bit timer in CTC mode
			 * meaning that if the value of seconds to wait converted to digital number
			 * less that 256 with the given pre-scaller */
      if (timer->timer_config.tick_ms_seconds < (registerMaxTime))
      {
        if (timer->unit == UNIT_A)
        {
          // Set Compare Value
          timer_manager[TIMER_0].unit_a_callback = timer->unit_a_callback;
          register(OCR0A) = (u8_t)(((timer->timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue);
        }
        else if (timer->unit == UNIT_B)
        {
          timer_manager[TIMER_0].unit_b_callback = timer->unit_b_callback;
          register(OCR0B) = (u8_t)(((timer->timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue);
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
      mcal_gpio_pin_init(timer->pwm_config.channel_port,
                         timer->pwm_config.channel_pin,
                         DIR_OUTPUT);

      /* choosing mode of operation fast pwm */
      set_bit(TCCR0A, WGMN0);
      set_bit(TCCR0A, WGMN1);
      clr_bit(TCCR0B, WGMN2);

      if (timer->unit == UNIT_A)
      {
        // Set Compare Value
        clr_bit(TCCR0A, COMNA0);
        set_bit(TCCR0A, COMNA1);
      }
      else if (timer->unit == UNIT_B)
      {
        clr_bit(TCCR0A, COMNB0);
        set_bit(TCCR0A, COMNB1);
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
  case TIMER_1:
  {
    reg_mask_write(TCCR1A, PRE_SCALER_MASK, timer->preScaler);
    registerMaxTime = resolution * TIMER_BIT_16_MAX * 1000;
    register(TCNT1L) = 0;
    register(TCNT1H) = 0;

    timer_manager[TIMER_1].ticks = 0;
    timer_manager[TIMER_1].overflow = 0;
    timer_manager[TIMER_1].number = TIMER_1;
    timer_manager[TIMER_1].ovf_callback = NULL_PTR;
    timer_manager[TIMER_1].unit_a_callback = NULL_PTR;
    timer_manager[TIMER_1].unit_b_callback = NULL_PTR;

    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      /* attach overflow value to timer so we can use it in unit_a_callback */
      timer_manager[TIMER_1].overflow = timer->timer_config.tick_ms_seconds / (double)registerMaxTime;
      timer_manager[TIMER_1].ovf_callback = timer->ovf_callback;

      clr_bit(TCCR1A, WGMN0);
      clr_bit(TCCR1A, WGMN1);
      clr_bit(TCCR1B, WGMN2);
      clr_bit(TCCR1B, WGMN3);
      break;
    }
    case TIMER_CTC_MODE:
    {
      clr_bit(TCCR0A, WGMN0);
      set_bit(TCCR0A, WGMN1);
      clr_bit(TCCR0B, WGMN2);
      clr_bit(TCCR0B, WGMN3);

      /* if the time we need to wait can be used with 8 bit timer in CTC mode
			 * meaning that if the value of seconds to wait converted to digital number
			 * less that 256 with the given pre-scaller */
      if (timer->timer_config.tick_ms_seconds < (registerMaxTime))
      {
        if (timer->unit == UNIT_A)
        {
          // Set Compare Value
          timer_manager[TIMER_1].unit_a_callback = timer->unit_a_callback;
          register(OCR1AL) = ((u8_t)(((timer->timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue));
          register(OCR1AH) = ((u16_t)(((timer->timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue) >> 8);
        }
        else if (timer->unit == UNIT_B)
        {
          timer_manager[TIMER_1].unit_b_callback = timer->unit_b_callback;
          register(OCR1BL) = ((u8_t)(((timer->timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue));
          register(OCR1BH) = ((u16_t)(((timer->timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue) >> 8);
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
      mcal_gpio_pin_init(timer->pwm_config.channel_port,
                         timer->pwm_config.channel_pin,
                         DIR_OUTPUT);

      /* choosing mode of operation fast pwm */
      set_bit(TCCR0A, WGMN0);
      set_bit(TCCR0A, WGMN1);
      clr_bit(TCCR0B, WGMN2);
      set_bit(TCCR0B, WGMN3);

      if (timer->unit == UNIT_A)
      {
        // Set Compare Value
        clr_bit(TCCR1A, COMNA0);
        set_bit(TCCR1A, COMNA1);
      }
      else if (timer->unit == UNIT_B)
      {
        clr_bit(TCCR1A, COMNB0);
        set_bit(TCCR1A, COMNB1);
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
  case TIMER_2:
  {
    reg_mask_write(TCCR2A, PRE_SCALER_MASK, timer->preScaler);
    registerMaxTime = resolution * TIMER_BIT_8_MAX * 1000;
    register(TCNT2) = 0;

    timer_manager[TIMER_2].ticks = 0;
    timer_manager[TIMER_2].overflow = 0;
    timer_manager[TIMER_2].number = TIMER_2;
    timer_manager[TIMER_2].ovf_callback = NULL_PTR;
    timer_manager[TIMER_2].unit_a_callback = NULL_PTR;
    timer_manager[TIMER_2].unit_b_callback = NULL_PTR;

    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      /* attach overflow value to timer so we can use it in unit_a_callback */
      timer_manager[TIMER_2].overflow = timer->timer_config.tick_ms_seconds / (double)registerMaxTime;
      timer_manager[TIMER_2].ovf_callback = timer->ovf_callback;

      clr_bit(TCCR2A, WGMN0);
      clr_bit(TCCR2A, WGMN1);
      clr_bit(TCCR2B, WGMN2);

      break;
    }
    case TIMER_CTC_MODE:
    {
      clr_bit(TCCR2A, WGMN0);
      set_bit(TCCR2A, WGMN1);
      clr_bit(TCCR2B, WGMN2);

      /* if the time we need to wait can be used with 8 bit timer in CTC mode
			 * meaning that if the value of seconds to wait converted to digital number
			 * less that 256 with the given pre-scaller */
      if (timer->timer_config.tick_ms_seconds < (registerMaxTime))
      {
        if (timer->unit == UNIT_A)
        {
          timer_manager[TIMER_2].unit_a_callback = timer->unit_a_callback;
          register(OCR2A) = (u8_t)(((timer->timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue);
        }
        else if (timer->unit == UNIT_B)
        {
          timer_manager[TIMER_2].unit_b_callback = timer->unit_b_callback;
          register(OCR2B) = (u8_t)(((timer->timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue);
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
      mcal_gpio_pin_init(timer->pwm_config.channel_port,
                         timer->pwm_config.channel_pin,
                         DIR_OUTPUT);

      /* choosing mode of operation fast pwm */
      set_bit(TCCR2A, WGMN0);
      set_bit(TCCR2A, WGMN1);
      clr_bit(TCCR2B, WGMN2);

      if (timer->unit == UNIT_A)
      {
        // Set Compare Value
        clr_bit(TCCR2A, COMNA0);
        set_bit(TCCR2A, COMNA1);
      }
      else if (timer->unit == UNIT_B)
      {
        clr_bit(TCCR2A, COMNB0);
        set_bit(TCCR2A, COMNB1);
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
  case TIMER_3:
  {
    reg_mask_write(TCCR3A, PRE_SCALER_MASK, timer->preScaler);
    registerMaxTime = resolution * TIMER_BIT_16_MAX * 1000;
    register(TCNT3L) = 0;
    register(TCNT3H) = 0;

    timer_manager[TIMER_3].ticks = 0;
    timer_manager[TIMER_3].overflow = 0;
    timer_manager[TIMER_3].number = TIMER_3;
    timer_manager[TIMER_3].ovf_callback = NULL_PTR;
    timer_manager[TIMER_3].unit_a_callback = NULL_PTR;
    timer_manager[TIMER_3].unit_b_callback = NULL_PTR;

    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      /* attach overflow value to timer so we can use it in unit_a_callback */
      timer_manager[TIMER_3].overflow = timer->timer_config.tick_ms_seconds / (double)registerMaxTime;
      timer_manager[TIMER_3].ovf_callback = timer->ovf_callback;

      clr_bit(TCCR3A, WGMN0);
      clr_bit(TCCR3A, WGMN1);
      clr_bit(TCCR3B, WGMN2);
      clr_bit(TCCR3B, WGMN3);
      break;
    }
    case TIMER_CTC_MODE:
    {
      clr_bit(TCCR3A, WGMN0);
      set_bit(TCCR3A, WGMN1);
      clr_bit(TCCR3B, WGMN2);
      clr_bit(TCCR3B, WGMN3);

      /* if the time we need to wait can be used with 8 bit timer in CTC mode
			 * meaning that if the value of seconds to wait converted to digital number
			 * less that 256 with the given pre-scaller */
      if (timer->timer_config.tick_ms_seconds < (registerMaxTime))
      {
        if (timer->unit == UNIT_A)
        {
          timer_manager[TIMER_3].unit_a_callback = timer->unit_a_callback;
          register(OCR3AL) = ((u8_t)(((timer->timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue));
          register(OCR3AH) = ((u16_t)(((timer->timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue) >> 8);
        }
        else if (timer->unit == UNIT_B)
        {
          timer_manager[TIMER_3].unit_b_callback = timer->unit_b_callback;
          register(OCR3BL) = ((u8_t)(((timer->timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue));
          register(OCR3BH) = ((u16_t)(((timer->timer_config.tick_ms_seconds / 1000) * F_CPU) / preScallerValue) >> 8);
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
      mcal_gpio_pin_init(timer->pwm_config.channel_port,
                         timer->pwm_config.channel_pin,
                         DIR_OUTPUT);

      /* choosing mode of operation fast pwm */
      set_bit(TCCR3A, WGMN0);
      set_bit(TCCR3A, WGMN1);
      clr_bit(TCCR3B, WGMN2);
      set_bit(TCCR3B, WGMN3);

      if (timer->unit == UNIT_A)
      {
        // Set Compare Value
        clr_bit(TCCR3A, COMNA0);
        set_bit(TCCR3A, COMNA1);
      }
      else if (timer->unit == UNIT_B)
      {
        clr_bit(TCCR3A, COMNB0);
        set_bit(TCCR3A, COMNB1);
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
  default:
    error = TIMER_STATE_INVALID_TIMER;
    break;
  }

  return error;
}

timer_error_t mcal_timer_start(timer_t *timer)
{
  timer_error_t error = TIMER_STATE_SUCCESS;

  switch (timer->number)
  {
  case TIMER_0:
  {
    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      set_bit(TIMSK0, TOIEN);
      break;
    }

    case TIMER_CTC_MODE:
    {
      switch (timer->unit)
      {
      case UNIT_A:
      {
        set_bit(TIMSK0, OCIENA);
        break;
      }

      case UNIT_B:
      {
        set_bit(TIMSK0, OCIENB);
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
  case TIMER_1:
  {
    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      set_bit(TIMSK1, TOIEN);
      break;
    }

    case TIMER_CTC_MODE:
    {
      switch (timer->unit)
      {
      case UNIT_A:
      {
        set_bit(TIMSK1, OCIENA);
        break;
      }

      case UNIT_B:
      {
        set_bit(TIMSK1, OCIENB);
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
  case TIMER_2:
  {
    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      set_bit(TIMSK2, TOIEN);
      break;
    }

    case TIMER_CTC_MODE:
    {
      switch (timer->unit)
      {
      case UNIT_A:
      {
        set_bit(TIMSK2, OCIENA);
        break;
      }

      case UNIT_B:
      {
        set_bit(TIMSK2, OCIENB);
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
  case TIMER_3:
  {
    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      set_bit(TIMSK3, TOIEN);
      break;
    }

    case TIMER_CTC_MODE:
    {
      switch (timer->unit)
      {
      case UNIT_A:
      {
        set_bit(TIMSK3, OCIENA);
        break;
      }

      case UNIT_B:
      {
        set_bit(TIMSK3, OCIENB);
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

  switch (timer->number)
  {
  case TIMER_0:
  {
    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      clr_bit(TIMSK0, TOIEN);
      break;
    }

    case TIMER_CTC_MODE:
    {
      switch (timer->unit)
      {
      case UNIT_A:
      {
        clr_bit(TIMSK0, OCIENA);
        break;
      }

      case UNIT_B:
      {
        clr_bit(TIMSK0, OCIENB);
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
  case TIMER_1:
  {
    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      clr_bit(TIMSK1, TOIEN);
      break;
    }

    case TIMER_CTC_MODE:
    {
      switch (timer->unit)
      {
      case UNIT_A:
      {
        clr_bit(TIMSK1, OCIENA);
        break;
      }

      case UNIT_B:
      {
        clr_bit(TIMSK1, OCIENB);
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
  case TIMER_2:
  {
    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      clr_bit(TIMSK2, TOIEN);
      break;
    }

    case TIMER_CTC_MODE:
    {
      switch (timer->unit)
      {
      case UNIT_A:
      {
        clr_bit(TIMSK2, OCIENA);
        break;
      }

      case UNIT_B:
      {
        clr_bit(TIMSK2, OCIENB);
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
  case TIMER_3:
  {
    switch (timer->mode)
    {
    case TIMER_NORMAL_MODE:
    {
      clr_bit(TIMSK3, TOIEN);
      break;
    }

    case TIMER_CTC_MODE:
    {
      switch (timer->unit)
      {
      case UNIT_A:
      {
        clr_bit(TIMSK3, OCIENA);
        break;
      }

      case UNIT_B:
      {
        clr_bit(TIMSK3, OCIENB);
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

  switch (timer->number)
  {
  case TIMER_0:
  {
    switch (timer->unit)
    {
    case UNIT_A:
    {
      register(OCR0A) = (u8_t)duty;
      break;
    }

    case UNIT_B:
    {
      register(OCR0B) = (u8_t)duty;
      break;
    }

    default:
    {
      break;
    }
    }
    break;
  }

  case TIMER_1:
  {
    switch (timer->unit)
    {
    case UNIT_A:
    {
      register(OCR1AL) = (u8_t)duty;
      register(OCR1AH) = (u8_t)duty >> 8;
      break;
    }

    case UNIT_B:
    {
      register(OCR1BL) = (u8_t)duty;
      register(OCR1BH) = (u8_t)duty >> 8;
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

  case TIMER_2:
  {
    switch (timer->unit)
    {
    case UNIT_A:
    {
      register(OCR2A) = (u8_t)duty;
      break;
    }

    case UNIT_B:
    {
      register(OCR2B) = (u8_t)duty;
      break;
    }

    default:
    {
      break;
    }
    }
    break;
  }

  case TIMER_3:
  {
    switch (timer->unit)
    {
    case UNIT_A:
    {
      register(OCR3AL) = (u8_t)duty;
      register(OCR3AH) = (u8_t)duty >> 8;
      break;
    }

    case UNIT_B:
    {
      register(OCR3BL) = (u8_t)duty;
      register(OCR3BH) = (u8_t)duty >> 8;
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

/**************************************************************************/
/*                               Timer 0                                  */
/**************************************************************************/
/* Timer/Counter0 Compare Match A */
void TIMER0_COMPA_vect(void)
{
  if (timer_manager[TIMER_0].unit_a_callback != NULL_PTR)
  {
    (*timer_manager[TIMER_0].unit_a_callback)();
  }
}

/* Timer/Counter0 Compare Match B */
void TIMER0_COMPB_vect(void)
{
  if (timer_manager[TIMER_0].unit_b_callback != NULL_PTR)
  {
    (*timer_manager[TIMER_0].unit_b_callback)();
  }
}

/* Timer/Counter0 Overflow */
void TIMER0_OVF_vect(void)
{
  timer_manager[TIMER_0].ticks++;
  if (timer_manager[TIMER_0].ovf_callback != NULL_PTR)
  {
    if (timer_manager[TIMER_0].ticks >= timer_manager[TIMER_0].overflow)
    {
      timer_manager[TIMER_0].ticks = 0;
      (*timer_manager[TIMER_0].ovf_callback)();
    }
  }
}

/**************************************************************************/
/*                               Timer 1                                  */
/**************************************************************************/
/* Timer/Counter1 Capture Event */
void TIMER1_CAPT_vect(void)
{
  /* not implemented */
}

/* Timer/Counter1 Compare Match A */
void TIMER1_COMPA_vect(void)
{
  if (timer_manager[TIMER_1].unit_a_callback != NULL_PTR)
  {
    (*timer_manager[TIMER_1].unit_a_callback)();
  }
}

/* Timer/Counter1 Compare Match B */
void TIMER1_COMPB_vect(void)
{
  if (timer_manager[TIMER_1].unit_b_callback != NULL_PTR)
  {
    (*timer_manager[TIMER_1].unit_b_callback)();
  }
}

/* Timer/Counter1 Overflow */
void TIMER1_OVF_vect(void)
{
  timer_manager[TIMER_1].ticks++;
  if (timer_manager[TIMER_1].ovf_callback != NULL_PTR)
  {
    if (timer_manager[TIMER_1].ticks >= timer_manager[TIMER_1].overflow)
    {
      timer_manager[TIMER_1].ticks = 0;
      (*timer_manager[TIMER_1].ovf_callback)();
    }
  }
}

/**************************************************************************/
/*                               Timer 2                                  */
/**************************************************************************/
/* Timer/Counter2 Compare Match A */
void TIMER2_COMPA_vect(void)
{
  if (timer_manager[TIMER_2].unit_a_callback != NULL_PTR)
  {
    (*timer_manager[TIMER_2].unit_a_callback)();
  }
}

/* Timer/Counter2 Compare Match B */
void TIMER2_COMPB_vect(void)
{
  if (timer_manager[TIMER_2].unit_b_callback != NULL_PTR)
  {
    (*timer_manager[TIMER_2].unit_b_callback)();
  }
}

/* Timer/Counter2 Overflow */
void TIMER2_OVF_vect(void)
{
  timer_manager[TIMER_2].ticks++;
  if (timer_manager[TIMER_2].ovf_callback != NULL_PTR)
  {
    if (timer_manager[TIMER_2].ticks >= timer_manager[TIMER_2].overflow)
    {
      timer_manager[TIMER_2].ticks = 0;
      (*timer_manager[TIMER_2].ovf_callback)();
    }
  }
}

/**************************************************************************/
/*                               Timer 3                                  */
/**************************************************************************/
/* Timer/Counter3 Capture Event */
void TIMER3_CAPT_vect(void)
{
  /* not implemented */
}

/* Timer/Counter3 Compare Match A */
void TIMER3_COMPA_vect(void)
{
  if (timer_manager[TIMER_3].unit_a_callback != NULL_PTR)
  {
    (*timer_manager[TIMER_3].unit_a_callback)();
  }
}

/* Timer/Counter3 Compare Match B */
void TIMER3_COMPB_vect(void)
{
  if (timer_manager[TIMER_3].unit_b_callback != NULL_PTR)
  {
    (*timer_manager[TIMER_3].unit_b_callback)();
  }
}

/* Timer/Counter3 Overflow */
void TIMER3_OVF_vect(void)
{
  timer_manager[TIMER_3].ticks++;
  if (timer_manager[TIMER_3].ovf_callback != NULL_PTR)
  {
    if (timer_manager[TIMER_3].ticks >= timer_manager[TIMER_3].overflow)
    {
      timer_manager[TIMER_3].ticks = 0;
      (*timer_manager[TIMER_3].ovf_callback)();
    }
  }
}
