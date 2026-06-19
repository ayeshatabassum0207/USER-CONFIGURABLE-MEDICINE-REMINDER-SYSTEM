//kpm.h

#include "types.h"		// User-defined data type definitions (u32, u8, etc.)

void InitKPM(void);		// Initializes the keypad module by configuring row pins

u32 ColScan(void);		// Checks whether any keypad key is pressed by scanning columns

u32 RowCheck(void);		// Determines the row number of the pressed key

u32 ColCheck(void);		// Determines the column number of the pressed key

u32 KeyScan(void);		// Identifies and returns the value of the pressed key

u32 ReadNum(void);		// Reads a multi-digit number from the keypad until '=' is pressed