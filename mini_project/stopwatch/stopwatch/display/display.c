
#include "display.h"

void display_initialization()
{

  /* make enable pins of 7 segment as output */
  SEGMENT_ENABLE_DDR = 0b00111111;
  SEGMENT_CONTROL_DDR = 0b00001111;
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
  for (int i = 0; i < 5; i++)
  {
    display_enable(i, OFF);
  }

  /*enable corrsponding digit */
  display_enable(digit, ON);

  SEGMENT_CONTROL_PORT = number;
}