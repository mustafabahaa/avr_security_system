
#include <avr/io.h>


int main(void)
{
    while (1) 
    {
		DDRC  = 0b00000001;
		PORTC = 0b00000001;
    }
}

