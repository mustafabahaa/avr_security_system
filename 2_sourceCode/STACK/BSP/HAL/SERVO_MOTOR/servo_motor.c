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

  timer_pwm_config_t pwm_config;
  pwm_config.channel_pin = motor->pin;
  pwm_config.channel_port = motor->base;

  timer.mode = TIMER_PWM_MODE;
  timer.preScaler = F_CPU_CLOCK;
  timer.timer_number = TIMER2_UNIT_1;
  timer.config = &pwm_config;

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

    switch (timer.timer_number)
    {
    // PB3
    case TIMER0_UNIT_1:
    {
      timer_min_duty = (256 * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (256 * SERVO_MAX_PERIOD) / SERVO_PERIOD;
      break;
    }
    case TIMER0_UNIT_2:
    {
      timer_min_duty = (256 * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (256 * SERVO_MAX_PERIOD) / SERVO_PERIOD;
      break;
    }

    // PD4
    case TIMER1_UNIT_1:
    {
      timer_min_duty = (65536 * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (65536 * SERVO_MAX_PERIOD) / SERVO_PERIOD;
      break;
    }

    // PD5
    case TIMER1_UNIT_2:
    {
      timer_min_duty = (65536 * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (65536 * SERVO_MAX_PERIOD) / SERVO_PERIOD;
      break;
    }

    // PD7
    case TIMER2_UNIT_1:
    {
      timer_min_duty = (256 * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (256 * SERVO_MAX_PERIOD) / SERVO_PERIOD;
      break;
    }

    case TIMER2_UNIT_2:
    {
      timer_min_duty = (256 * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (256 * SERVO_MAX_PERIOD) / SERVO_PERIOD;
      break;
    }

      // PD4
    case TIMER3_UNIT_1:
    {
      timer_min_duty = (65536 * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (65536 * SERVO_MAX_PERIOD) / SERVO_PERIOD;
      break;
    }

    // PD5
    case TIMER3_UNIT_2:
    {
      timer_min_duty = (65536 * SERVO_MIN_PERIOD) / SERVO_PERIOD;
      timer_max_duty = (65536 * SERVO_MAX_PERIOD) / SERVO_PERIOD;
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
