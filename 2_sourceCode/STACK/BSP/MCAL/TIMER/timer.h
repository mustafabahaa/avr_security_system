/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** timer.h
 **************************************************************************/
#ifndef _TIMER_H_
#define _TIMER_H_
/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "types.h"
#include "atmega32.h"
/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/
typedef enum
{
	TIMER_STATE_SUCCESS=1,
	TIMER_STATE_FAIL,
	TIMER_STATE_INVALID_TIMER,
	TIMER_STATE_INVALID_MODE,
	TIMER_STATE_INVALID_ARGUMENT
}timer_error_t;

typedef enum
{
	TIMER_NORMAL_MODE=1,
	TIMER_CTC_MODE,
}timer_mode_t;

typedef enum
{
	TIMER0=1,
	TIMER1_CHANNEL_1,
	TIMER1_CHANNEL_2,
	TIMER2,
}timer_number_t;

typedef enum
{
	F_CPU_CLOCK=1,
	F_CPU_8=2,
	F_CPU_64=3,
	F_CPU_256=4,
	F_CPU_1024=5
}timer_preScaler_t;

typedef struct
{
	timer_preScaler_t preScaler;
	timer_number_t timer_number;
	timer_mode_t mode;
	double tick_ms_seconds;
	double overflow;      /*used for normal mode only*/
}timer_config_t;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** mcal_timer_init()
 **
 ** parameters: timer_config_t* timer
 ** return    : timer_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for timer
 **************************************************************************/
timer_error_t mcal_timer_init(timer_config_t* timer);

/**************************************************************************
 ** mcal_timer_start()
 **
 ** parameters: timer_config_t* timer
 ** return    : timer_error_t
 ***************************************************************************
 ** this function is used to start given timer
 **************************************************************************/
timer_error_t mcal_timer_start(timer_config_t* timer);

/**************************************************************************
 ** mcal_timer_stop()
 **
 ** parameters: timer_config_t* timer
 ** return    : timer_error_t
 ***************************************************************************
 ** this function is used to start given timer
 **************************************************************************/
timer_error_t mcal_timer_stop(timer_config_t* timer);

/**************************************************************************
 ** timer_setCallBack()
 **
 ** parameters: void(*a_ptr)(void)
 ** return    : void
 ***************************************************************************
 ** this function is used to register timer interrupts callback
 **************************************************************************/
void timer_setCallBack(void(*a_ptr)(void));

/**************************************************************************
 ** set_timer_overflow()
 **
 ** parameters: u16_t overflow
 ** return    : void
 ***************************************************************************
 ** this function is used to update overflow value in callback file
 **************************************************************************/
void set_timer_overflow(double overflow);


#endif /* _TIMER_H_ */
