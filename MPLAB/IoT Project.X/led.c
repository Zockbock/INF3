
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

/**
void LEDs_React(int p) {  // p = percentage-value
    leds_off();
    switch(p){
        case p <= 11:
            DDRC |= (1 << DDC2);
            break;
        case 11 < p <= 22:
            DDRC |= (3 << DDC2);
            break;
        case 22 < p <= 33:
            DDRC |= (7 << DDC2);
            break;
        case 33 < p <= 44:
            DDRC |= (15 << DDC2);
            break;
        case 44 < p <= 55:
            DDRC |= (15 << DDC2);
            DDRD |= (1 << DDD4);
            break;
        case 55 < p <= 66:
            DDRC |= (15 << DDC2);
            DDRD |= (3 << DDD4);
            break;
        case 66 < p <= 77:
            DDRC |= (15 << DDC2);
            DDRD |= (7 << DDD4);
            break;
        case 77 < p <= 88:
            DDRC |= (15 << DDC2);
            DDRD |= (15 << DDD4);
            break;
        case 88 < p <= 100:
            DDRC |= (15 << DDC2);
            DDRD |= (15 << DDD4);
            DDRB |= (1 << DDB0);
            break;
        default:
            break;
    }
}
 **/ 
