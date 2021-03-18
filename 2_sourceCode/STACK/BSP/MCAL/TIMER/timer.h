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
#include "../../includes/types.h"
#include "../../includes/atmega16.h"
/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/
typedef enum
{
	TIMER_STATE_SUCCESS,
	TIMER_STATE_FAIL,
	TIMER_STATE_INVALID_TIMER,
	TIMER_STATE_INVALID_MODE,
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
	PRESCALER_1 = 1,
	PRESCALER_8 = 8,
	PRESCALER_64 = 64,
	PRESCALER_256 = 256,
	PRESCALER_1024 = 1024,
}timer_preScaler_t;

typedef struct
{
	timer_mode_t mode;
	timer_preScaler_t preScaler;
	u16_t inital_value;             /* initial value for timer */
	u16_t compare_value;            /* compare value for compare mode */
	double tick_seconds;
	u16_t overflows;
	timer1_channel_t timer_channel;
	timer_number_t timer_number;
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
 ** this function is used write a value to gpio pin
 **************************************************************************/
void timer_setCallBack(void(*a_ptr)(void));

/**************************************************************************
 ** set_timer_config()
 **
 ** parameters: timer_config_t* timer
 ** return    : void
 ***************************************************************************
 ** this function is used write a value to gpio pin
 **************************************************************************/
void set_timer_config(timer_config_t* timer);


#endif /* _TIMER_H_ */
