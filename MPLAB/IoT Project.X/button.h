
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef BUTTON_H
#define	BUTTON_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <avr/interrupt.h>
#include "led.h"
#include "adc.h"

void init_button(void);
void ADC_ToggleMux(void);

#endif	/* BUTTON_H */

