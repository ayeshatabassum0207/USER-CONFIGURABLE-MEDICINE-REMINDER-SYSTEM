//LCD.h
#include "types.h"		// User-defined data type definitions (u8, s8, u32, s32, f32, etc.)

void WriteLCD(u8 data);			// Low-level function to write data or command to LCD

void CmdLCD(u8 cmd);			// Sends a command byte to the LCD

void CharLCD(u8 ascii);			// Displays a single ASCII character on the LCD

void InitLCD(void);				// Initializes the LCD module

void StrLCD(s8* p);				// Displays a null-terminated string on the LCD

void U32LCD(u32 n);				// Displays an unsigned 32-bit integer on the LCD

void S32LCD(s32 n);				// Displays a signed 32-bit integer on the LCD

void F32LCD(f32 fnum, u8 nDP);	// Displays a floating-point number on the LCD
								// nDP specifies the number of digits after the decimal point

void HEXLCD(u32 n);				// Displays a number in hexadecimal format on the LCD

void BinLCD(u32 n, u8 nbd);		// Displays a number in binary format on the LCD
								// nbd specifies the number of bits to display

void BuildCGRAM(u8* p, u8 nb);	// Stores custom character patterns in LCD CGRAM