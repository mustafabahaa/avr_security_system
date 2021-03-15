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

	/* Configure the data port as output port */
	if (PORT_STATE_SUCCESS == 	 mcal_port_init(lcd->lcdDataPort , DIR_PORT_OUTPUT))
	{
		mcal_gpio_pin_init(lcd->lcdControlPort, lcd->lcdE, DIR_OUTPUT);


		register (LCD_CTRL_PORT_DIR) |= (1<<E) | (1<<RS) | (1<<RW); /* Configure the control pins(E,RS,RW) as output pins */

		LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */

		LCD_sendCommand(CURSOR_OFF); /* cursor off */

		LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
	}
	else
	{
		error = LCD_ERROR;
	}

	return error;
}

void LCD_sendCommand(u8_t command)
{
	clr_bit(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
	clr_bit(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	set_bit(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	register (LCD_DATA_PORT) = command; /* out the required command to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	clr_bit(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
}

void LCD_displayCharacter(u8_t data)
{
	set_bit(LCD_CTRL_PORT,RS); /* Data Mode RS=1 */
	clr_bit(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	_delay_ms(1); /* delay for processing Tas = 50ns */
	set_bit(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	register (LCD_DATA_PORT) = data; /* out the required data char to the data bus D0 --> D7 */
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	clr_bit(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
}

void LCD_displayString(const char *str)
{
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
}

void LCD_goToRowColumn(u8_t row,u8_t col)
{
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
}

void LCD_displayStringRowColumn(u8_t row,u8_t col,const char *str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(str); /* display the string */
}

void LCD_intgerToString(int data)
{
	char buff[16]; /* String to hold the ascii result */
	itoa(data,buff,10); /* 10 for decimal */
	LCD_displayString(buff);
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display
}

