
/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** lcd.c
 **************************************************************************
 **                              Includes                                 *
 *************************************************************************/
#include "lcd.h"
/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/
lcd_error_t hal_lcd_init(lcd_t *lcd)
{
	lcd_error_t error = LCD_SUCCESS;
	GPIO_STATE_ERROR_t gpioError = GPIO_STATE_SUCCESS;

	/* Configure the control pins(E,RS,RW) as output pins */
	gpioError = mcal_gpio_pin_init(lcd->lcdControlPort, lcd->lcdE, DIR_OUTPUT);
	gpioError = mcal_gpio_pin_init(lcd->lcdControlPort, lcd->lcdRW, DIR_OUTPUT);
	gpioError = mcal_gpio_pin_init(lcd->lcdControlPort, lcd->lcdRS, DIR_OUTPUT);

	if (gpioError == GPIO_STATE_SUCCESS)
	{
		if (lcd->lcdMode == MODE_8_BIT)
		{
			/* Configure the data port as output port */
			if (PORT_STATE_SUCCESS == mcal_port_init(lcd->lcdDataPort , DIR_PORT_OUTPUT , PORT_FULL))
			{
				/* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
				if (LCD_SUCCESS == hal_lcd_sendData(lcd,COMMAND,TWO_LINE_LCD_Eight_BIT_MODE))
				{
					/* 8 bit mode is configured */
				}
				else
				{
					error = LCD_command_ERROR;
				}
			}
			else
			{
				error = LCD_ERROR;
			}
		}
		else if (lcd->lcdMode == MODE_4_BIT)
		{
			/* Configure the data port as output port */
			if (PORT_STATE_SUCCESS == mcal_port_init(lcd->lcdDataPort , DIR_PORT_OUTPUT , PORT_HIGH_ORDER))
			{
				/* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
				if (LCD_SUCCESS == hal_lcd_sendData(lcd,COMMAND,TWO_LINE_LCD_Four_BIT_MODE))
				{
					/* 5 bit mode is configured */
				}
				else
				{
					error = LCD_command_ERROR;
				}
			}
			else
			{
				error = LCD_ERROR;
			}
		}
		else
		{
			error = LCD_MODE_ERROR;
		}


		if (error == LCD_SUCCESS)
		{
			/* cursor off */
			if (LCD_SUCCESS == hal_lcd_sendData(lcd,COMMAND,CURSOR_OFF))
			{
				/* clear LCD at the beginning */
				if (LCD_SUCCESS ==  hal_lcd_sendData(lcd,COMMAND,CLEAR_COMMAND))
				{
					/* LCD initialized */
				}
				else
				{
					error = LCD_command_ERROR;
				}
			}
			else
			{
				error = LCD_command_ERROR;
			}
		}
		else
		{
			/* error */
		}
	}
	else
	{
		error = LCD_ERROR;
	}

	return error;
}

lcd_error_t hal_lcd_sendData(lcd_t* lcd ,lcd_data_types_t type, u8_t data )
{
	lcd_error_t error = LCD_SUCCESS;
	GPIO_STATE_ERROR_t gpioError = GPIO_STATE_SUCCESS;
	port_error_t portError = PORT_STATE_SUCCESS;

	if (type == COMMAND)
	{
		gpioError = mcal_gpio_pin_write(lcd->lcdControlPort,lcd->lcdRS ,LOW);

	}
	else if(type == DISPLAY)
	{
		gpioError = mcal_gpio_pin_write(lcd->lcdControlPort,lcd->lcdRS ,HIGH);
	}
	else
	{
		error =	LCD_INVALID_TYPE;
	}

	/* Enable LCD E=1 */
	gpioError = mcal_gpio_pin_write(lcd->lcdControlPort,lcd->lcdE ,HIGH);
	delay_ms(1);

	if(lcd->lcdMode == MODE_8_BIT)
	{
		/* out the required command to the data bus D0 --> D7 */
		portError = mcal_port_write(lcd->lcdDataPort, data ,LOW);
	}
	else if (lcd->lcdMode == MODE_4_BIT)
	{
		/* Sending command with 4 bit mode*/
		portError = mcal_port_write(lcd->lcdDataPort, data , PORT_HIGH_ORDER );
	}
	else
	{
		return LCD_MODE_ERROR;
	}
	delay_ms(1);

	/* disable LCD E=0 */
	gpioError = mcal_gpio_pin_write(lcd->lcdControlPort,lcd->lcdE ,LOW);
	delay_ms(1);

	error = (gpioError == GPIO_STATE_SUCCESS && portError == PORT_STATE_SUCCESS) ?
			LCD_SUCCESS :  LCD_ERROR;

	return error;
}


lcd_error_t hal_lcd_displayString(lcd_t *lcd, const u8_t *str)
{
	lcd_error_t error = LCD_SUCCESS;
	u8_t i = 0;
	while(str[i] != '\0')
	{
		error = hal_lcd_sendData(lcd,DISPLAY,str[i]);
		i++;
	}
	return error;
}

lcd_error_t hal_lcd_goToRowColumn(lcd_t *lcd , u8_t row,u8_t col)
{
	lcd_error_t error = LCD_SUCCESS;
	u8_t Address=0;

	/* first of all calculate the required address */
	switch(row)
	{
	case 0:
		Address=col;
		break;
	case 1:
		Address=col+0x40;
		break;
	case 2:
		Address=col+0x10;
		break;
	case 3:
		Address=col+0x50;
		break;
	}
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000+Address */
	error = hal_lcd_sendData(lcd, COMMAND, (Address | SET_CURSOR_LOCATION));
	return error;
}

lcd_error_t hal_lcd_intgerToString(lcd_t *lcd,u16_t data)
{
	lcd_error_t error = LCD_SUCCESS;
	u8_t buff[16]; /* String to hold the ascii result */
	std_itoa(data,buff,10); /* 10 for decimal */
	error = hal_lcd_displayString(lcd,buff);
	return error;
}

lcd_error_t hal_lcd_clearScreen(lcd_t *lcd)
{
	lcd_error_t error = LCD_SUCCESS;
	error = hal_lcd_sendData(lcd,COMMAND,CLEAR_COMMAND); //clear display
	return error;
}

