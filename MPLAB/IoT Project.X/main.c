/*
 * File:   main.c
 * Author: Leiv
 *
 * Created on 2. Juni 2023, 13:57
 */


#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "button.h"
#include "led.h"
#include "usart.h"
#include "adc.h"

#define F_CPU 16000000UL
#include <util/delay.h>

void init(void) {
    init_button();
    init_led();

    ADCSRB |= (1 << ACME);

    USART_Init(MYUBRR);
    init_adc();
}

int main(void) {
    init();

    while (1) {
        float percVal = ((float)ADC / 255) * 100;
        LEDs_React(percVal);
        USART_Transmit(percVal);
        //        USART_Transmit(ADC);
    }
}
