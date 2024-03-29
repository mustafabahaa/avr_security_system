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
static timer_t timer;

/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

servo_motor_error_t hal_servo_motor_init(servo_motor_t *motor)
{
  servo_motor_error_t error = SERVO_MOTOR_STATE_SUCCESS;

  timer.mode = TIMER_PWM_MODE;
  timer.preScaler = F_CPU_CLOCK;
  timer.number = TIMER_2;
  timer.unit = UNIT_A;
  timer.pwm_config.channel_pin = motor->pin;
  timer.pwm_config.channel_port = motor->base;

  if (TIMER_STATE_SUCCESS == mcal_timer_init(&timer))
  {
    /*define TOP value to reset at to adjust the frequency
		  note that  Fpwm = Fcpu / (N * 256)  and f or optimal
		  operating  frequency  for  servo  is 50HZ means 20ms
		  time period hence from this  equation N must  be  at
		  least 64 to get  the  closest thing to 50hz which is
		  61Hz and that's by setting prescaller to 64 that why
		  we won't assign a Top value here
		 */

    switch (timer.number)
    {
    // PB3
    case TIMER_0:
    case TIMER_2:
    {
      timer_min_duty = (TIMER_BIT_8_MAX * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (TIMER_BIT_8_MAX * SERVO_MAX_PERIOD) / SERVO_PERIOD;
      break;
    }
    case TIMER_1:
    case TIMER_3:
    {
      timer_min_duty = (TIMER_BIT_16_MAX * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (TIMER_BIT_16_MAX * SERVO_MAX_PERIOD) / SERVO_PERIOD;
      break;
    }

    default:
    {
      error = SERVO_MOTOR_STATE_INVALID_MOTOR_PIN;
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

  if (degree >= 0 && degree <= 180)
  {
    if (TIMER_STATE_SUCCESS == mcal_timer_pwm_output(
                                   &timer,
                                   map(degree, 0, 180, timer_min_duty, timer_max_duty)))
    {
      /* do nothing */
    }
    else
    {
      error = SERVO_MOTOR_STATE_ERROR;
    }
  }
  else
  {
    error = SERVO_MOTOR_STATE_INVALID_DEGREE;
  }

  return error;
}

static u32_t map(u32_t x, u32_t in_min, u32_t in_max, u32_t out_min, u32_t out_max)
{
  return ((x * (out_max - out_min)) / (in_max - in_min)) + out_min;
}
