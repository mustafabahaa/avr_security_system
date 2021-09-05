/***************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** timer.h
 **************************************************************************/
#ifndef _TIMER_H_
#define _TIMER_H_
/**************************************************************************/
/*                              Includes                                  */
/**************************************************************************/
#include "types.h"
#include "avr.h"
#include "gpio.h"
/**************************************************************************/
/*                         Registers                                      */
/**************************************************************************/
#define TIMSK0 0x59
#define TIMSK1 0x6F
#define TIMSK2 0x70
#define TIMSK3 0x71

#define TCCR0A 0x44
#define TCCR0B 0x45
#define TCNT0 0x46
#define OCR0A 0x47
#define OCR0B 0x48

#define TCCR1A 0x80
#define TCCR1B 0x81
#define TCCR1C 0x82
#define TCNT1L 0x84
#define TCNT1H 0x85
#define OCR1AL 0x88
#define OCR1AH 0x89
#define OCR1BL 0x8A
#define OCR1BH 0x8B

#define TCCR2A 0xB0
#define TCCR2B 0xB1
#define TCNT2 0xB2
#define OCR2A 0xB3
#define OCR2B 0xB4

#define TCCR3A 0x90
#define TCCR3B 0x91
#define TCCR3C 0x92
#define TCNT3L 0x94
#define TCNT3H 0x95
#define OCR3AL 0x98
#define OCR3AH 0x99
#define OCR3BL 0x9A
#define OCR3BH 0x9B

#define CSN0 0
#define CSN1 1
#define CSN2 2

#define WGMN0 0
#define WGMN1 1
#define WGMN2 3
#define WGMN3 4

#define COMNB0 4
#define COMNB1 5
#define COMNA0 6
#define COMNA1 7

#define TOIEN 0
#define OCIENA 1
#define OCIENB 2
/**************************************************************************/
/*                         Linker Attributes                              */
/**************************************************************************/

