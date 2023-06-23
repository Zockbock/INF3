#include <xc.h>
#include <avr/interrupt.h>
#include "adc.h"
#include "usart.h"

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

volatile uint8_t counter = 0;
volatile uint16_t min = 1024;
volatile uint16_t max = 0;
volatile uint8_t adcVal;

void init_adc(void) {
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1); //set voltage Reference to AVCC 5V
    ADMUX |= (1 << ADLAR); // enable ADC left adjustment

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

int test;

ISR(ADC_vect) {
    if (ADMUX & (1 << MUX0)) {
        adcVal = ADCH;
    } else {
        adcVal = ADCH;
//        counter++;
//        if (counter == 1) {
//            min = 1024;
//            max = 0;
//        } else if (counter <= 10) {
//            min = MIN(min, ADC);
//            max = MAX(max, ADC);
//        } else {
//            counter = 0;
//            adcVal = (max - min);
//        }

    }
}

uint8_t getADCVal(void) {
    return adcVal;
}