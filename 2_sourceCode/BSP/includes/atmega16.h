/*************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** atmega16.h
 **************************************************************************/
#ifndef ATMEGA_16_H_
#define ATMEGA_16_H_
/*************************************************************************/
/*                          Needed Includes                              */
/*************************************************************************/
#define F_CPU 8000000UL
#define ECU_PORT_PINS_NUMBER 8
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

/*************************************************************************/
/*                               Register                                */
/*************************************************************************/

/*************************************************************************/
/*                               PORT Register                           */
/*************************************************************************/
#define BASE_A 0x39
#define BASE_B 0x36
#define BASE_C 0x33
#define BASE_D 0x30

#define OFFSET_PIN 0x00
#define OFFSET_DIR 0x01
#define OFFSET_PORT 0x02
/*************************************************************************/
/*                               TIMER Register                          */
/*************************************************************************/
#define TCCR0   0x53
#define CS00    0
#define CS01    1
#define CS02    2
#define WGM01   3
#define COM00   4
#define COM01   5
#define WGM00   6
#define FOC0    7

#define TCCR1A  0x4F
#define WGM10   0
#define WGM11   1
#define FOC1B   2
#define FOC1A   3
#define COM1B0  4
#define COM1B1  5
#define COM1A0  6
#define COM1A1  7

#define TCCR1B  0x4E
#define CS10    0
#define CS11    1
#define CS12    2
#define WGM12   3
#define WGM13   4
#define ICES1   6
#define ICNC1   7

#define TCCR2   0x45
#define CS20    0
#define CS21    1
#define CS22    2
#define WGM21   3
#define COM20   4
#define COM21   5
#define WGM20   6
#define FOC2    7

#define OCR0    0x5C
#define OCR1A   0x4A
#define OCR1AL  0x4A
#define OCR1AH  0x4B
#define OCR1B   0x48
#define OCR1BL  0x48
#define OCR1BH  0x49
#define OCR2    0x43
/*************************************************************************/
/*                               UART Register                           */
/*************************************************************************/
#define UCSRA 0x2B
#define MPCM    0
#define U2X     1
#define PE      2
#define DOR     3
#define FE      4
#define UDRE    5
#define TXC     6
#define RXC     7

#define UCSRB 0x2A
#define TXB8    0
#define RXB8    1
#define UCSZ2   2
#define TXEN    3
#define RXEN    4
#define UDRIE   5
#define TXCIE   6
#define RXCIE   7

#define UCSRC 0x40
#define UCPOL   0
#define UCSZ0   1
#define UCSZ1   2
#define USBS    3
#define UPM0    4
#define UPM1    5
#define UMSEL   6
#define URSEL   7

#define UBRRH   0x40
#define URSEL   7

#define UBRRL   0x29

#define UDR 0x2c



#endif /* ATMEGA_16_H_ */