/**************************************************************************/
/*                               Timer 0                                  */
/**************************************************************************/
/* Timer/Counter0 Compare Match A */
void __vector_16(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter0 Compare Match B */
void __vector_17(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter0 Overflow */
void __vector_18(void) __attribute__((signal, used, externally_visible));

/**************************************************************************/
/*                               Timer 1                                  */
/**************************************************************************/
/* Timer/Counter1 Capture Event */
void __vector_12(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter1 Compare Match A */
void __vector_13(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter1 Compare Match B */
void __vector_14(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter1 Overflow */
void __vector_15(void) __attribute__((signal, used, externally_visible));

/**************************************************************************/
/*                               Timer 2                                  */
/**************************************************************************/
/* Timer/Counter2 Compare Match A */
void __vector_9(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter2 Compare Match B */
void __vector_10(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter2 Overflow */
void __vector_11(void) __attribute__((signal, used, externally_visible));

/**************************************************************************/
/*                               Timer 3                                  */
/**************************************************************************/
/* Timer/Counter3 Capture Event */
void __vector_31(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter3 Compare Match A */
void __vector_32(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter3 Compare Match B */
void __vector_33(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter3 Overflow */
void __vector_34(void) __attribute__((signal, used, externally_visible));

/**************************************************************************/
/*                              Macros                                    */
/**************************************************************************/
#define TIMER0_COMPA_vect __vector_16
#define TIMER0_COMPB_vect __vector_17
#define TIMER0_OVF_vect __vector_18

#define TIMER1_CAPT_vect __vector_12
#define TIMER1_COMPA_vect __vector_13
#define TIMER1_COMPB_vect __vector_14
#define TIMER1_OVF_vect __vector_15

#define TIMER2_COMPA_vect __vector_9
#define TIMER2_COMPB_vect __vector_10
#define TIMER2_OVF_vect __vector_11

#define TIMER3_CAPT_vect __vector_31
#define TIMER3_COMPA_vect __vector_32
#define TIMER3_COMPB_vect __vector_33
#define TIMER3_OVF_vect __vector_34

#define MAX_TIMERS__COUNT 4

#define PRE_SCALER_MASK 0xF8
#define TIMERS_MAX_COUNT 4
/**************************************************************************/
/*                               Types                                   */
/**************************************************************************/
typedef enum
{
  TIMER_STATE_SUCCESS = 1,
  TIMER_STATE_FAIL,
  TIMER_STATE_INVALID_TIMER,
  TIMER_STATE_INVALID_MODE,
  TIMER_STATE_INVALID_ARGUMENT,
  TIMER_PWM_STATE_INVALID_CHANNEL
} timer_error_t;

typedef enum
{
  TIMER_NORMAL_MODE = 1,
  TIMER_CTC_MODE,
  TIMER_PWM_MODE,
} timer_mode_t;

typedef enum
{
  TIMER_0 = 0,
  TIMER_1 = 1,
  TIMER_2 = 2,
  TIMER_3 = 3,
} timer_number_t;

typedef enum
{
  UNIT_A = 1,
  UNIT_B
} timer_unit_t;

typedef enum
{
  TIMER_BIT_8_MAX = 256,
  TIMER_BIT_16_MAX = 65536,
} timer_max_count_t;

typedef enum
{
  F_CPU_CLOCK = 1,
  F_CPU_8 = 2,
  F_CPU_64 = 3,
  F_CPU_256 = 4,
  F_CPU_1024 = 5
} timer_preScaler_t;

typedef enum
{
  PB3_PWM = PB3, // OC0A PB3 Timer/Counter 0 Output Compare Match A Output 8-BIT
  PB4_PWM = PB4, // OC0B PB4 Timer/Counter 0 Output Compare Match B Output 8-BIT
  PD5_PWM = PD5, // OC1A PD5 Timer/Counter1 Output Compare Match A Output 16-BIT
  PD4_PWM = PD4, // OC1B PD4 Timer/Counter1 Output Compare Match B Output 16-BIT
  PD7_PWM = PD7, // OC2A PD7 Timer/Counter2 Output Compare Match A Output 8-BIT
  PD6_PWM = PD6, // OC2B PD6 Timer/Counter2 Output Compare Match B Output 8-BIT
  PB6_PWM = PB6, // OC3A PB6 Timer/Counter 3 Output Compare Match A Output 16-BIT
  PB7_PWM = PB7, // OC3B PB7 Timer/Counter 3 Output Compare Match B Output 16-BIT
} pwm_channel_pin_t;

typedef enum
{
  PWM_PORT_B = BASE_B,
  PWM_PORT_D = BASE_D
} pwm_channel_port_t;

typedef struct
{
  pwm_channel_pin_t channel_pin;
  pwm_channel_port_t channel_port;
} timer_pwm_config_t;

typedef struct
{
  double tick_ms_seconds;
} timer_config_t;

typedef struct
{
  timer_preScaler_t preScaler;
  timer_number_t number;
  timer_unit_t unit;
  timer_mode_t mode;
  timer_pwm_config_t pwm_config;
  timer_config_t timer_config;
  void (*ovf_callback)(void);
  void (*unit_a_callback)(void);
  void (*unit_b_callback)(void);
} timer_t;

/**************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** mcal_timer_init()
 **
 ** parameter: timer_t* timer
 ** return    : timer_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for timer
 **************************************************************************/
timer_error_t mcal_timer_init(timer_t *timer);

/***************************************************************************
 ** mcal_timer_start()
 **
 ** parameter: timer_t* timer
 ** return    : timer_error_t
 ***************************************************************************
 ** this function is used to start given timer
 **************************************************************************/
timer_error_t mcal_timer_start(timer_t *timer);

/***************************************************************************
 ** mcal_timer_stop()
 **
 ** parameter: timer_t* timer
 ** return    : timer_error_t
 ***************************************************************************
 ** this function is used to start given timer
 **************************************************************************/
timer_error_t mcal_timer_stop(timer_t *timer);

/***************************************************************************
 ** mcal_timer_pwm_output()
 **
 ** parameter: timer_t* timer
 ** parameter: u16_t duty
 ** return    : timer_error_t
 ***************************************************************************
 ** this function is used to start given timer
 **************************************************************************/
timer_error_t mcal_timer_pwm_output(timer_t *timer, u16_t duty);

/***************************************************************************
 ** timer_setCallBack()
 **
 ** parameter: void(*callback)(void)
 ** return    : void
 ***************************************************************************
 ** this function is used to register timer interrupts callback
 **************************************************************************/
void timer_setCallBack(void (*callback)(void));

#endif /* _TIMER_H_ */
