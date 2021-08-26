/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** delays.h
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "delay.h"

/***************************************************************************
 **                     Static Functions Prototype                        **
 ***************************************************************************
 ** delay_loop()
 **
 ** parameter: u16_t __count
 ** return    : void
 **************************************************************************
 ** this function is used to halt processor in loop
 *************************************************************************/
static void delay_loop(u16_t __count);

/**************************************************************************/
/*                     Functions Implementation                           */
/**************************************************************************/
void delay_ms(double __ms)
{
	u16_t __ticks;
	double __tmp = ((F_CPU) / 4e3) * __ms;
	if (__tmp < 1.0)
		__ticks = 1;
	else if (__tmp > 65535)
	{
		//	__ticks = requested delay in 1/10 ms
		__ticks = (u16_t) (__ms * 10.0);
		while(__ticks)
		{
			// wait 1/10 ms
			delay_loop(((F_CPU) / 4e3) / 10);
			__ticks --;
		}
		return;
	}
	else
		__ticks = (u16_t)__tmp;
	delay_loop(__ticks);
}

/**************************************************************************/
/*                     Static Functions Implementation                    */
/**************************************************************************/
static void delay_loop(u16_t __count)
{
	__asm__ volatile (
		"1: sbiw %0,1" "\n\t"
		"brne 1b"
		: "=w" (__count)
		: "0" (__count)
	);
}


