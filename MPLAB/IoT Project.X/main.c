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

#define F_CPU 16000000UL
#include <util/delay.h>

//unsigned char currentPercentage;
char audio_str[] = "audio-sense";
char illuminence_str[] = "light-sense";
char double_digit[2];
char tripple_digit[3];

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

char* PercentageToString(unsigned char p){
    if(p<100){
        double_digit[0] = '0' + ((p/10) % 10);
        double_digit[1] = '0' + (p % 10);
        double_digit[2] = '\0';
        return double_digit;
    } else {
        tripple_digit[0] = '0' + (p / 100);
        tripple_digit[1] = '0' + ((p/10) % 10);
        tripple_digit[2] = '0' + (p % 10);
        tripple_digit[3] = '\0';
        return tripple_digit;
    }
}

char* getCurrentMode(){
    if (!(ADMUX & (1 << MUX0))){ // photo-resistor active
        return audio_str;
    } else {
        return illuminence_str;
    }
}

//void intToString(unsigned char value, char *buffer){
//    buffer[0] = '0' + (value / 100);
//    buffer[1] = '0' + ((value/10) % 10);
//    buffer[2] = '0' + (value % 10);
//    buffer[3] = '\0';
//}

int main(void) {
    init();
    LEDs_React(50);
    
    Draw_Top_Rec();
    Draw_Bot_Rec();
    Draw_Mode_Rec();
    Draw_Percentage_Rec();
//    Draw_CurrentMode(getCurrentMode());
//    Draw_CurrentPercentage(PercentageToString(currentPercentage));
    
//    TFT_Window(0, 0, TFT_MAX_Y, TFT_MAX_X, TFT_Landscape);  //x1,y1,x2,y2
//    for(int i = 0; i <= (132 * 176); i++){
//        TFT_SPI_16BitPixelSend(TFT_16BitBlue);
//    }
//    unsigned char asd =42;  
//    char textPlusInt[4];
//    intToString(asd, textPlusInt);
//    
//    TFT_Print(textPlusInt, 20, 30, 2, TFT_16BitBlack, TFT_16BitWhite, TFT_Landscape);
    
    while (1) {
        //        double percVal = ((double) ADC / 1024) * 100;
        //        LEDs_React(percVal);
        //        USART_Transmit((uint8_t)percVal);
        //        _delay_ms(100);
        //        double dB = (getADCVal() + 83.2073) / 11.003;
        //        USART_Transmit(getADCVal());




        // --------------------------------
        USART_Transmit(getADCVal());
        _delay_ms(100);
        unsigned char receivedData = USART_Receive();
        if(receivedData > 100){ //105 -> modeChangeIndicator
            ADC_ToggleMux();
        } else { // percentage-value
            LEDs_React(receivedData);
            Draw_CurrentPercentage(PercentageToString(receivedData));  
        }    
        _delay_ms(100);
        // ----------------------------------
    }
}
