/*************************************************************************
** This  software  is  in  the  public  domain , furnished "as is", without
** technical support,  and with no  warranty, express or implied, as to its
** usefulness for any purpose.

** main.c
**************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "standardtypes.h"
#include "app_init.h"
#include "led.h"
#include "button.h"
#include "interrupt.h"
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

/** init_button()
**
** parameters: void
** return    : void
***************************************************************************
** this function is used to initialize all the necessary sequence for button
**************************************************************************/
static void init_button();

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
button_t button_1;
/*************************************************************************/
/*                             Application                               */
/*************************************************************************/
int main(void)
{
  button_states_t button_states;
  systemInit();

  while (1)
  {
    hal_button_get_state(&button_1, &button_states);

    switch (button_states)
    {
    case BUTTON_PRESSED:
      hal_led_set_state(&red_led, ON);
      break;

    case BUTTON_NOT_PRESSED:
      hal_led_set_state(&red_led, OFF);
      break;

    default:
      /*Error Unkown button states */
      break;
    }
  }

  return 0;
}

/*************************************************************************/
/*                   Static Functions Implementations                    */
/*************************************************************************/
static void systemInit()
{
  init_led();
  init_button();
  init_interrupts();
}

static void init_led()
{
  red_led.base_addr = BASE_C;
  red_led.pin_num = 0;
  red_led.wiring = CURRENT_SOURCING;
  hal_led_init(&red_led);
}

static void init_button()
{
  button_1.base_addr = BASE_C;
  button_1.pin_num = 1;
  button_1.connection = PULLDOWN_CONNECTION;
  hal_button_init(&button_1);
}

static void init_interrupts()
{
  mcal_interrupt_initialize(INT0, RISING_EDGE);
}

/*************************************************************************/
/*            External Interrupts ISR Implementations                    */
/*************************************************************************/

/* INT0_vect */
void __vector_1(void)
{
  hal_led_set_state(&red_led, ON);
}
