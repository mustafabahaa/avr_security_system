/**************************************************************************
** This  software  is  in  the  public  domain , furnished "as is", without
** technical support,  and with no  warranty, express or implied, as to its
** usefulness for any purpose.

** led.c
***************************************************************************
**                              Includes                                 **
**************************************************************************/
#include "led.h"

/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

led_error_t hal_led_init(led_t *the_led)
{
    led_error_t error = LED_STATE_SUCCESS;

    if (the_led->wiring == CURRENT_SOURCING ||
        the_led->wiring == CURRENT_SINKING)
    {
        if (STATE_SUCCESS == mcal_gpio_pin_init(
                                 the_led->base_addr,
                                 the_led->pin_num, DIR_OUTPUT))
        {
            /* led initialized */
        }
        else
        {
            error = LED_GPIO_ERROR;
        }
    }
    else
    {
        error = LED_STATE_INVALID_CURRENT;
    }
    return error;
}

led_error_t hal_led_set_state(led_t *the_led, u8_t value)
{
    led_error_t error = LED_STATE_SUCCESS;

    if (the_led->wiring == CURRENT_SOURCING)
    {
        if (STATE_SUCCESS == mcal_gpio_pin_write(
                                 the_led->base_addr,
                                 the_led->pin_num, value))
        {
            /* led value is written */
        }
        else
        {
            error = LED_GPIO_ERROR;
        }
    }
    else if (the_led->wiring == CURRENT_SINKING)
    {
        if (STATE_SUCCESS == mcal_gpio_pin_write(
                                 the_led->base_addr,
                                 the_led->pin_num, !value))
        {
            /* led value is written */
        }
        else
        {
            error = LED_GPIO_ERROR;
        }
    }
    else
    {
        error = LED_STATE_INVALID_CURRENT;
    }
    return error;
}

led_error_t hal_led_get_state(led_t *the_led, u8_t *result)
{
    led_error_t error = LED_STATE_SUCCESS;

    u8_t pin;

    if (STATE_SUCCESS == mcal_gpio_pin_read(
                             the_led->base_addr,
                             the_led->pin_num, &pin))
    {
        if (the_led->wiring == CURRENT_SOURCING)
        {
            *result = pin;
        }
        else if (the_led->wiring == CURRENT_SINKING)
        {
            *result = !pin;
        }
        else
        {
            error = LED_STATE_INVALID_CURRENT;
        }
    }
    else
    {
        error = LED_GPIO_ERROR;
    }

    return error;
}