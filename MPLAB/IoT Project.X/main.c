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
#include "photoresistor.h"
#include "microphone.h"

#define F_CPU 16000000UL
#include <util/delay.h>

void init(void) {
    init_button();
    init_led();
    USART_Init(MYUBRR);
//    init_photoresistor();
    init_microphone();
}

int main(void) {
    init();

    while (1) {

//        _delay_ms(100);
        USART_Transmit(getMicValue());

    }
}
