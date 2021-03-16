/*
 * keypad.h
 *
 *  Created on: Mar 11, 2021
 *      Author: Lenovo
 */

#ifndef HAL_KEYPAD_H_
#define HAL_KEYPAD_H_

#include "../../includes/types.h"
#include "../../includes/atmega16.h"

/*************************************************************************/
/*                                 Types                                 */
/*************************************************************************/
typedef enum
{
	KEYPAD_SUCCESS,
	KEYPAD_ERROR,
} keypad_error_t;

/*******************************************************************************
 *                      				 Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 4
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT (BASE_A + OFFSET_PORT)
#define KEYPAD_PORT_IN  (BASE_A + OFFSET_PIN)
#define KEYPAD_PORT_DIR (BASE_A + OFFSET_DIR)

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** hal_keypad_getPressedKey()
 **
 ** parameters: void
 ** return    : u8_t
 ***************************************************************************
 ** this function is used to get the pressed keypad key
 **************************************************************************/

u8_t hal_keypad_getPressedKey(void);


#endif /* HAL_KEYPAD_H_ */
