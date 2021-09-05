/***************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** dc_motor.h
 **************************************************************************/
#ifndef _DC_MOTOR_H_
#define _DC_MOTOR_H_
#if 0
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "avr.h"
#include "types.h"
#include "gpio.h"
/*************************************************************************/
/*                                 Types                                 */
/*************************************************************************/
typedef enum
{
	MOTOR_STATE_SUCCESS,
	MOTOR_STATE_ERROR,
	MOTOR_STATE_INVALID_DIRECTION,
	MOTOR_STATE_INVALID_SPEED,
	MOTOR_STATE_INVALID_MOTOR_PIN
} motor_error_t;

typedef struct
{
	u8_t dir_1_port;
	u8_t dir_2_port;
	u8_t dir_1_pin;
	u8_t dir_2_pin;
} motor_direction_pins_t;

typedef enum
{
	RIGHT,
	LEFT
} motor_direction_t;

typedef enum
{
	STOP = 0 ,
	HALF_SPEED = 128,
	FULL_SPEED = 255,
} motor_speed_t;

typedef struct
{
	pwm_channel_t* channel;
	motor_direction_pins_t* direction;
} motor_t;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** hal_dc_motor_init()
 **
 ** parameter: motor_t *motor
 ** return    : motor_error_t
 ***************************************************************************
 ** this function is used to initialize all  sequence for DC motor
 **************************************************************************/
motor_error_t hal_dc_motor_init(motor_t *motor);

/**************************************************************************
 ** hal_dc_motor_set_direction()
 **
 ** parameter: motor_t *motor
 ** parameter: motor_direction_t direction
 **
 ** return    : motor_error_t
 ***************************************************************************
 ** this function is used to change the direction of the motor
 **************************************************************************/
motor_error_t hal_dc_motor_set_direction(motor_t *motor ,motor_direction_t direction);

/**************************************************************************
 ** hal_dc_motor_set_speed()
 **
 ** parameter: motor_t *motor
 ** parameter: motor_speed_t speed
 **
 ** return    : motor_error_t
 ***************************************************************************
 ** this function is used to change the speed of the motor
 **************************************************************************/
motor_error_t hal_dc_motor_set_speed(motor_t *motor ,motor_speed_t speed);
#endif
#endif /* _DC_MOTOR_H_ */
