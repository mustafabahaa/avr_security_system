#ifndef DISPLAY_H_
#define DISPLAY_H_
/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include <avr/io.h>
#include "atmega16.h"
#include "types.h"
/*************************************************************************/
/*                                 Macro                                 */
/*************************************************************************/
#define SEGMENT_ENABLE_DDR DDRA
#define SEGMENT_ENABLE_PORT PORTA
#define SEGMENT_CONTROL_DDR DDRC
#define SEGMENT_CONTROL_PORT PORTC

#define SECONDS_DIGIT_1 0
#define SECONDS_DIGIT_2 1

#define MINUTES_DIGIT_1 2
#define MINUTES_DIGIT_2 3

#define HOURS_DIGIT_1 4
#define HOURS_DIGIT_2 5

#define TOTAL_DIGITS 5
/*************************************************************************/
/*                                 Types                                 */
/*************************************************************************/
typedef enum
{
  OFF,
  ON
} control_t;
/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
** display_initialization()
**
** parameter: void
** return    : void
***************************************************************************
** this function is used to initialize all the necessary sequence for timer
**************************************************************************/
void display_initialization();

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
** display_enable()
**
** parameter: u8_t pin
** parameter: control_t control
** return    : void
***************************************************************************
** this function control the display digit on or off before writing
**************************************************************************/
void display_enable(u8_t pin, control_t control);

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
** display_write()
**
** parameter: u8_t number
** parameter: u8_t digit
** return    : void
***************************************************************************
** this function write a certain number to certain digit on display
**************************************************************************/
void display_write(u8_t number, u8_t digit);

#endif /* DISPLAY_H_ */