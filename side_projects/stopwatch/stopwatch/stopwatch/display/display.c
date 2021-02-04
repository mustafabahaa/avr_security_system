
#include "display.h"

void display_initialization()
{

  /* make enable pins of 7 segment as output */
  SEGMENT_ENABLE_DDR = 0x3F;
  SEGMENT_CONTROL_DDR = 0x0F;
}

void display_enable(u8_t pin, control_t control)
{
  if (control == OFF)
  {
    clr_bit(SEGMENT_ENABLE_PORT, pin);
  }
  else
  {
    set_bit(SEGMENT_ENABLE_PORT, pin);
  }
}

void display_write(u8_t number, u8_t digit)
{

  /*disable all digits before enabling the required*/
  for (int i = 0; i < TOTAL_DIGITS; i++)
  {
    display_enable(i, OFF);
  }

  /*enable corrsponding digit */
  display_enable(digit, ON);

  SEGMENT_CONTROL_PORT = number;
}