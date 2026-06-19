//project.c
#include <lpc21xx.h>		// LPC21xx register definitions

#define BUZZER 4			// Buzzer connected to P0.4

#include"delay.h"			// Delay function declarations

#include "LCD.h"			// LCD function declarations

#include "project.h"		// Project-specific function declarations

#include "KPM.h"			// Keypad function declarations

extern int mhr,mmin,msec,hour,min,sec,date,month,year,day;	// Global variables for medicine and RTC time/date

extern int int2;			// External interrupt flag for medicine acknowledgment

extern volatile int flag;	// Global status flag

int medicine_rtc_time_equal(void)
{
 if((mhr==hour)&&(mmin==min)&&(msec==sec))//&&(msec==sec))	// Compare medicine schedule with current RTC time
 {
 //flag=2;
  return 1;		// Return true when both times match
 }
 else
 return 0;		// Return false when times do not match
}

/*void buzzeron(void)
{
 IOSET0=1<<BUZZER;
 CmdLCD (0X01);
 StrLCD("PLZ Take Med!!");
 if(int2==1)
 {
  buzzeroff();
 }
 delay_s(60);
 int2==0;
}*/

/*void buzzeroff(void)
{
 IOCLR0=1<<BUZZER;
 CmdLCD(0X01);
 StrLCD("med taken!");
 delay_s(1);
 CmdLCD(0X01);
}*/

void rtc_time_edit()
{
 /*CmdLCD (0X01);
 StrLCD("Enterhh:min:sec");
 CmdLCD (0XC0);
 hour=ReadNum();
 CharLCD(':');
 min=ReadNum();
 CharLCD(':');
 sec=ReadNum();
 delay_ms(100);
 CmdLCD (0X01);*/

	//menu rtc edit

	CmdLCD (0X01);		// Clear LCD

	menu_rtc();			// Open RTC edit menu

/* StrLCD("Enter dd/mm/year");
 CmdLCD (0XC0);
 date=ReadNum();
 CharLCD('/');
 month=ReadNum();
 CharLCD('/');
 year=ReadNum();*/

	CmdLCD(0X01);		// Clear LCD

	StrLCD("RTC UPDATED!");		// Display RTC update confirmation message

	delay_s(1);			// Wait for 1 second

	CmdLCD(0X01);		// Clear LCD

	SetRTCTimeInfo(hour,min,sec);		// Update RTC time

	SetRTCDateInfo(date,month,year);	// Update RTC date

	SetRTCDay(day);					// Update RTC day

	CmdLCD(0X01);					// Clear LCD
}

void menu_display()
{
 char op;		// Variable to store selected menu option

 CmdLCD(0X01);		// Clear LCD

 CmdLCD (0X80);		// Move cursor to first line

 StrLCD("1.med_E 2.RTC_E");		// Display menu options

 CmdLCD(0XC0);		// Move cursor to second line

 StrLCD("3.exit enter:");		// Display exit option

 //delay_s(1);

 //CmdLCD (0X01);

 //StrLCD("Enter choice:");

 op=KeyScan();		// Read user selection from keypad

 switch(op)
 {
  case '1':medicine_time_edit();	// Enter medicine schedule edit menu

         break;

  case '2':rtc_time_edit();			// Enter RTC edit menu

         break;

  default: CmdLCD(0X01);			// Clear LCD for any other key

          break;
 }
}

