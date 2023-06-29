#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "button.h"
#include "led.h"
#include "adc.h"
#include "usart.h"
#include "display.h"
#include "string.h"

void init_button(void) {

    DDRB &= ~(1 << DDB1); // Configure PB1 as Input BTN2
    PORTB |= (1 << DDB1);

    // enable interrupts on BTN
    PCICR |= 1 << PCIE0;
    PCMSK0 |= 1 << PCINT1;

//    TIMSK0 |= (1 << TOIE0); //allow overflow interrupt for timer0

    sei();
}

ISR(PCINT0_vect) {
    //    TCCR0B |= (1 << CS02) | (1 << CS00); //set prescaler to 1024 and start

    if (!(PINB & (1 << PB1))) {
        ADC_ToggleMux();
        USART_Transmit(255);
        _delay_ms(100);
    }
}

//ISR(TIMER0_OVF_vect) {
//    TCCR0B &= ~((1 << CS00) | (1 << CS01) | (1 << CS02)); //stop timer
//    if (!(PINB & (1 << PB1))) {
//        ADC_ToggleMux();
//        USART_Transmit(255);
//        //        _delay_ms(100);
//    }
//}

void ADC_ToggleMux(void) {

    ADCSRA &= ~(1 << ADEN); // ADC disable

    if (ADMUX & (1 << MUX0)) {
        // switch to microphone
        ADMUX &= ~(1 << MUX0); // select ADC0 as input
    } else {
        // switch to photoresistor 
        ADMUX |= (1 << MUX0); // select ADC1 as input
    }

    ADCSRA |= (1 << ADEN); // ADC enable
    ADCSRA |= (1 << ADSC); // start first conversion

    Draw_CurrentMode(getCurrentMode());
}

//#include <xc.h>
//#include <avr/io.h>
//#include <avr/interrupt.h>
//#include "button.h"
//#include "led.h"
//#include "adc.h"
//#include "usart.h"
//#include "display.h"
//#include "string.h"
//
//#define TOGGLE_INT PCICR ^= (1 << PCIE0);
//
//void init_button(void) {
//
//    DDRB &= ~(1 << DDB1); // Configure PB1 as Input BTN2
//    PORTB |= (1 << DDB1);
//
//    // enable interrupts on BTN
//    PCICR |= 1 << PCIE0;
//    PCMSK0 |= 1 << PCINT1;
//
//
//    sei();
//}
//
//ISR(PCINT0_vect) {
//    TOGGLE_INT;
////    counterB = 0;
//    for(uint16_t i = 0; i < 200; i++){
//        
//    }
//    if (!(PINB & (1 << PB1))) {
//        ADC_ToggleMux();
//        USART_Transmit(255);
//    }
//    TOGGLE_INT;
//}
//
//void ADC_ToggleMux(void) {
//
//    ADCSRA &= ~(1 << ADEN); // ADC disable
//
//    if (ADMUX & (1 << MUX0)) {
//        // switch to microphone
////        leds_on();
//        ADMUX &= ~(1 << MUX0); // select ADC0 as input
//    } else {
//        // switch to photoresistor 
////        leds_off();
//        ADMUX |= (1 << MUX0); // select ADC1 as input
//    }
//
//    ADCSRA |= (1 << ADEN); // ADC enable
//    ADCSRA |= (1 << ADSC); // start first conversion
//    
//    Draw_CurrentMode(getCurrentMode());
//}