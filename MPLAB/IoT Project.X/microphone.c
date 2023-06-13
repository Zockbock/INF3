#include <xc.h>
#include <avr/interrupt.h>
#include "microphone.h"

float micValue;

void init_microphone(void) {
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1); //set voltage Reference to AVCC 5V

    ADMUX &= ~(1 << MUX0);
    ADMUX &= ~(1 << MUX1);
    ADMUX &= ~(1 << MUX2);
    ADMUX &= ~(1 << MUX3); //set Input to ADC0

    ADCSRB &= ~(1 << ADTS0);
    ADCSRB &= ~(1 << ADTS1);
    ADCSRB &= ~(1 << ADTS2); //set to free running mode/
    // or ADCSRB = 0;

    ADCSRA |= (1 << ADPS2);
    ADCSRA |= (1 << ADPS1);
    ADCSRA |= (1 << ADPS0); // set ADC prescaler to 128 for 125 kHz

    ADCSRA |= (1 << ADIE); // enable ADC interrrupt
    ADCSRA |= (1 << ADATE); // enable ADC Auto Trigger
    ADCSRA |= (1 << ADEN); // ADC enable
    ADCSRA |= (1 << ADSC); // start first conversion

}

ISR(ADC_vect) {
    micValue = ADC;
}

float getMicValue(void) {
    return micValue;
}