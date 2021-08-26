/***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "servo_motor.h"

/*************************************************************************/
/*                Static Functions Prototypes                            */
/*************************************************************************/

static u32_t map(u32_t x, u32_t in_min, u32_t in_max,
                 u32_t out_min, u32_t out_max);

static u16_t timer_min_duty = 0;
static u16_t timer_max_duty = 0;
/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

servo_motor_error_t hal_servo_motor_init(servo_motor_t *motor)
{
  servo_motor_error_t error = SERVO_MOTOR_STATE_SUCCESS;

  if (PWM_STATE_SUCCESS == mcal_pwm_initialization(&(motor->channel)))
  {
    /*define TOP value to reset at to adjust the frequency
		  note that  Fpwm = Fcpu / (N * 256)  and f or optimal
		  operating  frequency  for  servo  is 50HZ means 20ms
		  time period hence from this  equation N must  be  at
		  least 64 to get  the  closest thing to 50hz which is
		  61Hz and that's by setting prescaller to 64 that why
		  we won't assign a Top value here
		 */

    switch (motor->channel.channel_pin)
    {
    // PB3
    case CHANNEL_1_PIN:
    {
      timer_min_duty = (256 * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (256 * SERVO_MAX_PERIOD) / SERVO_PERIOD;
      break;
    }

    // PD4
    case CHANNEL_2_PIN:
    {
      timer_min_duty = (65536 * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (65536 * SERVO_MAX_PERIOD) / SERVO_PERIOD;
      break;
    }

    // PD5
    case CHANNEL_3_PIN:
    {
      timer_min_duty = (65536 * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (65536 * SERVO_MAX_PERIOD) / SERVO_PERIOD;
      break;
    }

    // PD7
    case CHANNEL_4_PIN:
    {
      timer_min_duty = (256 * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (256 * SERVO_MAX_PERIOD) / SERVO_PERIOD;
      break;
    }
    }

    return error;

    /* LOOGGER : Servo Motor Initialized */
  }
  else
  {
    error = SERVO_MOTOR_STATE_ERROR;
  }
  return error;
}

servo_motor_error_t hal_servo_motor_set_degree(servo_motor_t *motor, u8_t degree)
{
  servo_motor_error_t error = SERVO_MOTOR_STATE_SUCCESS;

  switch (motor->channel.channel_pin)
  {
  // PB3
  case CHANNEL_1_PIN:
  {
    register(OCR1A) = map(degree, 0, 180, timer_min_duty, timer_max_duty);
    break;
  }

  // PD4
  case CHANNEL_2_PIN:
  {
    register(OCR1B) = map(degree, 0, 180, timer_min_duty, timer_max_duty);
    break;
  }

  // PD5
  case CHANNEL_3_PIN:
  {
    register(OCR2) = map(degree, 0, 180, timer_min_duty, timer_max_duty);
    break;
  }

  // PD7
  case CHANNEL_4_PIN:
  {
    break;
  }
  }

  return error;
}

static u32_t map(u32_t x, u32_t in_min, u32_t in_max, u32_t out_min, u32_t out_max)
{
  return ((x * (out_max - out_min)) / (in_max - in_min)) + out_min;
}
