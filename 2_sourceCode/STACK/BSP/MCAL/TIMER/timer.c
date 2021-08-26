/** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** timer.c
 **************************************************************************
 **                              Includes                                **
 *************************************************************************/
#include "timer.h"
/**************************************************************************
 **                              Global Variable                         **
 *************************************************************************/
/* Global variables to hold the address of the call back function*/
static void (*g_callBackPtr)(void) = NULL_PTR;
volatile double g_ticks_timer_0 = 0;
volatile double g_ticks_timer_1 = 0;
volatile double g_ticks_timer_2 = 0;
double g_ovf_timer_0 = 0;
double g_ovf_timer_1 = 0;
double g_ovf_timer_2 = 0;
/*************************************************************************/
/*                     Static Functions Prototype                        */
/*************************************************************************/
static void set_timer_overflow(timer_number_t timer_number, double overflow);
/**************************************************************************
 ** getPreScaler()
 **
 ** parameter: timer_preScaler_t preScaller
 ** return    : u16_t
 ***************************************************************************
 ** this function is used to get the actual values of pre-scaller
 **************************************************************************/
static double getPreScaler(timer_preScaler_t preScaller);

/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

timer_error_t mcal_timer_init(timer_config_t *timer)
{
  timer_error_t error = TIMER_STATE_SUCCESS;

  setGlobalInterrupt;

  double preScallerValue = (double)getPreScaler(timer->preScaler);
  double resolution = (double)preScallerValue / (double)F_CPU;
  double registerMaxTime = 0;

  switch (timer->timer_number)
  {
  case TIMER0:
  {
    reg_mask_write(TCCR0, 0xF8, timer->preScaler);

    registerMaxTime = resolution * 256 * 1000;

    if (TIMER_NORMAL_MODE == timer->mode)
    {
      register(TCNT0) = 0;
      set_bit(TCCR0, FOC0);

      /* attach overflow value to timer so we can use it in callback */
      timer->overflow = timer->tick_ms_seconds / (double)registerMaxTime;
      set_timer_overflow(timer->timer_number, timer->overflow);
    }
    else if (TIMER_CTC_MODE == timer->mode)
    {
      register(TCNT0) = 0;
      set_bit(TCCR0, WGM01);
      clr_bit(TCCR0, WGM00);

      /* if the time we need to wait can be used with 8 bit timer in CTC mode
			 * meaning that if the value of seconds to wait converted to digital number
			 * less that 256 with the given pre-scaller */
      if (timer->tick_ms_seconds < (registerMaxTime))
      {
        // Set Compare Value
        register(OCR0) = (u8_t)(((timer->tick_ms_seconds / 1000) * F_CPU) / preScallerValue);
      }
      else
      {
        error = TIMER_STATE_INVALID_ARGUMENT;
      }
    }
    else
    {
      error = TIMER_STATE_INVALID_MODE;
    }
    break;
  }
  case TIMER1_CHANNEL_1:
  case TIMER1_CHANNEL_2:
  {
    reg_mask_write(TCCR1B, 0xF8, timer->preScaler);

    registerMaxTime = resolution * 65536 * 1000;

    if (TIMER_NORMAL_MODE == timer->mode)
    {
      // Set Timer initial value to 0
      register(TCNT1) = 0;
      set_bit(TCCR1A, FOC1A);
      set_bit(TCCR1A, FOC1B);

      /* attach overflow value to timer so we can use it in callback */
      timer->overflow = timer->tick_ms_seconds / registerMaxTime;
      set_timer_overflow(timer->timer_number, timer->overflow);
    }
    else if (TIMER_CTC_MODE == timer->mode)
    {
      // Set Timer initial value
      register(TCNT1) = 0;
      set_bit(TCCR1A, FOC1A);
      set_bit(TCCR1A, WGM12);

      /* if the time we need to wait can be used with 8 bit timer in CTC mode
			 * meaning that if the value of seconds to wait converted to digital number
			 * less that 256 with the given pre-scaller */
      if (timer->tick_ms_seconds < registerMaxTime)
      {
        // Set Compare Value
        register(OCR1A) = (u8_t)(((timer->tick_ms_seconds / 1000) * F_CPU) / preScallerValue);
      }
      else
      {
        error = TIMER_STATE_INVALID_ARGUMENT;
      }
    }
    else
    {
      error = TIMER_STATE_INVALID_MODE;
    }
    break;
  }
  case TIMER2:
  {
    reg_mask_write(TCCR2, 0xF8, timer->preScaler);

    registerMaxTime = resolution * 256 * 1000;

    if (TIMER_NORMAL_MODE == timer->mode)
    {
      // Set Timer initial value
      register(TCNT2) = 0;
      set_bit(TCCR2, FOC2);

      /* attach overflow value to timer so we can use it in callback */
      timer->overflow = timer->tick_ms_seconds / registerMaxTime;
      set_timer_overflow(timer->timer_number, timer->overflow);
    }
    else if (TIMER_CTC_MODE == timer->mode)
    {
      // Set Timer initial value
      register(TCNT2) = 0;
      set_bit(TCCR2, FOC2);
      set_bit(TCCR2, WGM21);

      /* if the time we need to wait can be used with 8 bit timer in CTC mode
			 * meaning that if the value of seconds to wait converted to digital number
			 * less that 256 with the given pre-scaller */
      if (timer->tick_ms_seconds < registerMaxTime)
      {
        // Set Compare Value
        register(OCR2) = (u8_t)(((timer->tick_ms_seconds / 1000) * F_CPU) / preScallerValue);
      }
      else
      {
        error = TIMER_STATE_INVALID_ARGUMENT;
      }
    }
    else
    {
      error = TIMER_STATE_INVALID_MODE;
    }
    break;
  }
  }
  return error;
}

