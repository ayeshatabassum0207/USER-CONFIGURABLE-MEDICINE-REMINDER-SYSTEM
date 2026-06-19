//kpm.c
#include <lpc21xx.h>			// LPC21xx register definitions

#include "types.h"				// User-defined data type definitions

#include "defines.h"			// Bit manipulation macros


#include "kpm_defines.h"		// Keypad row and column pin definitions

#include "LCD.h"				// LCD function declarations

#include "LCD_defines.h"		// LCD command definitions

/*u32 kpmLUT[4][4]={{1,2,3,4},

									{5,6,7,8},

									{9,10,11,12},

									{13,14,15,16}};*/	// Alternative keypad lookup table using numeric values

u8 kpmLUT[4][4]={{'1','2','3','/'},		// Row 0 keypad mapping
									{'4','5','6','*'},	// Row 1 keypad mapping
									{'7','8','9','-'},	// Row 2 keypad mapping
									{'C','0','+','='}};	// Row 3 keypad mapping

void InitKPM(void)

{

	WNIBBLE(IODIR1,ROW0,15);	// Configure keypad row pins as outputs

}


u32 ColScan(void)

{

	return((RNIBBLE(IOPIN1,COL0)<15)?0:1);	// Check if any key is pressed by scanning column inputs

}

u32 RowCheck(void)

{

	u32 rno;	// Variable to store detected row number

	for(rno=0; rno<4; rno++)

	{

		WNIBBLE(IOPIN1,ROW0,~(1<<rno));	// Drive one row LOW at a time

		if(ColScan()==0)				// Check if a key press is detected in current row

		{

			break;						// Exit loop when active row is found

		}

	}

	//make rows as default

	WNIBBLE(IOPIN1,ROW0,0x0);			// Reset all rows to default state

	return rno;						// Return detected row number

}

u32 ColCheck(void)

{

	u32 cno;	// Variable to store detected column number

	for(cno=0; cno<4; cno++)

	{

		if(RBIT(IOPIN1,(COL0+cno))==0)	// Check each column pin for active LOW state

		{

			break;						// Exit loop when active column is found

		}

	}

	return cno;						// Return detected column number

}


u32 KeyScan(void)

{

	u32 rno,cno,keyv;	// Variables for row number, column number, and key value

	//wait for switch press

	while(ColScan());	// Wait until a key is pressed

	//find the row_no

	rno=RowCheck();		// Determine row number of pressed key

	//find the col_no

	cno=ColCheck();		// Determine column number of pressed key

	//get the key value using kpmLUT

	keyv=kpmLUT[rno][cno];	// Retrieve key value from lookup table

	//wait for switch release

	while(!ColScan());	// Wait until key is released

	return keyv;		// Return detected key value

}


u32 ReadNum(void)

{

	u8 key;			// Variable to store pressed key

	u32 sum=0;		// Variable to accumulate entered number

	while(1)

	{

		key=KeyScan();	// Read keypad input

		if(key>='0'&&key<='9')	// Check if pressed key is a numeric digit

		{

			CharLCD(key);	// Display digit on LCD

			sum=(sum*10)+(key-'0');	// Convert ASCII digit to numeric value and append
		}

	    // Handle Backspace (The '/' key)
        else if(key == '/')
        {
            if(sum > 0)
            {
                sum = sum / 10;      // Remove the last entered digit from the number

                // LCD Visual Backspace:
                CmdLCD(0x10);        // Move cursor one position to the left

                CharLCD(' ');        // Overwrite previous digit with a blank space

                CmdLCD(0x10);        // Move cursor back to erased position
            }
        }

		else if(key=='=')	// Check for end-of-input key

		{

			break;			// Exit input loop

		}

	}

	return sum;			// Return entered number

}