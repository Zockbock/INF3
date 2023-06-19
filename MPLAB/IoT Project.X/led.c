
#include <xc.h>
#include <avr/io.h>
#include "led.h"
#include "usart.h"

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

void LEDs_React(float p) { // p = percentage-value
    leds_off();

    if (p <= 11) {
        PORTC |= (1 << 2);
    }
    if ((p > 11) && (p <= 22)) {
        PORTC |= (3 << 2);
    }
    if ((22 < p) && (p <= 33)) {
        PORTC |= (7 << 2);
    }
    if ((33 < p) && (p <= 44)) {
        PORTC |= (15 << 2);
    }
    if ((44 < p) && (p <= 55)) {
        PORTC |= (15 << 2);
        PORTD |= (1 << 4);
    }
    if ((55 < p) && (p <= 66)) {
        PORTC |= (15 << 2);
        PORTD |= (3 << 4);
    }
    if ((66 < p) && (p <= 77)) {
        PORTC |= (15 << 2);
        PORTD |= (7 << 4);
    }
    if ((77 < p) && (p <= 88)) {
        PORTC |= (15 << 2);
        PORTD |= (15 << 4);
    }
    if ((88 < p) && (p <= 100)) {
        PORTC |= (15 << 2);
        PORTD |= (15 << 4);
        PORTB |= 1;
    }
}
