//LCD.c				// LCD driver source file

#include<lpc21xx.h>			// LPC21xx register definitions

#include "LCD_defines.h"	// LCD command and pin definitions

#include "types.h"			// User-defined data types

#include "defines.h"		// Bit manipulation macros

#include "delay.h"			// Delay function declarations

void WriteLCD(u8 data)
{

	SCLRBIT(IOCLR0,RW);//RW=0, write operation

	WBYTE(IOPIN0,LCD_DATA,data);	// Place command/data byte on LCD data pins

	SSETBIT(IOSET0,EN);//EN=1		// Set EN pin HIGH to latch data

	delay_us(1);					// Short enable pulse width delay

	SCLRBIT(IOCLR0,EN);//EN=0		// Set EN pin LOW to complete write operation

	delay_ms(2);//internal process	// Wait for LCD internal processing
}

void CmdLCD(u8 cmd)
{

	SCLRBIT(IOCLR0,RS);//RS=0, command reg selected	// Select command register

	WriteLCD(cmd);									// Send command to LCD
}

void CharLCD(u8 ascii)
{

	SSETBIT(IOSET0,RS);//RS=1, data reg selected	// Select data register

	WriteLCD(ascii);								// Send character to LCD
}

void InitLCD(void)
{

	WBYTE(IODIR0,LCD_DATA,255); //P0.8 to P0.15 as outputs	// Configure LCD data pins as outputs

	SETBIT(IODIR0,RS);//p0.16 as output		// Configure RS pin as output

	SETBIT(IODIR0,RW);//p0.17 as output		// Configure RW pin as output

	SETBIT(IODIR0,EN);//p0.18 as output		// Configure EN pin as output


	delay_ms(15);						// Wait for LCD power stabilization

	CmdLCD(MODE_8BIT_1LINE);			// Initialization sequence step 1

	delay_ms(5);

	CmdLCD(MODE_8BIT_1LINE);			// Initialization sequence step 2

	delay_us(100);

	CmdLCD(MODE_8BIT_1LINE);			// Initialization sequence step 3


	CmdLCD(MODE_8BIT_2LINE);			// Configure LCD for 8-bit, 2-line mode

	CmdLCD(DISP_ON_CUR_BLINK);			// Turn display ON with cursor blink

	CmdLCD(CLEAR_LCD);					// Clear LCD display

	CmdLCD(SHIFT_CUR_RIGHT);			// Move cursor to the right after each write
}


void StrLCD(s8* p)
{

	while(*p)

	CharLCD(*p++);						// Display string until null character is reached
}


void U32LCD(u32 n)
{

	u8 a[10];							// Buffer to store digits

	s32 i=0;							// Index variable

	if(n==0)
	{

		CharLCD('0');					// Display zero directly
	}

	else
	{

		while(n)
		{

			a[i++]=(n%10)+48;			// Convert digit to ASCII and store

			n/=10;						// Remove least significant digit
		}

		for(--i;i>=0;i--)

		CharLCD(a[i]);					// Display digits in correct order
	}


}


void S32LCD(s32 n)
{

	if(n<0)
	{

		CharLCD('-');					// Display negative sign

		n=-n;							// Convert number to positive

		U32LCD(n);						// Display magnitude
	}


}

void F32LCD(f32 fnum, u8 nDP)
{

	u32 n;								// Variable to store integer part

	s32 i;								// Loop counter

	if(fnum<0)
	{

		CharLCD('-');					// Display negative sign
	}

	n=fnum;								// Extract integer part

	U32LCD(n);							// Display integer part

	CharLCD('.');						// Display decimal point

	for(i=0; i<nDP; i++)
	{

		fnum=(fnum-n)*10;				// Shift next fractional digit

		n=fnum;							// Extract current digit

		CharLCD(n+48);					// Convert digit to ASCII and display
	}


}


void HEXLCD(u32 n)
{

	u8 a[8],rem;						// Buffer and remainder variable

	s32 i=0;							// Index variable

	if(n==0)
	{

		CharLCD('0');					// Display zero directly
	}

	else
	{

		while(n)
		{

			rem =n%16;					// Extract hexadecimal digit

			(rem<10)?(rem+=48):(rem+=55);	// Convert digit to ASCII

			a[i++]=rem;				// Store converted digit

			n/=16;						// Remove least significant digit
		}

		for(--i; i>=0; i--)
		{

			CharLCD(a[i]);				// Display digits in correct order
		}
	}
}


void BinLCD(u32 n, u8 nbd)
{

	s32 i;								// Loop counter

	for(i=(nbd-1); i>=0; i--)
	{

		CharLCD(((n>>i)&1)+48);			// Display each bit as ASCII '0' or '1'
	}
}

void BuildCGRAM(u8* p, u8 nb)
{

	s32 i;								// Loop counter

	CmdLCD(GOTO_CGRAM);				// Set LCD address pointer to CGRAM

	for(i=0; i<=nb; i++)
	{

		CharLCD(p[i]);					// Load custom character data into CGRAM
	}

	CmdLCD(GOTO_LINE1_POS0);			// Return cursor to first line, first position
}