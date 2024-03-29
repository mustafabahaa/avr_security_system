/***************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** servo_motor.h
 **************************************************************************/
#ifndef _SERVO_MOTOR_H_
#define _SERVO_MOTOR_H_
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "avr.h"
#include "types.h"
#include "gpio.h"
#include "timer.h"

/*************************************************************************/
/*                                 Macros                                */
/*************************************************************************/
/*servo specification from data sheet*/
#define SERVO_FREQUENCY  50
#define SERVO_PERIOD     0.02f
#define SERVO_MAX_PERIOD 0.0025f
#define SERVO_MIN_PERIOD 0.0005f
/*************************************************************************/
/*                                 Types                                 */
/*************************************************************************/
typedef enum
{
	SERVO_MOTOR_STATE_SUCCESS,
	SERVO_MOTOR_STATE_ERROR,
	SERVO_MOTOR_STATE_INVALID_DEGREE,
	SERVO_MOTOR_STATE_INVALID_MOTOR_PIN
} servo_motor_error_t;

typedef struct
{
	u8_t base;
  u8_t pin;
} servo_motor_t;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** hal_servo_motor_init()
 **
 ** parameter: motor_t *motor
 ** return    : servo_motor_error_t
 ***************************************************************************
 ** this function is used to initialize all  sequence for SERVO motor
 **************************************************************************/
servo_motor_error_t hal_servo_motor_init(servo_motor_t *motor);

/***************************************************************************
 ** hal_servo_motor_set_direction()
 **
 ** parameter: u8_t degree
 ** return    : servo_motor_error_t
 ***************************************************************************
 ** this function is used to change the direction of the motor
 **************************************************************************/
servo_motor_error_t hal_servo_motor_set_degree(servo_motor_t *motor ,u8_t degree);

#endif /* _SERVO_MOTOR_H_ */
