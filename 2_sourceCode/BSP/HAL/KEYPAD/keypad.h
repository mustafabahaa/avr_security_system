

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../includes/types.h"
#include "../../includes/atmega16.h"
#include "../../MCAL/PORT/port.h"



/* configure  your row pins*/
/* comment any line if you don't have 4 rows*/
#define ROW_1 0
#define ROW_2 1
#define ROW_3 2
#define ROW_4 3

/* configure  your columns pins */
/* comment any line if you don't have 4 columns*/
#define COL_1 4
#define COL_2 5
#define COL_3 6
#define COL_4 7

/* configure as your keypad dimention */
#define ROW_NUMBERS 4
#define COL_NUMBERS 4

/* configure the port of LCD */
#define KEYPAD_PORT (BASE_A + OFFSET_PORT)
#define KEYPAD_PIN  (BASE_A + OFFSET_PIN)



typedef enum
{
	KEYPAD_SUCCESS,
	KEYPAD_FAIL,
}keypad_error_t;

typedef struct
{
	u8_t keypad_port;
	u8_t keypad_
};
/* configure as your keypad */
s8_t KeyPad [ROW_NUMBERS][COL_NUMBERS] =
{
		{'7', '8' , '9' , '/' },
		{'4', '5' , '6' , '*' },
		{'1', '2' , '3' , '-' },
		{'A', '0' , '=' , '+' }
};

/* Don't change this at all */
#define NO_KEY_PRESSED 0XFF

/* Don't change this variables at all */
s8_t pressed=0;
s8_t keypressed = 0;
s8_t col_loop=COL_1;


/*************************************************************************/
/*                           Public Functions                            */
/*************************************************************************
 hal_keypad_getKey()
 **  paramters : void
 **  return    : u8_t
 ** -- implementation ---------------------------------------------------------
 **  this function loops the coloumns and rows of an keypad and return the
 **  keypressed at the intersection between the column and raw pressed ,
 **  configure the wanted character to be returned from the matrix at
 **  keypadconfig.h , this function returns a s8_t characters value in
 **  you can directly print it on LCD or to use the value as a integer
 **  you have to convert it back to integer.
 ** -------------------------------------------------------------------------
 ** important
 ** -------------------------------------------------------------------------
 ** the function will return 0XFF when no key pressed
 ** the function will return the pressed key as a character if key pressed
 ** -------------------------------------------------------------------------*/
u8_t hal_keypad_getKey();


#endif /* KEYPAD_H_ */
