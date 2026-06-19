//rtc.h

#include "types.h"		// User-defined data type definitions (u32, s32, etc.)

void RTC_Init(void);	// Initializes the Real-Time Clock (RTC) peripheral

void GetRTCTimeInfo(s32 *,s32 *,s32 *);	// Reads current RTC time (hours, minutes, seconds)

void DisplayRTCTime(u32,u32,u32);		// Displays time information on the LCD

void GetRTCDateInfo(s32 *,s32 *,s32 *);	// Reads current RTC date (day, month, year)

void DisplayRTCDate(u32,u32,u32);		// Displays date information on the LCD

void SetRTCTimeInfo(u32,u32,u32);		// Sets RTC time (hours, minutes, seconds)

void SetRTCDateInfo(u32,u32,u32);		// Sets RTC date (day, month, year)

void GetRTCDay(s32 *);					// Reads the current day of the week from RTC

void DisplayRTCDay(u32);				// Displays the current day of the week on the LCD

void SetRTCDay(u32);					// Sets the day of the week in RTC

void initial_start_rtc(void);			// Performs initial RTC configuration and startup