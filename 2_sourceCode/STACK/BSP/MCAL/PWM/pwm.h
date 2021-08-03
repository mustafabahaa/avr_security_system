/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** pwm.h
 **************************************************************************/
#ifndef _PWM_H_
#define _PWM_H_
/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "types.h"
#include "atmega16.h"
/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/

typedef enum
{
	CHANNEL_1_PIN = 3, // PB3,
	CHANNEL_2_PIN = 4, // PD4,
	CHANNEL_3_PIN = 5, // PD5,
	CHANNEL_4_PIN = 7, // PD7,
} pwm_channel_pin_t;

typedef enum
{
	CHANNEL_1_PORT = BASE_B,
	CHANNEL_2_PORT = BASE_D,
	CHANNEL_3_PORT = BASE_D,
	CHANNEL_4_PORT = BASE_D,
} pwm_channel_port_t;

typedef struct
{
	pwm_channel_pin_t channel_pin;
	pwm_channel_port_t channel_port;

} pwm_channel_t ;

typedef enum
{
	PWM_STATE_SUCCESS,
	PWM_STATE_ERROR,
	PWM_STATE_INVALID_CHANNEL
} pwm_error_t;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** PWM_1_initialization()
 **
 ** parameters: pwm_channel_t* channel
 ** return    : pwm_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for pwm
 **************************************************************************/
pwm_error_t  mcal_pwm_initialization(pwm_channel_t* channel);

/***************************************************************************
 ** mcal_pwm_output()
 **
 ** parameters: pwm_channel_t* channel
 ** parameters: u16_t duty
 ** return    : pwm_error_t
 ***************************************************************************
 ** this function is used to to output frequency to specific channel
 **************************************************************************/
pwm_error_t  mcal_pwm_output(pwm_channel_t* channel , u16_t duty);


#endif /* _PWM_H_ */
