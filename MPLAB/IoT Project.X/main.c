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
#include "display.h"

#define F_CPU 16000000UL
#include <util/delay.h>

void init(void) {
    init_button();
    init_led();

    ADCSRB |= (1 << ACME);

    USART_Init(MYUBRR);
    init_adc();
    
    SPI_init();
    Display_init();
}

int main(void) {
    init();
    LEDs_React(50);
    while (1) {
//        double percVal = ((double) ADC / 1024) * 100;
//        LEDs_React(percVal);
        //        USART_Transmit((uint8_t)percVal);
//        _delay_ms(100);
//        double dB = (getADCVal() + 83.2073) / 11.003;
//        USART_Transmit(getADCVal());
        
        
        
        
        // --------------------------------
//        USART_Transmit(getADCVal());
//        _delay_ms(200);
//        unsigned char receivedData = USART_Receive();
//        if(receivedData > 100){ //105 -> modeChangeIndicator
//            ADC_ToggleMux();
//        } else { // percentage-value
//            LEDs_React(receivedData);
//        }
//        _delay_ms(200);
        // ----------------------------------
        
        
        
        
//        if(USART_Receive() == 42) {
//            leds_off();
//        }
        
//        if(data_main == 0) {
//            data_main = USART_Receive();
//        } else {
//            USART_Transmit(data_main);
//            data_main = 0;
//        }
    }
}
