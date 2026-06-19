//main.c
#include<lpc21xx.h>
#include "kpm.h"
#define BUZZER 4
#include "project.h"

//lcd headers
#include "LCD_defines.h"
#include "LCD.h"
//rtc headers
#include "rtc_defines.h"
#include "rtc.h"
#include "interrupt.h"
#define _LPC2148

s32 hour,min,sec,date,month,year,day;
// Main function
int mhr,mmin,msec;
volatile int flag;
//int int2=0;
//int m_count[2];

int main()
{
 int i;
	
	
// Initialize RTC
	RTC_Init(); 	
	InitLCD();
	InitKPM();

	//interrupt_initialization();
 	initial_start_rtc();
	// Initialize the LCD
	
	
	interrupt_initialization();
	IODIR0|=1<<BUZZER;
	
/*	SetRTCTimeInfo(11,0,0);
	SetRTCDateInfo(14,3,2026);
	SetRTCDay(0);*/
	while (1) 
	{
	if(flag==0)
	 {

        // Get and display the current time info on LCD

				GetRTCTimeInfo(&hour,&min,&sec);
				DisplayRTCTime(hour,min,sec);

				// Get and display the current date info on LCD

				GetRTCDateInfo(&date,&month,&year);

				DisplayRTCDate(date,month,year);

				// Get and display the current day info on LCD

				GetRTCDay(&day);

				DisplayRTCDay(day);

	}
	if(flag==1)
	{
		 menu_display();
		 flag=0;
	}
	if(medicine_rtc_time_equal())
	{
    IOSET0 = 1 << BUZZER;           // Turn Buzzer ON
    CmdLCD(0x01);
    StrLCD("PLZ Take Med!!");

    	while(1)
		{
		GetRTCTimeInfo(&hour,&min,&sec);
		if((min!=mmin)&&(sec==msec))
		{
			 IOCLR0 = 1 << BUZZER;           // Turn Buzzer OFF (either after 1 min or break)
    		CmdLCD(0x01);                   // Clear message
			StrLCD("Med skipped");
			delay_s(2);
			CmdLCD(0X01);
    		flag =  0; 
            break; 
		}
        if ((flag == 2)) 
		{
			IOCLR0 = 1 << BUZZER;           // Turn Buzzer OFF (either after 1 min or break)
    		CmdLCD(0x01); 
			StrLCD("Med taken"); 
			delay_s(2);
			CmdLCD(0X01);                 // Clear message
    		flag =  0; 
            break;                  // Exit loop immediately to stop buzzer
        }
		}
        delay_ms(10);               // Wait 10ms before checking again
    //}

    /*IOCLR0 = 1 << BUZZER;           // Turn Buzzer OFF (either after 1 min or break)
    CmdLCD(0x01);                   // Clear message
    flag =  0;*/                       // Reset flag to return to normal RTC display
    }

	}

}						 