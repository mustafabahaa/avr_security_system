/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** buzzer.h
 **************************************************************************/
#ifndef _BUZZER_H_
#define _BUZZER_H_

/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "types.h"
#include "gpio.h"

/*************************************************************************/
/*                                 Types                                 */
/*************************************************************************/
typedef enum
{
	BUZZER_CURRENT_SOURCING,
	BUZZER_CURRENT_SINKING
} buzzer_current_t;

typedef enum
{
	BUZZER_GPIO_STATE_SUCCESS,
	BUZZER_GPIO_INVALID_CURRENT,
	BUZZER_GPIO_STATE_ERROR
} buzzer_error_t;

typedef struct
{
	u8_t base_addr;
	u8_t pin_num;
	buzzer_current_t wiring;
} buzzer_t;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
 ** hal_buzzer_init()
 **
 ** parameter: buzzer_t* the_buzzer
 ** return    : BUZZER_error_t
 ***************************************************************************
 ** this function is used to initialize all the necessary sequence for BUZZER
 **************************************************************************/
buzzer_error_t hal_buzzer_init(buzzer_t *the_buzzer);

/**************************************************************************
 ** hal_buzzer_set_state()
 **
 ** parameter: buzzer_t* the_buzzer
 ** parameter: u8_t value
 ** return    : BUZZER_error_t
 ***************************************************************************
 ** this function set the states of the BUZZER on or off
 **************************************************************************/
buzzer_error_t hal_buzzer_set_state(buzzer_t *the_buzzer, u8_t value);

/**************************************************************************
 ** hal_buzzer_toggle_state()
 **
 ** parameter: buzzer_t* the_buzzer
 ** return    : BUZZER_error_t
 ***************************************************************************
 ** this function toggle the BUZZER states
 **************************************************************************/
buzzer_error_t hal_buzzer_toggle_state(buzzer_t *the_buzzer);

/**************************************************************************
 ** hal_buzzer_get_state()
 **
 ** parameter: buzzer_t* the_buzzer
 ** parameter: u8_t* value
 ** return    : BUZZER_error_t
 ***************************************************************************
 ** this function get the states of the BUZZER on or off
 **************************************************************************/
buzzer_error_t hal_buzzer_get_state(buzzer_t *the_buzzer, u8_t *value);

#endif /*_BUZZER_H_*/
/**************************************************************************/
