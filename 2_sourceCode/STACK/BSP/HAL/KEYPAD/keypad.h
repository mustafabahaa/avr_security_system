/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** keypad.h
 **************************************************************************/
#ifndef KEYPAD_H_
#define KEYPAD_H_
/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "../../includes/types.h"
#include "../../includes/atmega16.h"
#include "../../MCAL/PORT/port.h"
#include "../../MCAL/GPIO/gpio.h"
#include "./../../../Utility/delay/delay.h"
/*************************************************************************/
/*                               Macros                                  */
/*************************************************************************/
#define NO_KEY_PRESSED 0XFF
/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/
typedef enum
{
	KEYPAD_SUCCESS,
	KEYPAD_FAIL,
}keypad_error_t;

typedef struct
{
	u8_t keypadPORT;
	u8_t keypadPIN;
	u8_t keypadRowsNo;
	u8_t keypadColsNo;
	u8_t keypadRowsGPIOS[4];
	u8_t keypadColumnsGPIOS[4];
	s8_t keypadMapping [4][4];
}keypad_t;


/*************************************************************************
**                           Public Functions                            *
**************************************************************************
 ** hal_keypad_init()
 **
 ** parameters: keypad_t keypad
 ** return    : keypad_error_t
 **************************************************************************
 ** this function is used to init the keypad ports and pins
 *************************************************************************/
keypad_error_t hal_keypad_init(keypad_t* keypad);

/**************************************************************************
 **  hal_keypad_getKey()
 **  paramters : void
 **  return    : u8_t
 **
 **  this function loops the coloumns and rows of an keypad and return the
 **  keypressed at the intersection between the column and raw pressed ,
 **  configure the wanted character to be returned from the matrix at
 **  keypadconfig.h , this function returns a s8_t characters value in
 **  you can directly print it on LCD or to use the value as a integer
 **  you have to convert it back to integer.
 ** ----------------------------------------------------------------------
 ** important
 ** ----------------------------------------------------------------------
 ** the function will return 0XFF when no key pressed
 ** the function will return the pressed key as a character if key pressed
 ** ---------------------------------------------------------------------*/
keypad_error_t hal_keypad_getKey(keypad_t* keypad , s8_t* keyPressed);

#endif /* KEYPAD_H_ */
