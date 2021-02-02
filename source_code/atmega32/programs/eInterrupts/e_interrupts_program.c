/*************************************************************************
** This  software  is  in  the  public  domain , furnished "as is", without
** technical support,  and with no  warranty, express or implied, as to its
** usefulness for any purpose.

** main.c
**************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "e_interrupts_program.h"
/*************************************************************************/
/*                   Static Functions Prototype                          */
/**************************************************************************
** systemInit()
**
** parameters: void
** return    : void
***************************************************************************
** this function is used to initialize all the necessary sequence for app
**************************************************************************/
static void systemInit();

/** init_led()
**
** parameters: void
** return    : void
***************************************************************************
** this function is used to initialize all the necessary sequence for led
**************************************************************************/
static void init_led();

/** init_interrupts()
**
** parameters: void
** return    : void
***************************************************************************
** this function is used to initialize the necessary sequence for interrupts
**************************************************************************/
static void init_interrupts();

/*************************************************************************/
/*                      Interrupts vector callbacks                      */
/*************************************************************************/
void __vector_1(void) __attribute__((signal, used, externally_visible));
void __vector_2(void) __attribute__((signal, used, externally_visible));
void __vector_3(void) __attribute__((signal, used, externally_visible));

/*************************************************************************/
/*                        Global Declerations                            */
/*************************************************************************/
led_t red_led;
led_t green_led;
led_t blue_led;

/*************************************************************************/
/*                             Application                               */
/*************************************************************************/
void execute_interrupt_program(void)
{
  systemInit();

  while (1)
  {
  }
}

/*************************************************************************/
/*                   Static Functions Implementations                    */
/*************************************************************************/
static void systemInit()
{
  init_interrupts();
  init_led();
}

static void init_led()
{
  green_led.base_addr = BASE_C;
  green_led.pin_num = 0;
  green_led.wiring = CURRENT_SOURCING;
  hal_led_init(&green_led);
  hal_led_set_state(&green_led, OFF);

  blue_led.base_addr = BASE_C;
  blue_led.pin_num = 1;
  blue_led.wiring = CURRENT_SOURCING;
  hal_led_init(&blue_led);
  hal_led_set_state(&blue_led, OFF);

  red_led.base_addr = BASE_C;
  red_led.pin_num = 2;
  red_led.wiring = CURRENT_SOURCING;
  hal_led_init(&red_led);
  hal_led_set_state(&red_led, OFF);
}

static void init_interrupts()
{
  mcal_interrupt_initialize(INT0, RISING_EDGE);
  mcal_interrupt_initialize(INT1, RISING_EDGE);
  mcal_interrupt_initialize(INT2, RISING_EDGE);
}

/*************************************************************************/
/*            External Interrupts ISR Implementations                    */
/*************************************************************************/

void __vector_1(void)
{
  hal_led_toggle_state(&green_led);
}

void __vector_2(void)
{
  hal_led_toggle_state(&blue_led);
}

void __vector_3(void)
{
  hal_led_toggle_state(&red_led);
}