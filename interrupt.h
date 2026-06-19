
//interrupt.h		// Header file for external interrupt function declarations

#include "interrupt_defines.h"		// External interrupt register and bit definitions

void interrupt_initialization(void);	// Configures and enables external interrupts

void eint0_isr(void) __irq;			// Interrupt Service Routine for External Interrupt 0 (EINT0)

void eint1_isr(void) __irq;			// Interrupt Service Routine for External Interrupt 1 (EINT1)