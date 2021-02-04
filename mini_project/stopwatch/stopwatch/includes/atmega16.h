#ifndef ATMEGA16_H_
#define ATMEGA16_H_
/*************************************************************************/
/*                                 Macro                                 */
/*************************************************************************/
#define set_bit(register, bit) (register |= (1 << bit))
#define tog_bit(register, bit) (register ^= (1 << bit))
#define clr_bit(register, bit) (register &= ~(1 << bit))

#endif /* ATMEGA16_H_ */