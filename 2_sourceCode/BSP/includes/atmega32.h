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
#define F_CPU 8000000UL
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

#define reg_write(reg,value) (*((volatile u8_t *)(u16_t)reg)) = value;
#define reg_read(reg,value) (*((volatile u8_t *)(u16_t)reg)) = *value;

#endif /* ATMEGA_32_H_ */