timer_error_t mcal_timer_start(timer_config_t *timer)
{
  timer_error_t error = TIMER_STATE_SUCCESS;

  switch (timer->timer_number)
  {
  case TIMER0:
  {
    if (TIMER_NORMAL_MODE == timer->mode)
    {
      // Enable Timer0 Overflow Interrupt
      set_bit(TIMSK, TOIE0);
    }
    else if (TIMER_CTC_MODE == timer->mode)
    {
      // Enable Timer0 Compare Interrupt
      set_bit(TIMSK, OCIE0);
    }
    else
    {
      error = TIMER_STATE_INVALID_MODE;
    }
    break;
  }
  case TIMER1_CHANNEL_1:
  {
    if (TIMER_NORMAL_MODE == timer->mode)
    {
      // Enable Timer1 channel 1 Overflow Interrupt
      set_bit(TIMSK, TOIE1);
    }
    else if (TIMER_CTC_MODE == timer->mode)
    {
      // Enable Timer1 channel 1 Compare Interrupt
      set_bit(TIMSK, OCIE1A);
    }
    else
    {
      error = TIMER_STATE_INVALID_MODE;
    }
    break;
  }
  case TIMER1_CHANNEL_2:
  {
    if (TIMER_NORMAL_MODE == timer->mode)
    {
      // Enable Timer1 channel 2 Overflow Interrupt
      set_bit(TIMSK, TOIE2);
    }
    else if (TIMER_CTC_MODE == timer->mode)
    {
      // Enable Timer1 channel 2 Compare Interrupt
      set_bit(TIMSK, OCIE1B);
    }
    else
    {
      error = TIMER_STATE_INVALID_MODE;
    }
    break;
  }
  case TIMER2:
  {
    if (TIMER_NORMAL_MODE == timer->mode)
    {

      // Enable Timer2 Overflow Interrupt
      set_bit(TIMSK, TOIE2);
    }
    else if (TIMER_CTC_MODE == timer->mode)
    {
      // Enable Timer2 Compare Interrupt
      set_bit(TIMSK, OCIE2);
    }
    else
    {
      error = TIMER_STATE_INVALID_MODE;
    }
    break;
  }

  default:
  {
    error = TIMER_STATE_INVALID_TIMER;
    break;
  }
  }

  return error;
}

timer_error_t mcal_timer_stop(timer_config_t *timer)
{
  timer_error_t error = TIMER_STATE_SUCCESS;

  switch (timer->timer_number)
  {
  case TIMER0:
  {
    if (TIMER_NORMAL_MODE == timer->mode)
    {
      // Enable Timer0 Overflow Interrupt
      clr_bit(TIMSK, TOIE0);
    }
    else if (TIMER_CTC_MODE == timer->mode)
    {
      // Enable Timer0 Compare Interrupt
      clr_bit(TIMSK, OCIE0);
    }
    else
    {
      error = TIMER_STATE_INVALID_MODE;
    }
    break;
  }
  case TIMER1_CHANNEL_1:
  {
    if (TIMER_NORMAL_MODE == timer->mode)
    {
      // Enable Timer1 channel 1 Overflow Interrupt
      clr_bit(TIMSK, TOIE1);
    }
    else if (TIMER_CTC_MODE == timer->mode)
    {
      // Enable Timer1 channel 1 Compare Interrupt
      clr_bit(TIMSK, OCIE1A);
      register(TCNT0) = 0;
    }
    else
    {
      error = TIMER_STATE_INVALID_MODE;
    }
    break;
  }
  case TIMER1_CHANNEL_2:
  {
    if (TIMER_NORMAL_MODE == timer->mode)
    {
      // Enable Timer1 channel 2 Overflow Interrupt
      set_bit(TIMSK, TOIE2);
    }
    else if (TIMER_CTC_MODE == timer->mode)
    {
      // Enable Timer1 channel 2 Compare Interrupt
      set_bit(TIMSK, OCIE1B);
    }
    else
    {
      error = TIMER_STATE_INVALID_MODE;
    }
    break;
  }
  case TIMER2:
  {
    if (TIMER_NORMAL_MODE == timer->mode)
    {
      // Enable Timer2 Overflow Interrupt
      clr_bit(TIMSK, TOIE2);
    }
    else if (TIMER_CTC_MODE == timer->mode)
    {
      // Enable Timer2 Compare Interrupt
      clr_bit(TIMSK, OCIE2);
    }
    else
    {
      error = TIMER_STATE_INVALID_MODE;
    }
    break;
  }

  default:
  {
    error = TIMER_STATE_INVALID_TIMER;
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

void timer_setCallBack(void (*a_ptr)(void))
{
  g_callBackPtr = a_ptr;
}

/*************************************************************************/
/*                    Static Functions Implementation                    */
/*************************************************************************/

static void set_timer_overflow(timer_number_t timer_number, double overflow)
{
  switch (timer_number)
  {
  case TIMER0:
    g_ovf_timer_0 = overflow;
    break;

  case TIMER1_CHANNEL_1:
  case TIMER1_CHANNEL_2:

    g_ovf_timer_1 = overflow;
    break;

  case TIMER2:
    g_ovf_timer_2 = overflow;
    break;

  default:
    break;
  }
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
    if (g_ticks_timer_2 >= g_ovf_timer_2)
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
    if (g_ticks_timer_1 >= g_ovf_timer_1)
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
    if (g_ticks_timer_0 >= g_ovf_timer_0)
    {
      g_ticks_timer_0 = 0;
      (*g_callBackPtr)();
    }
  }
}
