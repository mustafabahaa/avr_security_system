/*************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** atmega32.h
 **************************************************************************/
#ifndef ATMEGA_16_H_
#define ATMEGA_16_H_
/*************************************************************************/
/*                          Needed Includes                              */
/*************************************************************************/
#define F_CPU 1000000UL
#define ECU_PORT_PINS_NUMBER 8
/*************************************************************************/
/*                          Common Macros                                */
/*************************************************************************/
#define HIGH 1
#define LOW 0
#define ON 1
#define OFF 0
#define NULL_PTR    ((void*)0)
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
#define BASE_A 0x39
#define BASE_B 0x36
#define BASE_C 0x33
#define BASE_D 0x30

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

/*enable and disable interrupt by setting and clearing I bit in SREG */
#define SREG_interrupt_bit 7
#define setGlobalInterrupt set_bit(SREG, SREG_interrupt_bit)
#define clearGlobalInterrupt clr_bit(SREG, SREG_interrupt_bit)

/* define interrupt registers */
#define SREG 0X5F
#define GIFR 0x5A
#define GICR 0x5B
#define MCUCR 0x55
#define MCUCSR 0x54

/*MCUCR (MCU Control Register)*/
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
#define ISC2 6

/*Interrupts Number*/
#define INT0 6
#define INT1 7
#define INT2 5

/*Interrupts Flags*/
#define INTF0 6
#define INTF1 7
#define INTF2 5
/*************************************************************************/
/*                               TIMER Register                          */
/*************************************************************************/
#define TCNT0   0x52
#define TCNT1   0x4C
#define TCNT2   0x44

#define TIMSK   0x59
#define TOIE0   0
#define OCIE0   1
#define TOIE1   2
#define OCIE1B  3
#define OCIE1A  4
#define TICIE1  5
#define TOIE2   6
#define OCIE2   7

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

/*************************************************************************/
/*                               I2C Register                            */
/*************************************************************************/
#define TWBR    0x20

#define TWSR    0x21
#define TWPS0   0
#define TWPS1   1
#define TWS3    3
#define TWS4    4
#define TWS5    5
#define TWS6    6
#define TWS7    7

#define TWAR    0x22
#define TWGCE   0
#define TWA0    1
#define TWA1    2
#define TWA2    3
#define TWA3    4
#define TWA4    5
#define TWA5    6
#define TWA6    7

#define TWCR    0x56
#define TWIE    0
#define TWEN    2
#define TWWC    3
#define TWSTO   4
#define TWSTA   5
#define TWEA    6
#define TWINT   7

#define TWDR    0x23
/*************************************************************************/
/*                               SPI Register                            */
/*************************************************************************/
#define SPCR    0x2D
#define SPR0    0
#define SPR1    1
#define CPHA    2
#define CPOL    3
#define MSTR    4
#define DORD    5
#define SPE     6
#define SPIE    7

#define SPSR    0x2E
#define SPI2X   0
#define WCOL    6
#define SPIF    7

#define SPDR    0x2F

#endif /* ATMEGA_16_H_ */

