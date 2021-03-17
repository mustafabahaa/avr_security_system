/** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** timer.c
 **************************************************************************
 **                              Includes                                **
 *************************************************************************/
#include"timer.h"
/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

timer_error_t mcal_timer_init(timer_config_t* timer)
{
	timer_error_t error = TIMER_STATE_SUCCESS;
	setGlobalInterrupt;
	switch (timer->timer_number)
	{
	case TIMER0:
	{
		switch (timer->preScaler)
		{
		/* Prescaler F_CPU/1 */
		case PRESCALER_1:
		{
			set_bit(TCCR0, CS00);
			clr_bit(TCCR0, CS01);
			clr_bit(TCCR0, CS02);
			break;
		}
		/* Prescaler F_CPU/8 */
		case PRESCALER_8:
		{
			clr_bit(TCCR0, CS00);
			set_bit(TCCR0, CS01);
			clr_bit(TCCR0, CS02);
			break;
		}
		/* Prescaler F_CPU/64 */
		case PRESCALER_64:
		{
			set_bit(TCCR0, CS00);
			set_bit(TCCR0, CS01);
			clr_bit(TCCR0, CS02);
			break;
		}
		/* Prescaler F_CPU/256 */
		case PRESCALER_256:
		{
			clr_bit(TCCR0, CS00);
			clr_bit(TCCR0, CS01);
			set_bit(TCCR0, CS02);
			break;
		}
		/* Prescaler F_CPU/1024 */
		case PRESCALER_1024:
		{
			set_bit(TCCR0, CS00);
			clr_bit(TCCR0, CS01);
			set_bit(TCCR0, CS02);
			break;
		}
		}
		switch (timer->mode)
		{
		case TIMER_NORMAL_MODE:
		{
			 // Set Timer initial value
			register(TCNT0) = timer->inital_value;

			// Enable Timer0 Overflow Interrupt
			set_bit(TIMSK,TOIE0);

			/* configure the timer
			 * 1. Non PWM mode FOC0=1
			 * 2. Normal Mode WGM01=0 & WGM00=0
			 * 3. Normal Mode COM00=0 & COM01=0
			 */
			set_bit(TCCR0, FOC0);

			break;
		}
		case TIMER_CTC_MODE:
		{
			// Set Timer initial value
			register(TCNT0) = timer->inital_value;

			// Set Compare Value
			register(OCR0)  = timer->compare_value;

			// Enable Timer0 Compare Interrupt
			set_bit(TIMSK, OCIE0);

			/* Configure timer0 control register
			 * 1. Non PWM mode FOC0=1
			 * 2. CTC Mode WGM01=1 & WGM00=0
			 * 3. No need for OC0 so COM00=0 & COM01=0
			 */

			set_bit(TCCR0, FOC0);
			set_bit(TCCR0, WGM01);
			break;
		}
		}
		break;
	}
	case TIMER1:
	{
		switch(timer->preScaler)
		{
		/* Prescaler F_CPU/1 */
		case PRESCALER_1:
		{
			set_bit(TCCR1B, CS10);
			clr_bit(TCCR1B, CS11);
			clr_bit(TCCR1B, CS12);
			break;
		}
		/* Prescaler F_CPU/8 */
		case PRESCALER_8:
		{
			clr_bit(TCCR1B, CS10);
			set_bit(TCCR1B, CS11);
			clr_bit(TCCR1B, CS12);
			break;
		}
		/* Prescaler F_CPU/64 */
		case PRESCALER_64:
		{
			set_bit(TCCR1B, CS10);
			set_bit(TCCR1B, CS11);
			clr_bit(TCCR1B, CS12);
			break;
		}
		/* Prescaler F_CPU/256 */
		case PRESCALER_256:
		{
			clr_bit(TCCR1B, CS10);
			clr_bit(TCCR1B, CS11);
			set_bit(TCCR1B, CS12);
			break;
		}
		/* Prescaler F_CPU/1024 */
		case PRESCALER_1024:
		{
			set_bit(TCCR1B, CS10);
			clr_bit(TCCR1B, CS11);
			set_bit(TCCR1B, CS12);
			break;
		}
		}
		switch(timer->timer_channel)
		{
		case TIMER1_CHANNEL_A:
		{
			switch (timer->mode)
			{
			case TIMER_NORMAL_MODE:
			{
				// Set Timer initial value to 0
				register(TCNT1) = timer->inital_value;

				// Enable Timer1 Overflow Interrupt
				set_bit(TIMSK,TOIE1);

				/* configure the timer
				 *  Normal Mode WGM13=0 & WGM12=0 & WGM11=0 & WGM10=0
				 *  Normal Mode FOC1A=1 & FOC1B=1
				 *  Normal Mode COM1A1=0 & COM1A0=0
				 *  Normal Mode COM1B1=0 & COM1B0=0
				 */
				set_bit(TCCR1A, FOC1A);
				set_bit(TCCR1A, FOC1B);

				break;
			}
			case TIMER_CTC_MODE:
			{
				// Set Timer initial value
				register(TCNT1)= timer->inital_value;

				// Set Compare Value
				register(OCR1A)  = timer->compare_value;

				// Enable Timer1 Compare Interrupt
				set_bit(TIMSK, OCIE1A);

				/* Configure timer0 control register
				 * 1. Non PWM mode FOC0=1
				 * 2. CTC Mode WGM13=0 &WGM12=1 & WGM11=0 & WGM10=0
				 */
				set_bit(TCCR1A, FOC1A);
				set_bit(TCCR1A, WGM12);
				break;
			}
			}
			break;
		}
		case TIMER1_CHANNEL_B:
		{
			switch(timer->mode)
			{
			case TIMER_NORMAL_MODE:
			{
				 // Set Timer initial value to 0
				register(TCNT1) = timer->inital_value;

				// Enable Timer1 Overflow Interrupt
				set_bit(TIMSK,TOIE1);

				/* configure the timer
				 *  Normal Mode WGM13=0 & WGM12=0 & WGM11=0 & WGM10=0
				 *  Normal Mode FOC1A=1 & FOC1B=1
				 *  Normal Mode COM1A1=0 & COM1A0=0
				 *  Normal Mode COM1B1=0 & COM1B0=0
				 */
				set_bit(TCCR1A, FOC1A);
				set_bit(TCCR1B, FOC1B);

				break;
			}
			case TIMER_CTC_MODE:
			{
				// Set Timer initial value
				register(TCNT1)= timer->inital_value;

				// Set Compare Value
				register(OCR1B)  = timer->compare_value;

				// Enable Timer1 Compare Interrupt
				set_bit(TIMSK, OCIE1A);

				/* Configure timer0 control register
				 * 1. Non PWM mode FOC0=1
				 * 2. CTC Mode WGM13=0 &WGM12=1 & WGM11=0 & WGM10=0
				 */
				set_bit(TCCR1A, FOC1B);
				set_bit(TCCR1B, WGM12);
				break;
			}
			}
			break;
		}
		}
		break;
	}
	case TIMER2:
	{
		switch (timer->preScaler)
		{
		/* Prescaler F_CPU/1 */
		case PRESCALER_1:
		{
			set_bit(TCCR2, CS20);
			clr_bit(TCCR2, CS21);
			clr_bit(TCCR2, CS22);
			break;
		}
		/* Prescaler F_CPU/8 */
		case PRESCALER_8:
		{
			clr_bit(TCCR2, CS20);
			set_bit(TCCR2, CS21);
			clr_bit(TCCR2, CS22);
			break;
		}
		/* Prescaler F_CPU/64 */
		case PRESCALER_64:
		{
			set_bit(TCCR2, CS20);
			set_bit(TCCR2, CS21);
			clr_bit(TCCR2, CS22);
			break;
		}
		/* Prescaler F_CPU/256 */
		case PRESCALER_256:
		{
			clr_bit(TCCR2, CS20);
			clr_bit(TCCR2, CS21);
			set_bit(TCCR2, CS22);
			break;
		}
		/* Prescaler F_CPU/1024 */
		case PRESCALER_1024:
		{
			set_bit(TCCR2, CS20);
			clr_bit(TCCR2, CS21);
			set_bit(TCCR2, CS22);
			break;
		}
		}
		switch(timer->mode)
		{
		case TIMER_NORMAL_MODE:
		{
			// Set Timer initial value
			register(TCNT2) = timer->inital_value;

			// Enable Timer2 Overflow Interrupt
			set_bit(TIMSK,TOIE2);

			/* configure the timer
			 * 1. Non PWM mode FOC2=1
			 * 2. Normal Mode WGM21=0 & WGM20=0
			 * 3. Normal Mode COM20=0 & COM21=0
			 */
			set_bit(TCCR2, FOC2);
			break;
		}
		case TIMER_CTC_MODE:
		{
			// Set Timer initial value
			register(TCNT2) = timer->inital_value;

			// Set Compare Value
			register(OCR2)  = timer->compare_value;

			// Enable Timer2 Compare Interrupt
			set_bit(TIMSK, OCIE2);

			/* Configure timer0 control register
			 * 1. Non PWM mode FOC2=1
			 * 2. CTC Mode WGM21=1 & WGM20=0
			 * 3. No need for OC0 so COM20=0 & COM21=0
			 */
			set_bit(TCCR2, FOC2);
			set_bit(TCCR2, WGM21);
			break;
		}
		}
		break;
	}
	}
	return error;
}
