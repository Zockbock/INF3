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

void init(void) {
    sei();
}

int main(void) {
    init_button();
    init_led();
    
    while(1){
    };
}
