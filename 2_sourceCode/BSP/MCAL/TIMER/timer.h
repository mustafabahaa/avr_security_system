/*
 * timer.h
 *
 *  Created on: Mar 15, 2021
 *      Author: Lenovo
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include "../../includes/types.h"
#include "../../includes/atmega16.h"

typedef enum
{
	TIMER_STATE_SUCCESS,
	TIMER_STATE_FAIL,
}timer_error_t;

typedef enum
{
	TIMER1_CHANNEL_A,
	TIMER1_CHANNEL_B,
}timer1_channel_t;

typedef enum
{
	TIMER_NORMAL_MODE,
	TIMER_CTC_MODE,
}timer_mode_t;

typedef enum
{
	TIMER0,
	TIMER1,
	TIMER2,
}timer_number_t;

typedef enum
{
	PRESCALER_1,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024,
}timer_preScaler_t;

typedef struct
{
	timer_preScaler_t preScaler;
	timer_mode_t mode;
	u16_t inital_value; /* initial value for timer */
	u16_t compare_value; /* compare value for compare mode */
	timer1_channel_t timer1_A_B;
	timer_number_t timer_number;
}timer_config_t;


timer_error_t mcal_timer_init(timer_config_t* timer);




#endif /* _TIMER_H_ */
