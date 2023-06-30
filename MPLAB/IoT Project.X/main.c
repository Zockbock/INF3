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
#include "tft.h"
#include "string.h"

#define F_CPU 16000000UL
#include <util/delay.h>

void init(void) {
    init_button();
    init_led();

    ADCSRB |= (1 << ACME);

    USART_Init(MYUBRR);
    init_adc();

    DDRD |= (1 << D_C) | (1 << Reset); //output: PD2 -> Data/Command; PD3 -> Reset
    SPI_init();
    Display_init();
    ClearDisplay();
}

int main(void) {
    init();
    LEDs_React(50);

    Draw_Top_Rec();
    Draw_Bot_Rec();
    Draw_Mode_Rec();
    Draw_Percentage_Rec();
    Draw_CurrentMode(getCurrentMode());

    unsigned char dataStorage = 0;

    while (1) {



        USART_Transmit(getADCVal());
        _delay_ms(100);
        unsigned char receivedData = USART_Receive();

        if (receivedData > 100) { //105 -> modeChangeIndicator
            ADC_ToggleMux();
            _delay_ms(50);
        } else { // percentage-value
            if (receivedData != dataStorage) {
                LEDs_React(receivedData);
                Draw_CurrentPercentage(PercentageToString(receivedData));
            }
            //            Draw_CurrentPercentage(PercentageToString(receivedData));
            dataStorage = receivedData;
        }


        _delay_ms(100);
    }
}
