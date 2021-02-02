/*************************************************************************
** This  software  is  in  the  public  domain , furnished "as is", without 
** technical support,  and with no  warranty, express or implied, as to its
** usefulness for any purpose.

** atmega32.h
**************************************************************************/
#ifndef ATMEGA_32_H_
#define ATMEGA_32_H_
/*************************************************************************/
/*                          Needed Includes                              */
/*************************************************************************/
#define F_CPU 1000000UL
#include <util/delay.h>
/*************************************************************************/
/*                          Common Macros                                */
/*************************************************************************/
#define HIGH 1
#define LOW 0
#define ON 1
#define OFF 0
/*************************************************************************/
/*                      Register Access Functions Macros                 */
/*************************************************************************/

#define set_bit(register, bit) ((*((volatile u8_t *)(u16_t) register)) |= (1 << bit))
#define tog_bit(register, bit) ((*((volatile u8_t *)(u16_t) register)) ^= (1 << bit))
#define clr_bit(register, bit) ((*((volatile u8_t *)(u16_t) register)) &= ~(1 << bit))
#define bit_is_set(register, bit) (((*((volatile u8_t *)(u16_t) register)) & (1 << bit)) ? HIGH : LOW);
#define bit_is_clr(register, bit) (((*((volatile u8_t *)(u16_t) register)) & (1 << bit)) ? LOW : HIGH);

inline void reg_write(u8_t reg, u8_t value)
{
	(*((volatile u8_t *)(u16_t)reg)) = value;
}
inline void reg_read(u8_t reg, u8_t *value)
{
	*value = (*((volatile u8_t *)(u16_t)reg));
}

#endif /* ATMEGA_32_H_ */

