//project.h

void menu_display(void);				// Displays the main project menu on the LCD

void medicine_time_edit(void);			// Allows the user to configure medicine reminder time

int medicine_rtc_time_equal(void);		// Compares current RTC time with stored medicine reminder time
										// Returns 1 if both times match, otherwise returns 0

void menu_med(void);					// Displays and handles the medicine time editing menu

void menu_rtc(void);					// Displays and handles the RTC date and time editing menu