/**************************************************************************
** This  software  is  in  the  public  domain , furnished "as is", without
** technical support,  and with no  warranty, express or implied, as to its
** usefulness for any purpose.

** port.h
**************************************************************************/
#ifndef PORT_H_
#define PORT_H_
/*************************************************************************/
/*                              Includes                                 */
/*************************************************************************/
#include "./../../includes/types.h"
#include "./../../includes/atmega32.h"
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

#define MAX_PIN_NUMBER 8
#define PORT_ON 0xFF
#define PORT_OFF 0x00
#define PORT_OUTPUT_DIR 0xFF
#define PORT_INPUT_DIR 0x00
/*************************************************************************/
/*                               Types                                   */
/*************************************************************************/
typedef enum
{
  DIR_PORT_INPUT_PULLUP,
  DIR_PORT_INPUT_PULLDOWN,
  DIR_PORT_OUTPUT
} portState;

typedef enum port_error_t
{
  PORT_STATE_SUCCESS,
  PORT_STATE_ERROR,
  PORT_STATE_INVALID_ADDR,
  PORT_STATE_INVALID_DIR,
} port_error_t;

/*************************************************************************/
/*                           Public Functions                            */
/**************************************************************************
** mcal_port_init()
**
** parameters: u8_t base
** parameters: portState dir
** return    : GPIO_STATE_ERROR_t
***************************************************************************
** this function is used to initialize all the necessary sequence for port
**************************************************************************/
port_error_t mcal_port_init(u8_t base, portState dir);

/**************************************************************************
** mcal_port_write()
**
** parameters: u8_t base
** parameters: u8_t value
** return    : GPIO_STATE_ERROR_t
***************************************************************************
** this function is used to write a value to all port
**************************************************************************/
port_error_t mcal_port_write(u8_t base, u8_t value);

/**************************************************************************
** mcal_port_read()
**
** parameters: u8_t base
** parameters: u8_t* value
** return    : GPIO_STATE_ERROR_t
***************************************************************************
** this function is used to read a value from all port
**************************************************************************/
port_error_t mcal_port_read(u8_t base, u8_t *value);

#endif /* PORT_H_ */
