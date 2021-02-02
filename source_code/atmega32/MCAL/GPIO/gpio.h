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
#include "types.h"
#include "atmega32.h"
/*************************************************************************/
/*                              Macros                                   */
/*************************************************************************/

#define BASE_A 0x39
#define BASE_B 0x36
#define BASE_C 0x33
#define BASE_D 0x30

#define OFFSET_PIN 0x00
#define OFFSET_DIR 0x01
#define OFFSET_PORT 0x02

#define PORT_ON 0xFF
#define PORT_OFF 0x00
#define PORT_OUTPUT_DIR 0xFF
#define PORT_INPUT_DIR 0x00

#define MAX_PIN_NUMBER 8

/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/
typedef enum
{
  DIR_INPUT_PULLUP,
  DIR_INPUT_PULLDOWN,
  DIR_OUTPUT
} pinState;

typedef enum
{
  DIR_PORT_INPUT_PULLUP,
  DIR_PORT_INPUT_PULLDOWN,
  DIR_PORT_OUTPUT
} portState;

typedef enum gpio_error
{
  STATE_SUCCESS,
  STATE_ERROR,
  STATE_INVALID_ADDR,
  STATE_INVAILD_PIN,
  STATE_INVALID_DIR,
  STATE_INVALID_VALUE
} gpio_error_t;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
** mcal_gpio_pin_init()
**
** parameters: u8_t base
** parameters: u8_t pin
** parameters: pinState dir
** return    : gpio_error_t
***************************************************************************
** this function is used to initialize all the necessary sequence for pin
**************************************************************************/
gpio_error_t mcal_gpio_pin_init(u8_t base, u8_t pin, pinState dir);

/**************************************************************************
** mcal_gpio_pin_write()
**
** parameters: u8_t base
** parameters: u8_t pin
** parameters: u8_t value
** return    : gpio_error_t
***************************************************************************
** this function is used write a value to gpio pin
**************************************************************************/
gpio_error_t mcal_gpio_pin_write(u8_t base, u8_t pin, u8_t value);

/**************************************************************************
** mcal_gpio_pin_toggle()
**
** parameters: u8_t base
** parameters: u8_t pin
** return    : gpio_error_t
***************************************************************************
** this function is used to toggle gpio pin
**************************************************************************/
gpio_error_t mcal_gpio_pin_toggle(u8_t base, u8_t pin);

/**************************************************************************
** mcal_gpio_pin_read()
**
** parameters: u8_t base
** parameters: u8_t pin
** parameters: u8_t* value
** return    : gpio_error_t
***************************************************************************
** this function is used read a value from gpio pin
**************************************************************************/
gpio_error_t mcal_gpio_pin_read(u8_t base, u8_t pin, u8_t *value);

/**************************************************************************
** mcal_gpio_port_init()
**
** parameters: u8_t base
** parameters: portState dir
** return    : gpio_error_t
***************************************************************************
** this function is used to initialize all the necessary sequence for port
**************************************************************************/
gpio_error_t mcal_gpio_port_init(u8_t base, portState dir);

/**************************************************************************
** mcal_gpio_port_write()
**
** parameters: u8_t base
** parameters: u8_t value
** return    : gpio_error_t
***************************************************************************
** this function is used to write a value to all port
**************************************************************************/
gpio_error_t mcal_gpio_port_write(u8_t base, u8_t value);

/**************************************************************************
** mcal_gpio_port_read()
**
** parameters: u8_t base
** parameters: u8_t* value
** return    : gpio_error_t
***************************************************************************
** this function is used to read a value from all port
**************************************************************************/
gpio_error_t mcal_gpio_port_read(u8_t base, u8_t *value);

#endif /* GPIO_H_ */