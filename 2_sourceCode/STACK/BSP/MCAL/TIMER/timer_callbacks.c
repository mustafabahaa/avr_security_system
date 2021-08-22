/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** timer_callbacks.c
 **************************************************************************
 **                              Includes                                **
 *************************************************************************/
#include"timer.h"
/**************************************************************************
 **                              Global Variable                         **
 *************************************************************************/
/* Global variables to hold the address of the call back function*/
static void (*g_callBackPtr)(void) = NULL_PTR;
volatile double ticks = 0;
double interruptOverflow = 0;
/*************************************************************************/
/*                         Linker Attributes                             */
/*************************************************************************/
void __vector_4(void) __attribute__((signal, used, externally_visible));
void __vector_5(void) __attribute__((signal, used, externally_visible));
void __vector_6(void) __attribute__((signal, used, externally_visible));
void __vector_7(void) __attribute__((signal, used, externally_visible));
void __vector_8(void) __attribute__((signal, used, externally_visible));
void __vector_9(void) __attribute__((signal, used, externally_visible));
void __vector_10(void) __attribute__((signal, used, externally_visible));
void __vector_11(void) __attribute__((signal, used, externally_visible));
/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/
void timer_setCallBack( void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}

void set_timer_overflow(double overflow) {
	interruptOverflow = overflow;
}
/*************************************************************************/
/*                     Interrupts Implementation                         */
/*************************************************************************/

/* TIMER2_COMP_vect */
void __vector_4(void)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* TIMER2_OVF_vect */
void __vector_5(void)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* TIMER1_CAPT_vect */
void __vector_6(void)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* TIMER1_COMPA_vect */
void __vector_7(void)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* TIMER1_COMPB_vect */
void __vector_8(void)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* TIMER1_OVF_vect */
void __vector_9(void)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* TIMER0_COMP_vect */
void __vector_10(void)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

/* TIMER0_OVF_vect */
void __vector_11(void)
{
	ticks++;
	if(g_callBackPtr != NULL_PTR)
	{
		if(ticks >= interruptOverflow)
		{
			ticks= 0;
			(*g_callBackPtr)();
		}
	}
}




