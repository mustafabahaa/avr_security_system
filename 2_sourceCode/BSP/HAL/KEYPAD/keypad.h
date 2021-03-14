/*
 * keypad.h
 *
 *  Created on: Mar 11, 2021
 *      Author: Lenovo
 */

#ifndef HAL_KEYPAD_H_
#define HAL_KEYPAD_H_

#include "../../INCLUDE/common_macros.h"
#include "../../INCLUDE/micro_config.h"
#include"../../INCLUDE/std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 4
#define N_row 4

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN  PINA
#define KEYPAD_PORT_DIR DDRA

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */
uint8 KeyPad_getPressedKey(void);


#endif /* HAL_KEYPAD_H_ */
