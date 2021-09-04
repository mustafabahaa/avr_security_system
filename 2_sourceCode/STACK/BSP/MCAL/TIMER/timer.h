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
#define TOIE0 0
#define OCIE0A 1
#define OCIE0B 2

#define TIMSK1 0x6F
#define TOIE1 0
#define OCIE1B 2
#define OCIE1A 1
#define ICIE1 5

#define TIMSK2 0x70
#define TOIE2 0
#define OCIE2A 1
#define OCIE2B 2

#define TIMSK3 0x71
#define TOIE3 0
#define OCIE3A 1
#define OCIE3B 2
#define ICIE3 5

#define TCCR0A 0x44
#define WGM00 0
#define WGM01 1
#define COM0B0 4
#define COM0B1 5
#define COM0A0 6
#define COM0A1 7

#define TCCR0B 0x45
#define CS00 0
#define CS01 1
#define CS02 2
#define WGM02 3
#define FOC0B 6
#define FOC0A 7

#define TCNT0 0x46
#define OCR0A 0x47
#define OCR0B 0x48

#define TCCR1A 0x80
#define WGM10 0
#define WGM11 1
#define COM1B0 4
#define COM1B1 5
#define COM1A0 6
#define COM1A1 7

#define TCCR1B 0x81
#define CS10 0
#define CS11 1
#define CS12 2
#define WGM12 3
#define WGM13 4
#define ICES1 6
#define ICNC1 7

#define TCNT1 0x84
#define TCNT1L 0x84
#define TCNT1H 0x85
#define ICR1 0x86
#define ICR1L 0x86
#define ICR1H 0x87
#define OCR1A 0x88
#define OCR1AL 0x88
#define OCR1AH 0x89
#define OCR1B 0x8A
#define OCR1BL 0x8A
#define OCR1BH 0x8B

#define TCCR1C 0x82
#define FOC1B 6
#define FOC1A 7

#define TCCR3A 0x90
#define WGM30 0
#define WGM31 1
#define COM3B0 4
#define COM3B1 5
#define COM3A0 6
#define COM3A1 7

#define TCCR3B 0x91
#define CS30 0
#define CS31 1
#define CS32 2
#define WGM32 3
#define WGM33 4
#define ICES3 6
#define ICNC3 7

#define TCCR3C 0x92
#define FOC3B 6
#define FOC3A 7

/* Combine TCNT3L and TCNT3H */
#define TCNT3 0x94

#define TCNT3L 0x94
#define TCNT3H 0x95

/* Combine ICR3L and ICR3H */
#define ICR3 0x96

#define ICR3L 0x96
#define ICR3H 0x97

/* Combine OCR3AL and OCR3AH */
#define OCR3A 0x98

#define OCR3AL 0x98
#define OCR3AH 0x99

/* Combine OCR3BL and OCR3BH */
#define OCR3B 0x9A

#define OCR3BL 0x9A
#define OCR3BH 0x9B

#define TCCR2A 0xB0
#define WGM20 0
#define WGM21 1
#define COM2B0 4
#define COM2B1 5
#define COM2A0 6
#define COM2A1 7

#define TCCR2B 0xB1
#define CS20 0
#define CS21 1
#define CS22 2
#define WGM22 3
#define FOC2B 6
#define FOC2A 7

#define TCNT2 0xB2

#define OCR2A 0xB3

#define OCR2B 0xB4

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
/* Timer/Counter2 Compare Match */
void __vector_4(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter2 Overflow */
void __vector_5(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter1 Capture Event */
void __vector_6(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter1 Compare Match A */
void __vector_7(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter1 Compare Match B */
void __vector_8(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter1 Overflow */
void __vector_9(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter0 Compare Match */
void __vector_10(void) __attribute__((signal, used, externally_visible));

/* Timer/Counter0 Overflow */
void __vector_11(void) __attribute__((signal, used, externally_visible));
/**************************************************************************/
/*                              Macros                                    */
/**************************************************************************/
#define TIMER2_COMP_vect __vector_4
#define TIMER2_OVF_vect __vector_5
#define TIMER1_CAPT_vect __vector_6
#define TIMER1_COMPA_vect __vector_7
#define TIMER1_COMPB_vect __vector_8
#define TIMER1_OVF_vect __vector_9
#define TIMER0_COMP_vect __vector_10
#define TIMER0_OVF_vect __vector_11

#define MAX_TIMERS__COUNT 4

#define PRE_SCALER_MASK 0xF8
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
  TIMER_1 = 0,
  TIMER_2 = 1,
  TIMER_3 = 1,
} timer_number_t;

typedef enum
{
  UNIT_A = 1,
  UNIT_B
} timer_unit_t;

typedef enum
{
  TIMER_BIT_8 = 1,
  TIMER_BIT_16 = 2,
} timer_type_t;

typedef enum
{
  TIMER_BIT_8_MAX = 256,
  TIMER_BIT_16_MAX = 65536,
} timer_max_count_t;

typedef struct
{
  u8_t ctrl_reg_0;
  u8_t ctrl_reg_1;
  u8_t int_reg_0;
  u8_t cmp_reg_A;
  u8_t cmp_reg_B;
  u8_t counter;
} timer_8_bit_ctrl_regs;

typedef struct
{
  u8_t ctrl_reg_0;
  u8_t ctrl_reg_1;
  u8_t ctrl_reg_2;
  u8_t int_reg_0;
  u8_t cmp_reg_A_L;
  u8_t cmp_reg_A_H;
  u8_t cmp_reg_B_L;
  u8_t cmp_reg_B_H;
  u8_t counter_L;
  u8_t counter_H;
} timer_16_bit_ctrl_regs;

typedef struct
{
  timer_type_t type;
  timer_number_t number;
  void *ctr_regs_config;
  double ticks;
  double overflow;
  void (*a_ptr)(void);
} timer_module_t;

typedef struct
{
  timer_module_t *timers[MAX_TIMERS__COUNT];
} timer_device_t;

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
  timer_number_t timer_number;
  timer_type_t type;
  timer_unit_t unit;
  timer_mode_t mode;
  void *config;
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
 ** parameter: void(*a_ptr)(void)
 ** return    : void
 ***************************************************************************
 ** this function is used to register timer interrupts callback
 **************************************************************************/
void timer_setCallBack(void (*a_ptr)(void));

#endif /* _TIMER_H_ */
