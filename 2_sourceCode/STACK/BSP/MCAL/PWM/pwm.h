/***************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** pwm.h
 **************************************************************************/
#ifndef _PWM_H_
#define _PWM_H_
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "types.h"
#include "avr.h"
#include "gpio.h"
#include "timer.h"
#include "logger.h"
/**************************************************************************/
/*                               Types                                    */
/**************************************************************************/

typedef enum
{
  CHANNEL_1_PIN = PB3, // OC0A PB3 Timer/Counter 0 Output Compare Match A Output 8-BIT
  CHANNEL_2_PIN = PB4, // OC0B PB4 Timer/Counter 0 Output Compare Match B Output 8-BIT
  CHANNEL_3_PIN = PD5, // OC1A PD5 Timer/Counter1 Output Compare Match A Output 16-BIT
  CHANNEL_4_PIN = PD4, // OC1B PD4 Timer/Counter1 Output Compare Match B Output 16-BIT
  CHANNEL_5_PIN = PD7, // OC2A PD7 Timer/Counter2 Output Compare Match A Output 8-BIT
  CHANNEL_6_PIN = PD6, // OC2B PD6 Timer/Counter2 Output Compare Match B Output 8-BIT
  CHANNEL_7_PIN = PB6, // OC3A PB6 Timer/Counter 3 Output Compare Match A Output 16-BIT
  CHANNEL_8_PIN = PB7, // OC3B PB7 Timer/Counter 3 Output Compare Match B Output 16-BIT

} pwm_channel_pin_t;

typedef enum
{
  CHANNEL_1_PORT = BASE_B,
  CHANNEL_2_PORT = BASE_B,
  CHANNEL_3_PORT = BASE_D,
  CHANNEL_4_PORT = BASE_D,
  CHANNEL_5_PORT = BASE_D,
  CHANNEL_6_PORT = BASE_D,
  CHANNEL_7_PORT = BASE_B,
  CHANNEL_8_PORT = BASE_B,

} pwm_channel_port_t;

typedef struct
{
  pwm_channel_pin_t channel_pin;
  pwm_channel_port_t channel_port;
  timer_number_t timer_number;

} pwm_channel_t;

typedef enum
{
  PWM_STATE_SUCCESS = 1,
  PWM_STATE_ERROR,
  PWM_STATE_INVALID_CHANNEL
} pwm_error_t;

/**************************************************************************/
/*                           Public Functions                             */
/***************************************************************************
 ** PWM_1_initialization()
 **
 ** parameter: pwm_channel_t* channel
 ** return    : pwm_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for pwm
 **************************************************************************/
pwm_error_t mcal_pwm_initialization(pwm_channel_t *channel);

/***************************************************************************
 ** mcal_pwm_output()
 **
 ** parameter: pwm_channel_t* channel
 ** parameter: u16_t duty
 ** return    : pwm_error_t
 ***************************************************************************
 ** this function is used to to output frequency to specific channel
 **************************************************************************/
pwm_error_t mcal_pwm_output(pwm_channel_t *channel, u16_t duty);

#endif /* _PWM_H_ */
