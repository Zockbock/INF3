
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LED_H
#define	LED_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define LEDS_C_OFF PORTC &= ~(31 << 1);
#define LEDS_D_OFF PORTD &= ~(15 << 4);
#define LED_B_OFF PORTB &= ~(1);

void init_led(void);
void leds_off(void);

#endif	/* LED_H */

