


#include"keypad.h"
	
u8_t getKey()
{
	/* the following loop clear every column one by one then
       to search for a pressed key in that column then increments
       to the second column to find if key pressed into ... etc*/
	for (u8_t col_count =0 ; col_count<=COL_NUMBERS ; col_count++)
	{
		
		/*this line clears the column that is selected by for loop*/
		clr_bit(KEYPAD_PORT,col_loop);
		
		
		/*this line increment the column number for the next time
          the for loop enters to search the next column*/
		col_loop++; 
		
		/* delay 5 mills-seconds give user time to press*/
	    _delay_ms(5);
		
		
		/* the following for loop , loop on the rows to find if any
		   key is pressed on the rows for each column*/
		for (u8_t row_count=ROW_1;row_count<ROW_NUMBERS;row_count++)
		{
			/* if any bit of that row is cleared (means pressed)*/
			if (bit_is_clear(KEYPAD_PIN,row_count))
			{
				/* this while loop is used to make the program
				   only take the value of the pressed button 
				   as the moment the user leaves the button in
				   order to get one reading only from the push
				   because normally when you press you get a lot
				   of readings because micro-controller is a lot
				   faster than you */
				while(bit_is_clear(KEYPAD_PIN,row_count))
					
				/* as soon as we found the keypressed by finding
				   the intersection between the column and row
				   needed we get that value from the array that
				   is declared in configuration */  
				keypressed = KeyPad[row_count][col_count];
				
				return keypressed;
		
			}
			/* if no keypressed , then all the bits of the 
			   port is ones meaning 0xff */
			else {keypressed = NO_KEY_PRESSED;}		
		}
		/*make all the port equal to one again in order to clear
		  only the bit of the column that we need to search for*/
	    KEYPAD_PORT=ALL_PORT_ON;	
	}
	/*after finishing the search on all the keypad return col_loop into
	  it's initial value which is COL_1 in order to start from beginning
	  when it enters the function again*/
	col_loop = COL_1;
	
	
	return keypressed;
}
