
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LED_H
#define	LED_H

#include <xc.h> // include processor files - each processor file is guarded. 

#ifndef LEDS_C_OFF
#define LEDS_C_OFF PORTC &= ~(15 << 2);
#endif

#ifndef LEDS_D_OFF
#define LEDS_D_OFF PORTD &= ~(15 << 4);
#endif

#ifndef LED_B_OFF
#define LED_B_OFF PORTB &= ~(1);
#endif

void init_led(void);
void leds_off(void);
void leds_on(void);

#endif	/* LED_H */