void medicine_time_edit(void)
{
 CmdLCD (0X01);		// Clear LCD

 StrLCD("IN MED TIME EDIT");		// Display medicine edit mode message

 delay_s(1);		// Wait for 1 second

 CmdLCD (0x01);		// Clear LCD

 /*
 StrLCD("Enter hh:mm:ss");
 delay_s(1);
 CmdLCD (0XC0);
 mhr=ReadNum();
 //CharLCD(mhr / 10+48);
 //CharLCD(mhr%10+48);
 CharLCD(':');
 mmin=ReadNum();
 //CharLCD(mmin/10+48);
 //CharLCD(mmin%10+48);
 CharLCD(':');
 msec=ReadNum();
 //CharLCD(msec/10+48);
 //CharLCD(msec%10+48);
 delay_s(1);
 */

 //menu based for med

 menu_med();		// Open medicine schedule edit menu

 CmdLCD (0X01);

 StrLCD("med time set!");		// Display confirmation message

 delay_s(1);

 CmdLCD(0X01);		// Clear LCD
}

void menu_med(void)
{
 char num;		// Variable to store selected menu option

 //CmdLCD(0X01);

 while(1)
 {
  CmdLCD(0X01);		// Clear LCD

  StrLCD("1.H 2.M 3.S 4.E");		// Display medicine time menu

  CmdLCD(0XC0);		// Move cursor to second line

  StrLCD("Enter choice:");

  num=KeyScan();	// Read keypad input

  CmdLCD(0x01);		// Clear LCD

  switch(num)
  {
   case '1':StrLCD("Enter hr(0-23):");

          CmdLCD(0XC0);

          mhr=ReadNum();		// Read medicine hour

		  LABEL1:if((mhr>24)||(mhr<0))
		  {
		   CmdLCD(0X01);

		   StrLCD("Error hours!");

		   delay_s(1);

		   CmdLCD(0X01);

		   StrLCD("Enter hr (0-23)");

		   CmdLCD(0XC0);

		   mhr=ReadNum();

		   if((mhr>23)||(mhr<0))
		   {
		    goto LABEL1;		// Repeat until valid hour is entered
		   }
		   }

		  break;

   case '2':StrLCD("Enter min:(0-59)");

           CmdLCD(0XC0);

           mmin=ReadNum();		// Read medicine minutes

		   LABEL2:if((mmin>59)||(mmin<0))
		   {
		    CmdLCD(0X01);

		    StrLCD("Error min!");

		    delay_s(1);

		    CmdLCD(0X01);

		    StrLCD("Enter min 0-59");

		    CmdLCD(0XC0);

		    mmin=ReadNum();

		    if((mmin>59)||(mmin<0))
		    {
		     goto LABEL2;		// Repeat until valid minutes are entered
		    }
		   }

		   break;

  case '3':StrLCD("Enter sec:(0-59)");

         CmdLCD(0XC0);

         msec=ReadNum();		// Read medicine seconds

		 LABEL3:if((msec>59)||(msec<0))
		  {
		   CmdLCD(0X01);

		   StrLCD("Error sec!");

		   delay_s(1);

		   CmdLCD(0X01);

		   StrLCD("Enter sec 0-59");

		   CmdLCD(0XC0);

		   msec=ReadNum();

		   if((msec>59)||(msec<0))
		   {
		    goto LABEL3;		// Repeat until valid seconds are entered
		   }

		 break;

  case '4':return;		// Exit medicine menu

  }
 }
}
}

