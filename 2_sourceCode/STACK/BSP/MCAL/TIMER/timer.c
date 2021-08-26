/** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** timer.c
 **************************************************************************
 **                              Includes                                **
 *************************************************************************/
#include"timer.h"
/*************************************************************************/
/*                     Static Functions Prototype                        */
/*************************************************************************/

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

timer_error_t mcal_timer_init(timer_config_t* timer)
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
		reg_mask_write(TCCR0,0xF8,timer->preScaler);

		registerMaxTime = resolution * (double)256;

		if (TIMER_NORMAL_MODE == timer->mode)
		{
			// Set Timer initial value
			register(TCNT0) = 0;

			/* configure the timer
			 * 1. Non PWM mode FOC0=1
			 * 2. Normal Mode WGM01=0 & WGM00=0
			 * 3. Normal Mode COM00=0 & COM01=0
			 */
			set_bit(TCCR0, FOC0);

			/* attach overflow value to timer so we can use it in callback */
			timer->overflow = timer->tick_ms_seconds / (double)registerMaxTime;
			set_timer_overflow(timer->overflow);

		}
		else if ( TIMER_CTC_MODE == timer->mode)
		{
			// Set Timer initial value
			register(TCNT0) = 0;

			/* Configure timer0 control register
			 * 1. Non PWM mode FOC0=1
			 * 2. CTC Mode WGM01=1 & WGM00=0
			 * 3. No need for OC0 so COM00=0 & COM01=0
			 */

			//set_bit(TCCR0, FOC0);
			set_bit(TCCR0, WGM01);
			clr_bit(TCCR0, WGM00);

			/* if the time we need to wait can be used with 8 bit timer in CTC mode
			 * meaning that if the value of seconds to wait converted to digital number
			 * less that 256 with the given pre-scaller */
			if (timer->tick_ms_seconds < (registerMaxTime * 1000))
			{
				// Set Compare Value
				register(OCR0) = (u8_t)(((timer->tick_ms_seconds /1000) * F_CPU) / timer->preScaler);
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
		reg_mask_write(TCCR1B,0xF8,timer->preScaler);

		registerMaxTime = resolution * (double)65536;

		if (TIMER_NORMAL_MODE == timer->mode)
		{
			// Set Timer initial value to 0
			register(TCNT1) = 0;

			/* configure the timer
			 *  Normal Mode WGM13=0 & WGM12=0 & WGM11=0 & WGM10=0
			 *  Normal Mode FOC1A=1 & FOC1B=1
			 *  Normal Mode COM1A1=0 & COM1A0=0
			 *  Normal Mode COM1B1=0 & COM1B0=0
			 */
			set_bit(TCCR1A, FOC1A);
			set_bit(TCCR1A, FOC1B);

			/* attach overflow value to timer so we can use it in callback */
			timer->overflow = timer->tick_ms_seconds / registerMaxTime;
			set_timer_overflow(timer->overflow);
		}
		else if ( TIMER_CTC_MODE == timer->mode)
		{
			// Set Timer initial value
			register(TCNT1)= 0;

			/* Configure timer0 control register
			 * 1. Non PWM mode FOC0=1
			 * 2. CTC Mode WGM13=0 &WGM12=1 & WGM11=0 & WGM10=0
			 */
			set_bit(TCCR1A, FOC1A);
			set_bit(TCCR1A, WGM12);

			/* if the time we need to wait can be used with 8 bit timer in CTC mode
			 * meaning that if the value of seconds to wait converted to digital number
			 * less that 256 with the given pre-scaller */
			if (timer->tick_ms_seconds < registerMaxTime)
			{
				// Set Compare Value
				register(OCR1A) = ((double)timer->tick_ms_seconds * (double)F_CPU) / (double)preScallerValue;
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
		reg_mask_write(TCCR2,0xF8,timer->preScaler);

		registerMaxTime = resolution * (double)256;

		if(TIMER_NORMAL_MODE == timer->mode)
		{
			// Set Timer initial value
			register(TCNT2) = 0;

			/* configure the timer
			 * 1. Non PWM mode FOC2=1
			 * 2. Normal Mode WGM21=0 & WGM20=0
			 * 3. Normal Mode COM20=0 & COM21=0
			 */
			set_bit(TCCR2, FOC2);

			/* attach overflow value to timer so we can use it in callback */
			timer->overflow = timer->tick_ms_seconds / registerMaxTime;
			set_timer_overflow(timer->overflow);

		}
		else if ( TIMER_CTC_MODE == timer->mode)
		{
			// Set Timer initial value
			register(TCNT2) = 0;

			/* Configure timer0 control register
			 * 1. Non PWM mode FOC2=1
			 * 2. CTC Mode WGM21=1 & WGM20=0
			 * 3. No need for OC0 so COM20=0 & COM21=0
			 */
			set_bit(TCCR2, FOC2);
			set_bit(TCCR2, WGM21);

			/* if the time we need to wait can be used with 8 bit timer in CTC mode
			 * meaning that if the value of seconds to wait converted to digital number
			 * less that 256 with the given pre-scaller */
			if (timer->tick_ms_seconds < registerMaxTime)
			{
				// Set Compare Value
				register(OCR2) = ((double)timer->tick_ms_seconds * (double)F_CPU) / (double)preScallerValue;
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


timer_error_t mcal_timer_start(timer_config_t* timer)
{
	timer_error_t error = TIMER_STATE_SUCCESS;

	switch (timer->timer_number)
	{
	case TIMER0:
	{
		if (TIMER_NORMAL_MODE ==  timer->mode)
		{
			// Enable Timer0 Overflow Interrupt
			set_bit(TIMSK,TOIE0);
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
		if (TIMER_NORMAL_MODE ==  timer->mode)
		{
			// Enable Timer1 channel 1 Overflow Interrupt
			set_bit(TIMSK,TOIE1);
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
		if (TIMER_NORMAL_MODE ==  timer->mode)
		{
			// Enable Timer1 channel 2 Overflow Interrupt
			set_bit(TIMSK,TOIE2);
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
		if (TIMER_NORMAL_MODE ==  timer->mode)
		{

			// Enable Timer2 Overflow Interrupt
			set_bit(TIMSK,TOIE2);
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

	default :
	{
		error = TIMER_STATE_INVALID_TIMER;
		break;
	}
	}

	return error;
}

timer_error_t mcal_timer_stop(timer_config_t* timer)
{
	timer_error_t error = TIMER_STATE_SUCCESS;

	switch (timer->timer_number)
	{
	case TIMER0:
	{
		if (TIMER_NORMAL_MODE ==  timer->mode)
		{
			// Enable Timer0 Overflow Interrupt
			clr_bit(TIMSK,TOIE0);
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
		if (TIMER_NORMAL_MODE ==  timer->mode)
		{
			// Enable Timer1 channel 1 Overflow Interrupt
			clr_bit(TIMSK,TOIE1);
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
		if (TIMER_NORMAL_MODE ==  timer->mode)
		{
			// Enable Timer1 channel 2 Overflow Interrupt
			set_bit(TIMSK,TOIE2);
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
		if (TIMER_NORMAL_MODE ==  timer->mode)
		{
			// Enable Timer2 Overflow Interrupt
			clr_bit(TIMSK,TOIE2);
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

	default :
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
	switch(preScaller)
	{
	case F_CPU_CLOCK :
	{
		value = 1;
		break;
	}
	case F_CPU_8 :
	{
		value = 8;
		break;
	}
	case F_CPU_64 :
	{
		value = 64;
		break;
	}
	case F_CPU_256 :
	{
		value = 256;
		break;
	}
	case F_CPU_1024 :
	{
		value = 1024;
		break;
	}
	default:
	{
		value = 0 ;
	}
	}

	return value;
}
