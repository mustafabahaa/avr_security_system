
#include "timer.h"

void timer_initialization()
{

  /* enable global interrupts */
  set_bit(SREG, 7);

  /*init the counter register*/
  TCNT1 = 0;

  /*adjust compare match to 976 
    using prescaller 1024 resolution is 1024/1MHZ timer tick = 1024 Micro 
    then 1 seconds / 1024 Microsecond = 976
  */
  OCR1A = 976;

  /* enable timer 1 compare register interrupt */
  set_bit(TIMSK, OCIE1A);

  /*init configuration register to enable
  CTC Mode
  prescaller 1024
  */
   set_bit(TCCR1A, FOC1A);
   set_bit(TCCR1B, WGM12);
   set_bit(TCCR1B, CS10);
   set_bit(TCCR1B, CS12);
}