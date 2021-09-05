/*************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** avr.h
 **************************************************************************/
#ifndef _AVR_H_
#define _AVR_H_
/*************************************************************************/
/*                          Needed Includes                              */
/*************************************************************************/
#define F_CPU 1000000UL
#define ECU_PORT_PINS_NUMBER 8
/*************************************************************************/
/*                          Common Macros                                */
/*************************************************************************/
#define LSB 0x0F
#define MSB 0xF0
#define HIGH 1
#define LOW 0
#define ON 1
#define OFF 0
#define NULL_PTR    ((void*)0)
#define NULL '\0'
/*************************************************************************/
/*                      Register Access Functions Macros                 */
/*************************************************************************/
#define register(reg) (*((volatile u8_t *)(u16_t) reg))
#define set_bit(reg, bit) (register(reg) |= (1 << bit))
#define dbl_set_bit(reg, bit,bit2) (register(reg) |= (1 << bit) | (1<<bit2))
#define tog_bit(reg, bit) (register(reg) ^= (1 << bit))
#define clr_bit(reg, bit) (register(reg) &= ~(1 << bit))
#define bit_is_set(reg, bit) ((register(reg) & (1 << bit)))
#define bit_is_clr(reg, bit) (!(register(reg) & (1 << bit)))
#define en_bit(bit) (1<<bit)
#define reg_write(reg,value) register(reg) = value;
#define reg_mask_write(reg,mask,value) register(reg) = (register(reg) & mask) | value;
#define reg_read(reg,value) value = register(reg);
#define reg_mask_read(reg,mask,value) value = register(reg) & mask;

/*************************************************************************/
/*                               Register                                */
/*************************************************************************/

/*************************************************************************/
/*                               PORT Register                           */
/*************************************************************************/
#define BASE_A  0x20
#define PA7     7
#define PA6     6
#define PA5     5
#define PA4     4
#define PA3     3
#define PA2     2
#define PA1     1
#define PA0    

#define BASE_B  0x23
#define PB7     7
#define PB6     6
#define PB5     5
#define PB4     4
#define PB3     3
#define PB2     2
#define PB1     1
#define PB0     0

#define BASE_C  0x26
#define PC7     7
#define PC6     6
#define PC5     5
#define PC4     4
#define PC3     3
#define PC2     2
#define PC1     1
#define PC0     0

#define BASE_D  0x29
#define PD7     7
#define PD6     6
#define PD5     5
#define PD4     4
#define PD3     3
#define PD2     2
#define PD1     1
#define PD0     0

#define OFFSET_PIN 0x00
#define OFFSET_DIR 0x01
#define OFFSET_PORT 0x02

/*************************************************************************/
/*                               INTERRUPT Register                          */
/*************************************************************************/

/*enable and disable interrupt by setting and clearing I bit in SREG */
#define SREG_interrupt_bit 7
#define setGlobalInterrupt set_bit(SREG, SREG_interrupt_bit)
#define clearGlobalInterrupt clr_bit(SREG, SREG_interrupt_bit)

#define SREG 0x5F
/*************************************************************************/
/*                               I2C Register                            */
/*************************************************************************/
#define TWBR    0xB8

#define TWSR    0xB9
#define TWPS0   0
#define TWPS1   1
#define TWS3    3
#define TWS4    4
#define TWS5    5
#define TWS6    6
#define TWS7    7

#define TWAR    0xBA
#define TWGCE   0
#define TWA0    1
#define TWA1    2
#define TWA2    3
#define TWA3    4
#define TWA4    5
#define TWA5    6
#define TWA6    7

#define TWDR    0xBB

#define TWCR    0xBC
#define TWIE    0
#define TWEN    2
#define TWWC    3
#define TWSTO   4
#define TWSTA   5
#define TWEA    6
#define TWINT   7

#define TWAMR   0xBD
#define TWAM0   1
#define TWAM1   2
#define TWAM2   3
#define TWAM3   4
#define TWAM4   5
#define TWAM5   6
#define TWAM6   7
/*************************************************************************/
/*                               SPI Register                            */
/*************************************************************************/
#define SPCR    0x4C
#define SPR0    0
#define SPR1    1
#define CPHA    2
#define CPOL    3
#define MSTR    4
#define DORD    5
#define SPE     6
#define SPIE    7

#define SPSR    0x4D
#define SPI2X   0
#define WCOL    6
#define SPIF    7

#define SPDR    0x4E
#endif /* _AVR_H_ */

