#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "button.h"
#include "led.h"
#include "photoresistor.h"
#include "microphone.h"
#include "usart.h"

void init_button(void) {

    DDRB &= ~(1 << DDB1); // Configure PB1 as Input BTN2
    PORTB |= (1 << DDB1);

    sei();

    // enable interrupts on BTN
    PCICR |= 1 << PCIE0;
    PCMSK0 |= 1 << PCINT1;
}

ISR(PCINT0_vect) {
    //leds_off();

    ADC_ToggleMux();

}

void ADC_ToggleMux(void) {
    
    ADCSRA &= ~(1 << ADEN); // ADC disable
            
    if (!(ADMUX & (1 << MUX1))) {
        // switch to photoresistor 
        ADMUX |= (1 << MUX1); // select ADC1 as input
        leds_off();
    } else 
//        if (ADMUX & (1 << MUX1)) 
        {
        // switch to microphone
        ADMUX &= ~(1 << MUX1); // select ADC0 as input
        leds_on();
    }
    
    ADCSRA |= (1 << ADEN); // ADC enable
    ADCSRA |= (1 << ADSC); // start first conversion
}