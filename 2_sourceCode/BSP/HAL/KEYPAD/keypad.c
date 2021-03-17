
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

/* configure as your keypad */
s8_t KeyPad [4][4] =
{
		{'7', '8' , '9' , '/' },
		{'4', '5' , '6' , '*' },
		{'1', '2' , '3' , '-' },
		{'A', '0' , '=' , '+' }
};

keypad_error_t hal_keypad_init (keypad_t* keypad)
{
	keypad_error_t error = KEYPAD_SUCCESS;

	/* Initialize all columns GPIOS of keypad as output pins */
	for(int i =0 ; i < (keypad->keypadColsNo) ; i++)
	{
		if(GPIO_STATE_SUCCESS == mcal_gpio_pin_init
				(keypad->keypadPORT,keypad->keypadColumnsGPIOS[i],DIR_OUTPUT))
		{
			/* pin configured */
		}
		else
		{
			error = KEYPAD_FAIL;
		}
	}

	/* Initialize all Rows GPIOS of keypad as input pull up pins */
	for(int i =0 ; i < (keypad->keypadRowsNo) ; i++)
	{
		if(GPIO_STATE_SUCCESS == mcal_gpio_pin_init
				(keypad->keypadPORT,keypad->keypadRowsGPIOS[i],DIR_INPUT_PULLUP))
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

keypad_error_t hal_keypad_getKey(keypad_t* keypad , s8_t* keyPressed)
{
	keypad_error_t error = KEYPAD_SUCCESS;

	s8_t col_loop=keypad->keypadColumnsGPIOS[0];

	/* the following loop clear every column one by one then
       to search for a pressed key in that column then increments
       to the second column to find if key pressed into ... etc*/
	for (u8_t col_count =0 ; col_count<=(keypad->keypadColsNo) ; col_count++)
	{
		/*this line clears the column that is selected by for loop*/
		clr_bit(keypad->keypadPORT+ OFFSET_PORT , keypad->keypadColumnsGPIOS[col_loop] );

		/*this line increment the column number for the next time
          the for loop enters to search the next column*/
		col_loop++; 

		/* delay 5 mills-seconds give user time to press*/
		_delay_ms(5);

		/* the following for loop , loop on the rows to find if any
		   key is pressed on the rows for each column*/
		for (u8_t row_count=(keypad->keypadRowsGPIOS[0]) ; row_count<(keypad->keypadRowsNo) ; row_count++)
		{
			/* if any bit of that row is cleared (means pressed)*/
			if (bit_is_clr(keypad->keypadPIN + OFFSET_PIN ,keypad->keypadRowsGPIOS[row_count]))
			{
				/* this while loop is used to make the program
				   only take the value of the pressed button 
				   as the moment the user leaves the button in
				   order to get one reading only from the push
				   because normally when you press you get a lot
				   of readings because micro-controller is a lot
				   faster than you */
				while(bit_is_clr(keypad->keypadPIN + OFFSET_PIN ,keypad->keypadRowsGPIOS[row_count]))

					/* as soon as we found the keypressed by finding
				   the intersection between the column and row
				   needed we get that value from the array that
				   is declared in configuration */  
					*keyPressed = KeyPad[row_count][col_count];


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
		register(keypad->keypadPORT + OFFSET_PORT)=PORT_ON;
	}
	/*after finishing the search on all the keypad return col_loop into
	  it's initial value which is COL_1 in order to start from beginning
	  when it enters the function again*/
	col_loop = keypad->keypadColumnsGPIOS[0];

	return error;
}
