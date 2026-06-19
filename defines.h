//#ifndef __DEFINES_H__		// Header guard start (currently commented out)

//#define __DEFINES_H__		// Header guard macro definition (currently commented out)


#define SETBIT(WORD,BITPOS) (WORD|=1<<BITPOS)		// Set the bit at BITPOS in WORD

#define CLRBIT(WORD,BITPOS) (WORD&=~(1<<BITPOS))	// Clear the bit at BITPOS in WORD

#define SSETBIT(WORD,BITPOS) (WORD=1<<BITPOS)		// Set only the specified bit and clear all other bits in WORD

#define SCLRBIT(WORD,BITPOS) (WORD=1<<BITPOS)		// Assign WORD with only the specified bit position set

#define CPLBIT(WORD,BITPOS) (WORD^=1<<BITPOS)		// Toggle the bit at BITPOS in WORD


#define WBYTE(WORD,SBITPOS,BYTE) WORD=(WORD&~(0XFF<<SBITPOS))|(BYTE<<SBITPOS)	// Write a byte value into WORD starting at SBITPOS


#define WNIBBLE(WORD,SBITPOS,NIBBLE) WORD=(WORD&~(0XF<<SBITPOS))|(NIBBLE<<SBITPOS)	// Write a 4-bit nibble into WORD starting at SBITPOS


#define WBIT(WORD,BITPOS,BIT) WORD=(WORD&~(1<<BITPOS))|(BIT<<BITPOS)	// Write BIT value (0 or 1) to BITPOS in WORD


#define RBIT(WORD,BITPOS) ((WORD>>BITPOS)&1)		// Read the bit value at BITPOS

#define RNIBBLE(WORD,SBITPOS) ((WORD>>SBITPOS)&15)	// Read a 4-bit nibble from WORD starting at SBITPOS

#define RBYTE(WORD,SBITPOS) ((WORD>>SBITPOS)&255)	// Read a byte from WORD starting at SBITPOS


#define READWRITEBIT(DWORD,DBIT,SBIT) DWORD=(DWORD&~(1<<DBIT))|(((DWORD>>SBIT)&1)<<DBIT)	// Copy the bit from SBIT position to DBIT position within the same variable


#define READWRITEBIT2(DWORD,DBIT,SWORD,SBIT) DWORD=(DWORD&~(1<<DBIT))|(((SWORD>>SBIT)&1)<<DBIT)	// Copy the bit from SWORD at SBIT position to DWORD at DBIT position


//#endif		// Header guard end (currently commented out)