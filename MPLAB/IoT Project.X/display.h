#ifndef DISPLAY_H
#define	DISPLAY_H

#define F_CPU 16000000UL

#include <xc.h> // include processor files - each processor file is guarded.
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "tft.h"

#define SPI_DDR DDRB
#define CS      PINB2
#define MOSI    PINB3
#define SCK     PINB5
#define D_C		PIND2		//display: Data/Command
#define Reset	PIND3		//display: Reset

void SPI_init(void);
void SPISend8Bit(uint8_t data);
void SendCommandSeq(const uint16_t * data, uint16_t Anzahl);
void TFT_Window(U8 x1, U8 y1, U8 x2, U8 y2, U8 TFT_Orientation);
void TFT_SPI_16BitPixelSend(U16 data);
void TFT_Print(char* Text, U8 X, U8 Y, U8 Scale, U16 ForeColor, U16 BackColor, U8 Display_Orientation);
void Display_init(void);
void ClearDisplay(void);

#endif	/* DISPLAY_H */

