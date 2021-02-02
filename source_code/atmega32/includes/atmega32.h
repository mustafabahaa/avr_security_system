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
#define REGISTER (*((volatile u8_t *)(u16_t)reg_addr))

inline void set_bit(u8_t reg_addr, u8_t bit_num)
{
	REGISTER |= (1 << bit_num);
}
inline void clr_bit(u8_t reg_addr, u8_t bit_num)
{
	REGISTER &= ~(1 << bit_num);
}
inline void tog_bit(u8_t reg_addr, u8_t bit_num)
{
	REGISTER ^= (1 << bit_num);
}

inline void reg_write(u8_t reg_addr, u8_t value)
{
	REGISTER = value;
}
inline void reg_read(u8_t reg_addr, u8_t *value)
{
	*value = REGISTER;
}

inline u8_t bit_is_set(u8_t reg_addr, u8_t bit_num)
{
	return (REGISTER & (1 << bit_num)) ? HIGH : LOW;
}
inline u8_t bit_is_clr(u8_t reg_addr, u8_t bit_num)
{
	return (REGISTER & (1 << bit_num)) ? LOW : HIGH;
}

#endif /* ATMEGA_32_H_ */
/*************************************************************************/
