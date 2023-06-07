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

#define F_CPU 16000000UL
#include <util/delay.h>

void init(void) {
    
}

int main(void) {
    init_button();
    init_led();
    USART_Init(MYUBRR);
//    unsigned char test = 1;
    unsigned char val = 0;
    while(1){
//        test++;
//        USART_Transmit(test);
//        _delay_ms(500);
        val = USART_Receive();
        
        if(val != 0) {
            leds_off();
        }
        
//        _delay_ms(500);
        USART_Transmit(val);
        val = 0;
    }
}