void menu_rtc(void)
{
 char num;		// Variable to store selected menu option

 while(1)
 {
  CmdLCD(0X01);		// Clear LCD

  StrLCD("1.H 2.M 3.S 4.D");		// Display RTC menu options

  CmdLCD(0XC0);

  StrLCD("5.M 6.Y 7.D 8.E");

  num=KeyScan();		// Read keypad input

  CmdLCD(0X01);

  switch(num)
  {
  /*case 1:

  case 2:
  case 3:*/

  case '1':StrLCD("Enter hr(0-23):");

          CmdLCD(0XC0);

          hour=ReadNum();		// Read hour value

		  LABEL1:if((hour>23)||(hour<0))
		  {
		   CmdLCD(0X01);

		   StrLCD("Error hours!");

		   delay_s(1);

		   CmdLCD(0X01);

		   StrLCD("Enter hr 0-23");

		   hour=ReadNum();

		   if((hour>23)||(hour<0))
		   {
		    goto LABEL1;		// Repeat until valid hour is entered
		   }
		   }

		  break;

   case '2':StrLCD("Enter min:(0-59)");

           CmdLCD(0XC0);

           min=ReadNum();		// Read minute value

		   LABEL2:if((min>59)||(min<0))
		   {
		    CmdLCD(0X01);

		    StrLCD("Error min!");

		    delay_s(1);

		    CmdLCD(0X01);

		    StrLCD("Enter min 0-59");

		    CmdLCD(0XC0);

		    min=ReadNum();

		    if((min>59)||(min<0))
		    {
		     goto LABEL2;		// Repeat until valid minute is entered
		    }
		   }

		   break;

  case '3':StrLCD("Enter sec:(0-59)");

         CmdLCD(0XC0);

         sec=ReadNum();		// Read second value

		 LABEL3:if((sec>59)||(sec<0))
		  {
		   CmdLCD(0X01);

		   StrLCD("Error sec!");

		   delay_s(1);

		   CmdLCD(0X01);

		   StrLCD("Enter sec 0-59");

		   CmdLCD(0XC0);

		   sec=ReadNum();

		   if((sec>59)||(sec<0))
		   {
		    goto LABEL3;		// Repeat until valid second is entered
		   }
		  }

		 break;

  case '4':StrLCD("Enter date(1-31):");

         CmdLCD(0XC0);

		 date=ReadNum();		// Read date value

		 CmdLCD(0X10);

		 LABEL4:if((date>31)||(date<1))
		  {
		   CmdLCD(0X01);

		   StrLCD("Error date!");

		   delay_s(1);

		   CmdLCD(0X01);

		   StrLCD("Enter date 1-31");

		   CmdLCD(0XC0);

		   date=ReadNum();

		   if((date>31)||(date<1))
		   {
		    goto LABEL4;		// Repeat until valid date is entered
		   }
		  }

		 break;

  case '5':StrLCD("Enter M(1-12):");

         CmdLCD(0XC0);

		 month=ReadNum();		// Read month value

		 CmdLCD(0X10);

		 LABEL5:if((month>12)||(month<1))
		  {
		   CmdLCD(0X01);

		   StrLCD("Error month!");

		   delay_s(1);

		   CmdLCD(0X01);

		   StrLCD("Enter M(1-12)");

		   CmdLCD(0XC0);

		   month=ReadNum();

		   if((month>12)||(month<1))
		   {
		    goto LABEL5;		// Repeat until valid month is entered
		   }
		   }

		 break;

  case '6':StrLCD("Enter y2000-3000");

         CmdLCD(0XC0);

		 year=ReadNum();		// Read year value

		 CmdLCD(0X10);

		 LABEL6:if((year>3000)||(year<2000))
		  {
		   CmdLCD(0X01);

		   StrLCD("Error year!");

		   delay_s(1);

		   CmdLCD(0X01);

		   StrLCD("Enter y2000-3000");

		   CmdLCD(0XC0);

		   year=ReadNum();

		   if((year>3000)||(year<2000))
		   {
		    goto LABEL6;		// Repeat until valid year is entered
		   }
		   }

		 break;

  case '7':StrLCD("Enter day(0-6):");

         CmdLCD(0XC0);

		 day=ReadNum();		// Read day value

		 CmdLCD(0X10);

		 LABEL7:if((day>6)||(day<0))
		  {
		   CmdLCD(0X01);

		   StrLCD("Error day!");

		   delay_s(1);

		   CmdLCD(0X01);

		   StrLCD("Enter day 0-6");

		   CmdLCD(0XC0);

		   day=ReadNum();

		   if((day>6)||(day<0))
		   {
		    goto LABEL7;		// Repeat until valid day is entered
		   }
		  }

		 break;

  case '8':return;		// Exit RTC menu
 }
 }
}