
/**************************************************************************
 ** This  software  is  in  the  public  domain , furnished "as is", without
 ** technical support,  and with no  warranty, express or implied, as to its
 ** usefulness for any purpose.

 ** keypad.c
 **************************************************************************
 **                              Includes                                **
 *************************************************************************/
#include"keypad.h"
/*************************************************************************/
/*                     Functions Implementation                          */
/*************************************************************************/

keypad_error_t hal_keypad_init (keypad_t* keypad)
{
	keypad_error_t error = KEYPAD_SUCCESS;

	/* Initialize all columns GPIOS of keypad as output pins */
	for(int i =0 ; i < keypad->keypadColsNo ; i++)
	{
		if(GPIO_STATE_SUCCESS == mcal_gpio_pin_init
				(keypad->keypadColsPORT,((u8_t*)keypad->keypadColumnsGPIOS)[i],DIR_OUTPUT))
		{
			if (GPIO_STATE_SUCCESS == mcal_gpio_pin_write
					(keypad->keypadColsPORT,((u8_t*)keypad->keypadColumnsGPIOS)[i],HIGH))
			{
				/* pin configured */
			}
			else
			{
				error = KEYPAD_FAIL;
			}
		}
		else
		{
			error = KEYPAD_FAIL;
		}
	}

	/* Initialize all Rows GPIOS of keypad as input pull up pins */
	for(int i =0 ; i < keypad->keypadRowsNo ; i++)
	{
		if(GPIO_STATE_SUCCESS == mcal_gpio_pin_init
				(keypad->keypadRowsPort,((u8_t*)keypad->keypadRowsGPIOS)[i],DIR_INPUT_PULLUP))
		{
			/* pin configured */
		}
		else
		{
			error = KEYPAD_FAIL;
		}
	}

	return error;
}

keypad_error_t hal_keypad_getKey(keypad_t* keypad , u8_t* keyPressed)
{
	keypad_error_t error = KEYPAD_SUCCESS;
	/* the following loop clear every column one by one then
       to search for a pressed key in that column then increments
       to the second column to find if key pressed into ... etc*/

	for (u8_t col_count = 0 ; col_count < keypad->keypadRowsNo ; col_count++)
	{
		/*this line clears the column that is selected by for loop*/
		clr_bit(keypad->keypadColsPORT+ OFFSET_PORT ,((u8_t*)keypad->keypadColumnsGPIOS)[col_count]);

		//clr_bit(keypad->keypadColsPORT+ OFFSET_PORT , arr[col_count]);

		/* delay 5 mills-seconds give user time to press*/
		delay_ms(5);

		/* the following for loop , loop on the rows to find if any
		   key is pressed on the rows for each column*/
		for (u8_t row_count=0 ; row_count< keypad->keypadColsNo ; row_count++)
		{
			/* if any bit of that row is cleared (means pressed)*/
			if (bit_is_clr(keypad->keypadRowsPort + OFFSET_PIN ,((u8_t*)keypad->keypadRowsGPIOS)[row_count]))
			{
				/* this while loop is used to make the program
				   only take the value of the pressed button 
				   as the moment the user leaves the button in
				   order to get one reading only from the push
				   because normally when you press you get a lot
				   of readings because micro-controller is a lot
				   faster than you */
				while(bit_is_clr(keypad->keypadRowsPort + OFFSET_PIN ,((u8_t*)keypad->keypadRowsGPIOS)[row_count]))

					/* as soon as we found the keypressed by finding
				   the intersection between the column and row
				   needed we get that value from the array that
				   is declared in configuration */  
					*keyPressed = ((s8_t*)keypad->keypadMapping)[(row_count * keypad->keypadRowsNo) + col_count];

				return KEYPAD_SUCCESS;
			}
			/* if no keypressed , then all the bits of the 
			   port is ones meaning 0xff */
			else
			{
				*keyPressed = NO_KEY_PRESSED;
			}
		}
		/*make all the port equal to one again in order to clear
		  only the bit of the column that we need to search for*/
		register(keypad->keypadColsPORT + OFFSET_PORT) = PORT_ON;
	}
	return error;
}
