/*************************************************************************
** This  software  is  in  the  public  domain , furnished "as is", without
** technical support,  and with no  warranty, express or implied, as to its
** usefulness for any purpose.

** gpio_program.c
**************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "gpio_program.h"
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

/*************************************************************************/
/*                        Global Declerations                            */
/*************************************************************************/
led_t red_led;
button_t button_1;
/*************************************************************************/
/*                             Application                               */
/*************************************************************************/
void execute_gpio_program(void)
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
}

/*************************************************************************/
/*                   Static Functions Implementations                    */
/*************************************************************************/
static void systemInit()
{
  init_led();
  init_button();
}

static void init_led()
{
  red_led.base_addr = BASE_C;
  red_led.pin_num = 0;
  red_led.wiring = CURRENT_SOURCING;
  hal_led_init(&red_led);
  hal_led_set_state(&red_led, OFF);
}

static void init_button()
{
  button_1.base_addr = BASE_C;
  button_1.pin_num = 1;
  button_1.connection = PULLDOWN_CONNECTION;
  hal_button_init(&button_1);
}
