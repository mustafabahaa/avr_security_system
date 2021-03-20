/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** std_library.h
 ***************************************************************************
 **                              Includes                                 **
 **************************************************************************/
#include "std_library.h"

/***************************************************************************
 **                     Static Functions Prototype                        **
 ***************************************************************************
 ** std_reverse()
 **
 ** parameters: u8_t *buffer
 ** parameters: u16_t i
 ** parameters: u16_t j
 ** return    : void
 **************************************************************************
 ** this function is used to reverse buffer[i..j]
 *************************************************************************/
static u8_t* std_reverse(u8_t *buffer, u16_t i, u16_t j);

/**************************************************************************
** std_swap()
**
** parameters: u8_t *x
** parameters: u8_t *y
** return    : void
**************************************************************************
** this function is used to swap two numbers
*************************************************************************/
static inline void std_swap(u8_t *x, u8_t *y);

/**************************************************************************
** std_abs()
**
** parameters: u16_t v
** parameters: u8_t *y
** return    : void
**************************************************************************
** this function is used to get the absolute value of number
*************************************************************************/
static u16_t std_abs(u16_t v);
/**************************************************************************/
/*                     Functions Implementation                           */
/**************************************************************************/

u8_t* std_strcat(u8_t* destination,u8_t* source)
{
    // make ptr pou16_t to the end of destination string
	u8_t* ptr = destination + std_strlen(destination);

    // Appends u8_tacters of source to the destination string
    while (*source != '\0')
        *ptr++ = *source++;

    // null terminate destination string
    *ptr = '\0';

    // destination is returned by standard strcat()
    return destination;
}


u16_t std_strlen(u8_t *str)
{
    u16_t count = 0;
    while(*str!='\0')
    {
        count++;
        str++;
    }
    return count;
}

u8_t* std_itoa(u16_t value, u8_t* buffer, u16_t base)
{
    // invalid input
    if (base < 2 || base > 32)
        return buffer;

    // consider absolute value of number
    u16_t n = std_abs(value);

    u16_t i = 0;
    while (n)
    {
        u16_t r = n % base;

        if (r >= 10)
            buffer[i++] = 65 + (r - 10);
        else
            buffer[i++] = 48 + r;

        n = n / base;
    }

    // if number is 0
    if (i == 0)
        buffer[i++] = '0';

    // If base is 10 and value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10)
        buffer[i++] = '-';

    buffer[i] = '\0'; // null terminate string

    // reverse the string and return it
    return std_reverse(buffer, 0, i - 1);
}

u16_t std_strcmp(const u8_t *X, const u8_t *Y)
{
    while(*X)
    {
        // if u8_t differ or end of second string is reached
        if (*X != *Y)
            break;

        // move to next pair of u8_t
        X++;
        Y++;
    }

    // return the ASCII difference after converting u8_t* to unsigned u8_t*
    return *(const u8_t*)X - *(const u8_t*)Y;
}


/**************************************************************************/
/*                     Static Functions Implementation                    */
/**************************************************************************/

static inline void std_swap(u8_t *x, u8_t *y)\
{
    u8_t t = *x; *x = *y; *y = t;
}


static u8_t* std_reverse(u8_t *buffer, u16_t i, u16_t j)
{
    while (i < j)
        std_swap(&buffer[i++], &buffer[j--]);

    return buffer;
}

static u16_t std_abs(u16_t v)
{
  return v * ((v>0) - (v<0));
}

