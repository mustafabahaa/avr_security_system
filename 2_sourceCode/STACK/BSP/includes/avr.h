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

#define EICRA   0x69
#define ISC00   0
#define ISC01   1
#define ISC10   2
#define ISC11   3
#define ISC20   4
#define ISC21   5

#define EIMSK   0x3D
#define INT0    0
#define INT1    1
#define INT2    2

#define EIFR    0x3C
#define INTF0   0
#define INTF1   1
#define INTF2   2
/*************************************************************************/
/*                               TIMER Register                          */
/*************************************************************************/
#define TIMSK0   0x59
#define TOIE0   0
#define OCIE0A  1
#define OCIE0B  2

#define TIMSK1  0x6F
#define TOIE1   0
#define OCIE1A  1
#define OCIE1B  2
#define ICIE1   5

#define TIMSK2  0x70
#define TOIE2   0
#define OCIE2A  1
#define OCIE2B  2

#define TIMSK3  0x71
#define TOIE3   0
#define OCIE3A  1
#define OCIE3B  2
#define ICIE3   5

#define TCCR0A  0x44
#define WGM00   0
#define WGM01   1
#define COM0B0  4
#define COM0B1  5
#define COM0A0  6
#define COM0A1  7

#define TCCR0B  0x45
#define CS00    0
#define CS01    1
#define CS02    2
#define WGM02   3
#define FOC0B   6
#define FOC0A   7

#define TCNT0   0x46
#define OCR0A   0x47
#define OCR0B   0x48

#define TCCR1A  0x80
#define WGM10   0
#define WGM11   1
#define COM1B0  4
#define COM1B1  5
#define COM1A0  6
#define COM1A1  7

#define TCCR1B  0x81
#define CS10    0
#define CS11    1
#define CS12    2
#define WGM12   3
#define WGM13   4
#define ICES1   6
#define ICNC1   7

#define TCNT1   (0x84)
#define TCNT1L  (0x84)
#define TCNT1H  (0x85)
#define ICR1    (0x86)
#define ICR1L   (0x86)
#define ICR1H   (0x87)
#define OCR1A   (0x88)
#define OCR1AL  (0x88)
#define OCR1AH  (0x89)
#define OCR1B   (0x8A)
#define OCR1BL  (0x8A)
#define OCR1BH  (0x8B)


#define TCCR1C  0x82
#define FOC1B   6
#define FOC1A   7

#define TCCR3A  0x90
#define WGM30   0
#define WGM31   1
#define COM3B0  4
#define COM3B1  5
#define COM3A0  6
#define COM3A1  7

#define TCCR3B  0x91
#define CS30    0
#define CS31    1
#define CS32    2
#define WGM32   3
#define WGM33   4
#define ICES3   6
#define ICNC3   7

#define TCCR3C  0x92
#define FOC3B   6
#define FOC3A   7

/* Combine TCNT3L and TCNT3H */
#define TCNT3   0x94

#define TCNT3L  0x94
#define TCNT3H  0x95

/* Combine ICR3L and ICR3H */
#define ICR3    0x96

#define ICR3L   0x96
#define ICR3H   0x97

/* Combine OCR3AL and OCR3AH */
#define OCR3A   0x98

#define OCR3AL  0x98
#define OCR3AH  0x99

/* Combine OCR3BL and OCR3BH */
#define OCR3B   0x9A

#define OCR3BL  0x9A
#define OCR3BH  0x9B

#define TCCR2A  0xB0
#define WGM20   0
#define WGM21   1
#define COM2B0  4
#define COM2B1  5
#define COM2A0  6
#define COM2A1  7

#define TCCR2B  0xB1
#define CS20    0
#define CS21    1
#define CS22    2
#define WGM22   3
#define FOC2B   6
#define FOC2A   7

#define TCNT2   0xB2

#define OCR2A   0xB3

#define OCR2B   0xB4
/*************************************************************************/
/*                               UART Register                           */
/*************************************************************************/
#define UCSR0A  0xC0
#define MPCM0   0
#define U2X0    1
#define UPE0    2
#define DOR0    3
#define FE0     4
#define UDRE0   5
#define TXC0    6
#define RXC0    7

#define UCSR0B  0xC1
#define TXB80   0
#define RXB80   1
#define UCSZ02  2
#define TXEN0   3
#define RXEN0   4
#define UDRIE0  5
#define TXCIE0  6
#define RXCIE0  7

#define UCSR0C  0xC2
#define UCPOL0  0
#define UCSZ00  1
#define UCSZ01  2
#define USBS0   3
#define UPM00   4
#define UPM01   5
#define UMSEL00 6
#define UMSEL01 7

/* Reserved [0xC3] */

/* Combine UBRR0L and UBRR0H */
#define UBRR0   0xC4

#define UBRR0L  0xC4
#define UBRR0H  0xC5

#define UDR0    0xC6

/* Reserved [0xC7] */

#define UCSR1A  0xC8
#define MPCM1   0
#define U2X1    1
#define UPE1    2
#define DOR1    3
#define FE1     4
#define UDRE1   5
#define TXC1    6
#define RXC1    7

#define UCSR1B  0xC9
#define TXB81   0
#define RXB81   1
#define UCSZ12  2
#define TXEN1   3
#define RXEN1   4
#define UDRIE1  5
#define TXCIE1  6
#define RXCIE1  7

#define UCSR1C  0xCA
#define UCPOL1  0
#define UCSZ10  1
#define UCSZ11  2
#define USBS1   3
#define UPM10   4
#define UPM11   5
#define UMSEL10 6
#define UMSEL11 7

/* Reserved [0xCB] */

/* Combine UBRR1L and UBRR1H */
#define UBRR1   0xCC

#define UBRR1L  0xCC
#define UBRR1H  0xCD

#define UDR1    0xCE


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

