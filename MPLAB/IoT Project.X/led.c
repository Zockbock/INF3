
#include <xc.h>
#include <avr/io.h>
#include "led.h"

#define LEDS_C_OFF PORTC &= ~(15 << 2);
#define LEDS_D_OFF PORTD &= ~(15 << 4);
#define LED_B_OFF PORTB &= ~(1);

void leds_off(void) {
    LEDS_C_OFF;
    LEDS_D_OFF;
    LED_B_OFF;
}

void init_led(void) {
    //LED
    DDRC |= (1 << DDC2); // Configure PC2 as Output
    DDRC |= (1 << DDC3); // Configure PC3 as Output
    DDRC |= (1 << DDC4); // Configure PC4 as Output
    DDRC |= (1 << DDC5); // Configure PC5 as Output
    DDRD |= (1 << DDD4); // Configure PD4 as Output
    DDRD |= (1 << DDD5); // Configure PD5 as Output
    DDRD |= (1 << DDD6); // Configure PD6 as Output
    DDRD |= (1 << DDD7); // Configure PD7 as Output
    DDRB |= (1 << DDB0); // Configure PB0 as Output

    leds_on();
}

void leds_on(void) {
    PORTC |= (15 << 2);
    PORTD |= (15 << 4);
    PORTB |= 1;
}