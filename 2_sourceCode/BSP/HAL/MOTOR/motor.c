/*
 * motor.c
 *
 *  Created on: Mar 13, 2021
 *      Author: Lenovo
 */

#include "motor.h"



int main(void)
{
	DDRD |= (1<<PD7);	/* Make OC2 pin as output */
	while(1)
	{

		 PWM_4_OUTPUT(uint8 duty);

	}
}
