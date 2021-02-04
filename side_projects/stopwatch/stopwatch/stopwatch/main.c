/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "atmega16.h"
#include "types.h"
#include "display.h"
#include "timer.h"
#include "e_interrupt.h"
/*************************************************************************/
/*                   Static Functions Prototype                          */
/**************************************************************************
** systemInit()
**
** parameters: void
** return    : void
***************************************************************************
** this function is used to call all intialization functions
**************************************************************************/
static void system_init();

/** updateTime()
**
** parameters: void
** return    : void
***************************************************************************
** this function is used to update the time every timer tick
**************************************************************************/
static void updateTime();

/** updateDisplay()
**
** parameters: void
** return    : void
***************************************************************************
** this function is used to update 7 segment according to current time
**************************************************************************/
static void updateDisplay();
/*************************************************************************/
/*                            Global Variables                           */
/*************************************************************************/
volatile u8_t seconds = 0;
volatile u8_t minutes = 0;
volatile u8_t hours = 0;

/*************************************************************************/
/*                            Main Program                               */
/*************************************************************************/
int main(void)
{
  system_init();

  while (1)
  {
    updateTime();
    updateDisplay();
  }
}

/*************************************************************************/
/*                   Static Functions Implementations                    */
/*************************************************************************/

static void system_init()
{
  e_interrupt_initialization();
  timer_initialization();
  display_initialization();
}

static void updateTime()
{
  if (seconds == 60)
  {
    seconds = 0;
    minutes++;
  }

  if (minutes == 60)
  {
    minutes = 0;
    hours++;
  }

  if (hours == 24)
  {
    seconds = 0;
    minutes = 0;
    hours = 0;
  }
}

static void updateDisplay()
{
  if (seconds < 10)
  {
    display_write(seconds, SECONDS_DIGIT_1);
  }
  else
  {
    display_write(seconds % 10, SECONDS_DIGIT_1);
    display_write((seconds / 10) % 10, SECONDS_DIGIT_2);
  }
  if (minutes < 10)
  {
    display_write(minutes, MINUTES_DIGIT_1);
  }
  else
  {
    display_write(minutes % 10, MINUTES_DIGIT_1);
    display_write((minutes / 10) % 10, MINUTES_DIGIT_2);
  }
  if (hours < 10)
  {
    display_write(hours, HOURS_DIGIT_1);
  }
  else
  {
    display_write(hours % 10, HOURS_DIGIT_1);
    display_write((hours / 10) % 10, HOURS_DIGIT_2);
  }
}

/*************************************************************************/
/*                            Interrupt Handlers                         */
/*************************************************************************/

/*Time monitor */
ISR(TIMER1_COMPA_vect)
{
  seconds++;
}

/*Reset stopwatch*/
ISR(INT0_vect)
{
  seconds = 0;
  minutes = 0;
  hours = 0;
}

/*Pause stopwatch*/
ISR(INT1_vect)
{
  /* Disable timer 1 compare register interrupt */
  clr_bit(TIMSK, OCIE1A);
}

/*resume stopwatch*/
ISR(INT2_vect)
{
  /* Disable timer 1 compare register interrupt */
  set_bit(TIMSK, OCIE1A);
}