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
	timer_mode_t mode;
	timer_preScaler_t preScaler;
	u16_t inital_value;             /* initial value for timer */
	u16_t compare_value;            /* compare value for compare mode */
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


#endif /* _TIMER_H_ */
