/*
 * lcd.c
 *
 *  Created on: Mar 11, 2021
 *      Author: Lenovo
 */

#include "lcd.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
lcd_error_t LCD_init(lcd_t *lcd)
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
			if (PORT_STATE_SUCCESS == mcal_port_init(lcd->lcdDataPort , DIR_PORT_OUTPUT))
			{
				/* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
				if (LCD_SUCCESS == LCD_sendCommand(lcd,TWO_LINE_LCD_Eight_BIT_MODE))
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
			if (PORT_STATE_SUCCESS == mcal_port_init(lcd->lcdDataPort , DIR_HIGH_ORDER_PORT_OUTPUT))
			{
				/* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
				if (LCD_SUCCESS == LCD_sendCommand(lcd,TWO_LINE_LCD_Four_BIT_MODE))
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
			if (LCD_SUCCESS == LCD_sendCommand(lcd,CURSOR_OFF))
			{
				/* clear LCD at the beginning */
				if (LCD_SUCCESS ==  LCD_sendCommand(lcd,CLEAR_COMMAND))
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

lcd_error_t LCD_sendCommand(lcd_t* lcd , u8_t command)
{
	lcd_error_t error = LCD_SUCCESS;
	GPIO_STATE_ERROR_t gpioError = GPIO_STATE_SUCCESS;
	port_error_t portError = PORT_STATE_SUCCESS;

	/* Instruction Mode RS=0 */
	gpioError = mcal_gpio_pin_write(lcd->lcdControlPort,lcd->lcdRS ,LOW);
	_delay_ms(1);

	/* write data to LCD so RW=0 */
	gpioError = mcal_gpio_pin_write(lcd->lcdControlPort,lcd->lcdRW ,LOW);
	_delay_ms(1);

	/* Enable LCD E=1 */
	gpioError = mcal_gpio_pin_write(lcd->lcdControlPort,lcd->lcdE ,HIGH);
	_delay_ms(1);

	/* REVIEW : Here you should handle if it's 8 bit mode or 4 bit mode
	 * you don't have port write high order  port only so you need to add
	 * this modification to port driver before proceeding
	 */
	/* out the required command to the data bus D0 --> D7 */
	portError = mcal_port_write(lcd->lcdDataPort,command);
	_delay_ms(1);

	 /* disable LCD E=0 */
	gpioError = mcal_gpio_pin_write(lcd->lcdControlPort,lcd->lcdE ,LOW);
	_delay_ms(1);

	error = (gpioError == GPIO_STATE_SUCCESS && portError == PORT_STATE_SUCCESS) ?
			LCD_SUCCESS :  LCD_ERROR;

	return error;
}

lcd_error_t LCD_displayCharacter(u8_t data)
{
	lcd_error_t error = LCD_SUCCESS;

	set_bit(LCD_CTRL_PORT,RS); /* Data Mode RS=1 */
	clr_bit(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	set_bit(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	register (LCD_DATA_PORT) = data; /* out the required data char to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	clr_bit(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	return error;
}

lcd_error_t LCD_displayString(const char *str)
{
	lcd_error_t error = LCD_SUCCESS;
	u8_t i = 0;
	while(str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
	/***************** Another Method ***********************
	while((*Str) != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}
	 *********************************************************/
	return error;
}

lcd_error_t LCD_goToRowColumn(u8_t row,u8_t col)
{
	lcd_error_t error = LCD_SUCCESS;
	u8_t Address;

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
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
	return error;
}

lcd_error_t LCD_displayStringRowColumn(u8_t row,u8_t col,const char *str)
{
	lcd_error_t error = LCD_SUCCESS;
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(str); /* display the string */
	return error;
}

lcd_error_t LCD_intgerToString(int data)
{
	lcd_error_t error = LCD_SUCCESS;
	char buff[16]; /* String to hold the ascii result */
	itoa(data,buff,10); /* 10 for decimal */
	LCD_displayString(buff);
	return error;
}

lcd_error_t LCD_clearScreen(void)
{
	lcd_error_t error = LCD_SUCCESS;
	LCD_sendCommand(CLEAR_COMMAND); //clear display
	return error;
}

