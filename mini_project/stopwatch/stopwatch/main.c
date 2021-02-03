
#include <avr/io.h>
#include <avr/interrupt.h>

#define SEGMENT_ENABLE_DDR DDRA
#define SEGMENT_ENABLE_PORT PORTA
#define SEGMENT_CONTROL_DDR DDRC
#define SEGMENT_CONTROL_PORT PORTC

#define set_bit(register, bit) (register |= (1 << bit))
#define tog_bit(register, bit) (register ^= (1 << bit))
#define clr_bit(register, bit) (register &= ~(1 << bit))

typedef enum
{
  OFF,
  ON
} control_t;

void system_init();
void init_7_segment();
void init_timer();
void control_7_segment_pin(unsigned char pin, control_t control);
void write_7_segment_pin(unsigned char number, unsigned char digit);

/* global variable contain the ticks count of the timer */
unsigned char g_tick = 0;

int main(void)
{
  system_init();

  while (1)
  {
  }
}

void system_init()
{
  init_7_segment();
  init_timer();
}

void init_timer()
{
  SREG |= (1 << 7); /* Enable global interrupts in MC */

  TCNT1 = 0; /* Set timer1 initial count to zero */

  /* using 1024 prescaller / tick takes 1024 Micro  
  then 1 second / 1024 micro = 976
  */
  OCR1A = 976;

  TIMSK |= (1 << OCIE1A); /* Enable Timer1 Compare A Interrupt */

  /* Configure timer control register TCCR1A
	 * 1. Disconnect OC1A and OC1B  COM1A1=0 COM1A0=0 COM1B0=0 COM1B1=0
	 * 2. FOC1A=1 FOC1B=0
	 * 3. CTC Mode WGM10=0 WGM11=0 (Mode Number 4)
	 */
  TCCR1A = (1 << FOC1A);

  /* Configure timer control register TCCR1B
	 * 1. CTC Mode WGM12=1 WGM13=0 (Mode Number 4)
	 * 2. Prescaler = F_CPU/1024 CS10=1 CS11=0 CS12=1
	 */
  TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);
}

void init_7_segment()
{

  /* make enable pins of 7 segment as output */
  SEGMENT_ENABLE_DDR = 0b00111111;

  SEGMENT_CONTROL_DDR = 0b00001111;
}

void control_7_segment_pin(unsigned char pin, control_t control)
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

void write_7_segment_pin(unsigned char number, unsigned char digit)
{
  /*enable corrsponding digit */
  control_7_segment_pin(digit, ON);

  SEGMENT_CONTROL_PORT = number;
}

ISR(TIMER1_COMPA_vect)
{
  g_tick++;
  write_7_segment_pin(g_tick, 0);

  if (g_tick == 10)
  {
    g_tick = 0;
    write_7_segment_pin(0, 0);
  };
}