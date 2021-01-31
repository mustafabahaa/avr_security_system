/*************************************************************************
** This  software  is  in  the  public  domain , furnished "as is", without
** technical support,  and with no  warranty, express or implied, as to its
** usefulness for any purpose.

** StandardTypes.h
**************************************************************************/
#ifndef STANDARDTYPES_H_
#define STANDARDTYPES_H_
/*************************************************************************/
/*                          standard types                               */
/*************************************************************************/

typedef unsigned char u8_t; // Define unsigned char as u8_t
typedef char s8_t;          // Define  char as s8_t

typedef unsigned short u16_t; // Define unsigned short as u16_t
typedef short s16_t;          // Define  short as s16_t

typedef unsigned long u32_t; // Define unsigned long as u32_t
typedef long s32_t;          // Define  long as sint32_t

typedef unsigned long long u64_t; // Define unsigned long long u64_t
typedef long long s64_t;          // Define  long long as s64_t

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

#endif /* STANDARDTYPES_H_ */
       /*************************************************************************/