
#include "timer.h"

void timer_initialization()
{

  /* enable global interrupts */
  SREG |= (1 << 7);

  /*init the counter register*/
  TCNT1 = 0;

  /*adjust compare match to 976 
    using prescaller 1024 resolution is 1024/1MHZ timer tick = 1024 Micro 
    then 1 seconds / 1024 Microsecond = 976
  */
  OCR1A = 976;

  /* enable timer 1 compare register interrupt */
  TIMSK |= (1 << OCIE1A);

  /*init configuration register to enable
  CTC Mode
  prescaller 1024
  */
  TCCR1A = (1 << FOC1A);
  TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);
}