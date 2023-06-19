#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "button.h"
#include "led.h"
#include "adc.h"
#include "usart.h"

void init_button(void) {

    DDRB &= ~(1 << DDB1); // Configure PB1 as Input BTN2
    PORTB |= (1 << DDB1);

    // enable interrupts on BTN
    PCICR |= 1 << PCIE0;
    PCMSK0 |= 1 << PCINT1;


    sei();
}

ISR(PCINT0_vect) {
    //leds_off();

    if (!(PINB & (1 << PB1))) {

        ADC_ToggleMux();
    }
}

void ADC_ToggleMux(void) {

    ADCSRA &= ~(1 << ADEN); // ADC disable

//    ADMUX |= (1 << REFS0);
//    ADMUX &= ~(1 << REFS1); //set voltage Reference to AVCC 5V

    if (ADMUX & (1 << MUX0)) {
        // switch to microphone
        ADMUX &= ~(1 << MUX0); // select ADC0 as input
    } else {
        // switch to photoresistor 
        ADMUX |= (1 << MUX0); // select ADC1 as input
    }

//    ADMUX &= ~(1 << MUX1);
//    ADMUX &= ~(1 << MUX2);
//    ADMUX &= ~(1 << MUX3);
//
//    ADCSRB &= ~(1 << ADTS0);
//    ADCSRB &= ~(1 << ADTS1);
//    ADCSRB &= ~(1 << ADTS2); //set to free running mode/
//    // or ADCSRB = 0;
//
//    ADCSRA |= (1 << ADPS2);
//    ADCSRA |= (1 << ADPS1);
//    ADCSRA |= (1 << ADPS0); // set ADC prescaler to 128 for 125 kHz
//
//    ADCSRA |= (1 << ADIE); // enable ADC interrrupt
//    ADCSRA |= (1 << ADATE); // enable ADC Auto Trigger

    ADCSRA |= (1 << ADEN); // ADC enable
    ADCSRA |= (1 << ADSC); // start first conversion
}