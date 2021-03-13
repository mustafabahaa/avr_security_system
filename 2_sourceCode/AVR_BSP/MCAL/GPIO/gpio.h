/**************************************************************************
** This  software  is  in  the  public  domain , furnished "as is", without
** technical support,  and with no  warranty, express or implied, as to its
** usefulness for any purpose.

** GPIO.h
**************************************************************************/
#ifndef GPIO_H_
#define GPIO_H_

/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "./../../includes/types.h"
#include "./../../includes/atmega32.h"
#include "./../port/port.h"
/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/
typedef enum
{
  DIR_INPUT_PULLUP,
  DIR_INPUT_PULLDOWN,
  DIR_OUTPUT
} pinState;

typedef enum GPIO_STATE_ERROR_t
{
  GPIO_STATE_SUCCESS,
  GPIO_STATE_ERROR,
  GPIO_STATE_INVALID_ADDR,
  GPIO_STATE_INVAILD_PIN,
  GPIO_STATE_INVALID_DIR,
  GPIO_STATE_INVALID_VALUE
} GPIO_STATE_ERROR_t;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
** mcal_gpio_pin_init()
**
** parameters: u8_t base
** parameters: u8_t pin
** parameters: pinState dir
** return    : GPIO_STATE_ERROR_t
***************************************************************************
** this function is used to initialize all the necessary sequence for pin
**************************************************************************/
GPIO_STATE_ERROR_t mcal_gpio_pin_init(u8_t base, u8_t pin, pinState dir);

/**************************************************************************
** mcal_gpio_pin_write()
**
** parameters: u8_t base
** parameters: u8_t pin
** parameters: u8_t value
** return    : GPIO_STATE_ERROR_t
***************************************************************************
** this function is used write a value to gpio pin
**************************************************************************/
GPIO_STATE_ERROR_t mcal_gpio_pin_write(u8_t base, u8_t pin, u8_t value);

/**************************************************************************
** mcal_gpio_pin_toggle()
**
** parameters: u8_t base
** parameters: u8_t pin
** return    : GPIO_STATE_ERROR_t
***************************************************************************
** this function is used to toggle gpio pin
**************************************************************************/
GPIO_STATE_ERROR_t mcal_gpio_pin_toggle(u8_t base, u8_t pin);

/**************************************************************************
** mcal_gpio_pin_read()
**
** parameters: u8_t base
** parameters: u8_t pin
** parameters: u8_t* value
** return    : GPIO_STATE_ERROR_t
***************************************************************************
** this function is used read a value from gpio pin
**************************************************************************/
GPIO_STATE_ERROR_t mcal_gpio_pin_read(u8_t base, u8_t pin, u8_t *value);

#endif /* GPIO_H_ */
