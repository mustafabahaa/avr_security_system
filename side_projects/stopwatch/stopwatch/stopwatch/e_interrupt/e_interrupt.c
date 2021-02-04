
#include "e_interrupt.h"

void e_interrupt_initialization()
{
    /* enable global interrupts */
    set_bit(SREG, 7);
    
    /*enable interrupt 0 , 1 , 2 */
    set_bit(GICR, INT0);
    set_bit(GICR, INT1);
    set_bit(GICR, INT2);

    /*enable interrupt 0 in falling edge mode */
    set_bit(MCUCR, ISC01);
    clr_bit(MCUCR, ISC00);

    /*enable interrupt 1 in falling edge mode */
    set_bit(MCUCR, ISC11);
    clr_bit(MCUCR, ISC10);

    /*enable interrupt 2 in falling edge mode */
    clr_bit(MCUCSR, ISC2);
}