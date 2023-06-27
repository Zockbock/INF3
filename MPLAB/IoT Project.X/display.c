
#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "display.h"
#include "tft.h"

//#define SPI_DDR DDRB
//#define CS      PINB2
//#define MOSI    PINB3
//#define SCK     PINB5
//#define D_C		PIND2		//display: Data/Command
//#define Reset	PIND3		//display: Reset

const U8 Font[] =
{
   0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,      // Leerzeichen
   0x04 , 0x0E , 0x0E , 0x04 , 0x04 , 0x00 , 0x04 , 0x00,      //!
   0x1B , 0x1B , 0x12 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,      // Anf?hrungszeichen
   0x00 , 0x0A , 0x1F , 0x0A , 0x0A , 0x1F , 0x0A , 0x00,      //#
   0x08 , 0x0E , 0x10 , 0x0C , 0x02 , 0x1C , 0x04 , 0x00,      //$
   0x19 , 0x19 , 0x02 , 0x04 , 0x08 , 0x13 , 0x13 , 0x00,      //%
   0x08 , 0x14 , 0x14 , 0x08 , 0x15 , 0x12 , 0x0D , 0x00,      //&
   0x0C , 0x0C , 0x08 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,      //'
   0x04 , 0x08 , 0x08 , 0x08 , 0x08 , 0x08 , 0x04 , 0x00,      //(
   0x08 , 0x04 , 0x04 , 0x04 , 0x04 , 0x04 , 0x08 , 0x00,      //)
   0x00 , 0x0A , 0x0E , 0x1F , 0x0E , 0x0A , 0x00 , 0x00,      //*
   0x00 , 0x04 , 0x04 , 0x1F , 0x04 , 0x04 , 0x00 , 0x00,      //+
   0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x0C , 0x0C , 0x08,      //,
   0x00 , 0x00 , 0x00 , 0x1F , 0x00 , 0x00 , 0x00 , 0x00,      //-
   0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x0C , 0x0C , 0x00,      //.
   0x00 , 0x01 , 0x02 , 0x04 , 0x08 , 0x10 , 0x00 , 0x00,      ///
   0x0E , 0x11 , 0x13 , 0x15 , 0x19 , 0x11 , 0x0E , 0x00,      //0
   0x04 , 0x0C , 0x04 , 0x04 , 0x04 , 0x04 , 0x0E , 0x00,      //1
   0x0E , 0x11 , 0x01 , 0x06 , 0x08 , 0x10 , 0x1F , 0x00,      //2
   0x0E , 0x11 , 0x01 , 0x0E , 0x01 , 0x11 , 0x0E , 0x00,      //3
   0x02 , 0x06 , 0x0A , 0x12 , 0x1F , 0x02 , 0x02 , 0x00,      //4
   0x1F , 0x10 , 0x10 , 0x1E , 0x01 , 0x11 , 0x0E , 0x00,      //5
   0x06 , 0x08 , 0x10 , 0x1E , 0x11 , 0x11 , 0x0E , 0x00,      //6
   0x1F , 0x01 , 0x02 , 0x04 , 0x08 , 0x08 , 0x08 , 0x00,      //7
   0x0E , 0x11 , 0x11 , 0x0E , 0x11 , 0x11 , 0x0E , 0x00,      //8
   0x0E , 0x11 , 0x11 , 0x0F , 0x01 , 0x02 , 0x0C , 0x00,      //9
   0x00 , 0x00 , 0x0C , 0x0C , 0x00 , 0x0C , 0x0C , 0x00,      //:
   0x00 , 0x00 , 0x0C , 0x0C , 0x00 , 0x0C , 0x0C , 0x08,      //;
   0x02 , 0x04 , 0x08 , 0x10 , 0x08 , 0x04 , 0x02 , 0x00,      //<
   0x00 , 0x00 , 0x1F , 0x00 , 0x00 , 0x1F , 0x00 , 0x00,      //=
   0x08 , 0x04 , 0x02 , 0x01 , 0x02 , 0x04 , 0x08 , 0x00,      //>
   0x0E , 0x11 , 0x01 , 0x06 , 0x04 , 0x00 , 0x04 , 0x00,      //?
   0x0E , 0x11 , 0x17 , 0x15 , 0x17 , 0x10 , 0x0E , 0x00,      //@
   0x0E , 0x11 , 0x11 , 0x1F , 0x11 , 0x11 , 0x11 , 0x00,      //A
   0x1E , 0x11 , 0x11 , 0x1E , 0x11 , 0x11 , 0x1E , 0x00,      //B
   0x0E , 0x11 , 0x10 , 0x10 , 0x10 , 0x11 , 0x0E , 0x00,      //C
   0x1E , 0x11 , 0x11 , 0x11 , 0x11 , 0x11 , 0x1E , 0x00,      //D
   0x1F , 0x10 , 0x10 , 0x1E , 0x10 , 0x10 , 0x1F , 0x00,      //E
   0x1F , 0x10 , 0x10 , 0x1E , 0x10 , 0x10 , 0x10 , 0x00,      //F
   0x0E , 0x11 , 0x10 , 0x17 , 0x11 , 0x11 , 0x0F , 0x00,      //G
   0x11 , 0x11 , 0x11 , 0x1F , 0x11 , 0x11 , 0x11 , 0x00,      //H
   0x0E , 0x04 , 0x04 , 0x04 , 0x04 , 0x04 , 0x0E , 0x00,      //I
   0x01 , 0x01 , 0x01 , 0x01 , 0x11 , 0x11 , 0x0E , 0x00,      //J
   0x11 , 0x12 , 0x14 , 0x18 , 0x14 , 0x12 , 0x11 , 0x00,      //K
   0x10 , 0x10 , 0x10 , 0x10 , 0x10 , 0x10 , 0x1F , 0x00,      //L
   0x11 , 0x1B , 0x15 , 0x11 , 0x11 , 0x11 , 0x11 , 0x00,      //M
   0x11 , 0x19 , 0x15 , 0x13 , 0x11 , 0x11 , 0x11 , 0x00,      //N
   0x0E , 0x11 , 0x11 , 0x11 , 0x11 , 0x11 , 0x0E , 0x00,      //O
   0x1E , 0x11 , 0x11 , 0x1E , 0x10 , 0x10 , 0x10 , 0x00,      //P
   0x0E , 0x11 , 0x11 , 0x11 , 0x15 , 0x12 , 0x0D , 0x00,      //Q
   0x1E , 0x11 , 0x11 , 0x1E , 0x12 , 0x11 , 0x11 , 0x00,      //R
   0x0E , 0x11 , 0x10 , 0x0E , 0x01 , 0x11 , 0x0E , 0x00,      //S
   0x1F , 0x04 , 0x04 , 0x04 , 0x04 , 0x04 , 0x04 , 0x00,      //T
   0x11 , 0x11 , 0x11 , 0x11 , 0x11 , 0x11 , 0x0E , 0x00,      //U
   0x11 , 0x11 , 0x11 , 0x11 , 0x11 , 0x0A , 0x04 , 0x00,      //V
   0x11 , 0x11 , 0x15 , 0x15 , 0x15 , 0x15 , 0x0A , 0x00,      //W
   0x11 , 0x11 , 0x0A , 0x04 , 0x0A , 0x11 , 0x11 , 0x00,      //X
   0x11 , 0x11 , 0x11 , 0x0A , 0x04 , 0x04 , 0x04 , 0x00,      //Y
   0x1E , 0x02 , 0x04 , 0x08 , 0x10 , 0x10 , 0x1E , 0x00,      //Z
   0x0E , 0x08 , 0x08 , 0x08 , 0x08 , 0x08 , 0x0E , 0x00,      //[
   0x00 , 0x10 , 0x08 , 0x04 , 0x02 , 0x01 , 0x00 , 0x00,      // "\"
   0x0E , 0x02 , 0x02 , 0x02 , 0x02 , 0x02 , 0x0E , 0x00,      //]
   0x04 , 0x0A , 0x11 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,      //^
   0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x1F,      //_
   0x0C , 0x0C , 0x04 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,      //`
   0x00 , 0x00 , 0x0E , 0x01 , 0x0F , 0x11 , 0x0F , 0x00,      //a
   0x10 , 0x10 , 0x1E , 0x11 , 0x11 , 0x11 , 0x1E , 0x00,      //b
   0x00 , 0x00 , 0x0E , 0x11 , 0x10 , 0x11 , 0x0E , 0x00,      //c
   0x01 , 0x01 , 0x0F , 0x11 , 0x11 , 0x11 , 0x0F , 0x00,      //d
   0x00 , 0x00 , 0x0E , 0x11 , 0x1F , 0x10 , 0x0E , 0x00,      //e
   0x06 , 0x08 , 0x08 , 0x1E , 0x08 , 0x08 , 0x08 , 0x00,      //f
   0x00 , 0x00 , 0x0F , 0x11 , 0x11 , 0x0F , 0x01 , 0x0E,      //g
   0x10 , 0x10 , 0x1C , 0x12 , 0x12 , 0x12 , 0x12 , 0x00,      //h
   0x04 , 0x00 , 0x04 , 0x04 , 0x04 , 0x04 , 0x04 , 0x00,      //i
   0x02 , 0x00 , 0x06 , 0x02 , 0x02 , 0x02 , 0x12 , 0x0C,      //j
   0x10 , 0x10 , 0x12 , 0x14 , 0x18 , 0x14 , 0x12 , 0x00,      //k
   0x04 , 0x04 , 0x04 , 0x04 , 0x04 , 0x04 , 0x06 , 0x00,      //l
   0x00 , 0x00 , 0x1A , 0x15 , 0x15 , 0x11 , 0x11 , 0x00,      //m
   0x00 , 0x00 , 0x1C , 0x12 , 0x12 , 0x12 , 0x12 , 0x00,      //n
   0x00 , 0x00 , 0x0E , 0x11 , 0x11 , 0x11 , 0x0E , 0x00,      //o
   0x00 , 0x00 , 0x1E , 0x11 , 0x11 , 0x11 , 0x1E , 0x10,      //p
   0x00 , 0x00 , 0x0F , 0x11 , 0x11 , 0x11 , 0x0F , 0x01,      //q
   0x00 , 0x00 , 0x16 , 0x09 , 0x08 , 0x08 , 0x1C , 0x00,      //r
   0x00 , 0x00 , 0x0E , 0x10 , 0x0E , 0x01 , 0x0E , 0x00,      //s
   0x00 , 0x08 , 0x1E , 0x08 , 0x08 , 0x0A , 0x04 , 0x00,      //t
   0x00 , 0x00 , 0x12 , 0x12 , 0x12 , 0x16 , 0x0A , 0x00,      //u
   0x00 , 0x00 , 0x11 , 0x11 , 0x11 , 0x0A , 0x04 , 0x00,      //v
   0x00 , 0x00 , 0x11 , 0x11 , 0x15 , 0x1F , 0x0A , 0x00,      //w
   0x00 , 0x00 , 0x12 , 0x12 , 0x0C , 0x12 , 0x12 , 0x00,      //x
   0x00 , 0x00 , 0x12 , 0x12 , 0x12 , 0x0E , 0x04 , 0x18,      //y
   0x00 , 0x00 , 0x1E , 0x02 , 0x0C , 0x10 , 0x1E , 0x00,      //z
   0x06 , 0x08 , 0x08 , 0x18 , 0x08 , 0x08 , 0x06 , 0x00,      //{
   0x04 , 0x04 , 0x04 , 0x04 , 0x04 , 0x04 , 0x04 , 0x00,      //|
   0x0C , 0x02 , 0x02 , 0x03 , 0x02 , 0x02 , 0x0C , 0x00,      //}
   0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00,      // nicht verwendet
   0x0A , 0x00 , 0x0E , 0x01 , 0x0F , 0x11 , 0x0F , 0x00,      //?
   0x0A , 0x00 , 0x0E , 0x11 , 0x11 , 0x11 , 0x0E , 0x00,      //?
   0x0A , 0x00 , 0x12 , 0x12 , 0x12 , 0x16 , 0x0A , 0x00,      //?
   0x0A , 0x0E , 0x11 , 0x1F , 0x11 , 0x11 , 0x11 , 0x00,      //?
   0x0A , 0x0E , 0x11 , 0x11 , 0x11 , 0x11 , 0x0E , 0x00,      //?
   0x0A , 0x11 , 0x11 , 0x11 , 0x11 , 0x11 , 0x0E , 0x00,      //?
   0x0C , 0x12 , 0x12 , 0x1C , 0x12 , 0x12 , 0x1C , 0x10,      //?
   0x06 , 0x09 , 0x09 , 0x06 , 0x00 , 0x00 , 0x00 , 0x00	   //?  Anmerkung: selbst hinzugef?gt!!	
};

void SPI_init(void){
	//set CS, MOSI and SCK to output:
	SPI_DDR |= (1 << CS) | (1 << MOSI) | (1 << SCK);

	//enable SPI, set as master, and clock to fosc/4:
	SPCR = (1 << SPE) | (1 << MSTR);
}

void SPISend8Bit(uint8_t data){
	PORTB &= ~(1<<CS);				//CS low
	SPDR = data;					//load data into register
	while(!(SPSR & (1 << SPIF)));	//wait for transmission complete
	PORTB |= (1<<CS);				//CS high
}

void SendCommandSeq(const uint16_t * data, uint16_t Anzahl){
	uint32_t index;
	uint8_t SendeByte;
	for (index=0; index<Anzahl; index++){
		PORTD |= (1<<D_C);						//Data/Command auf High => Kommando-Modus
		SendeByte = (data[index] >> 8) & 0xFF;	//High-Byte des Kommandos
		SPISend8Bit(SendeByte);
		SendeByte = data[index] & 0xFF;			//Low-Byte des Kommandos
		SPISend8Bit(SendeByte);
		PORTD &= ~(1<<D_C);						//Data/Command auf Low => Daten-Modus
	}
}

void TFT_Window(U8 x1, U8 y1, U8 x2, U8 y2, U8 TFT_Orientation) 
{ 
	U16 data[] = 
	{ 
		0xEF08,
		0x1800,
		0x1200, // x1,
		0x1500, // x2,
		0x1300, // y1,
		0x1600  // y2 
	};

	switch (TFT_Orientation)
	{
		default:
			//Wenn ung?ltig, verwende Hochformat!
		case TFT_Portrait:		//Hochformat
			data[2]  |= x1;
	    	data[3]  |= x2;
	    	data[4]  |= y1;
	    	data[5]  |= y2;
			break;
		case TFT_Portrait180:
			data[1] |= 0x03;		//Hochformat um 180? gedreht
			data[2] |= TFT_MAX_X - x1;
			data[3] |= TFT_MAX_X - x2;
			data[4] |= TFT_MAX_Y - y1;
			data[5] |= TFT_MAX_Y - y2;
			break;
		case TFT_Landscape:
			data[1] |= 0x05;		//Querformat
			data[2] |= TFT_MAX_X - y1;
			data[3] |= TFT_MAX_X - y2;
			data[4] |= x1;
			data[5] |= x2;
			break;
		case TFT_Landscape180:
			data[1] |= 0x06;		//Querformat um 180? gedreht
			data[2] |= y1;
			data[3] |= y2;
			data[4] |= TFT_MAX_Y - x1;
			data[5] |= TFT_MAX_Y - x2;
			break;
    }

	SendCommandSeq(&data[0], 6);
}

void TFT_SPI_16BitPixelSend(U16 data)
{
	U8   lo, hi;

	hi = (data >> 8) & 0xFF;   //MSB
	lo = data & 0xFF;          //LSB

	SPISend8Bit(hi);
	SPISend8Bit(lo);
}

void TFT_Print(char* Text, U8 X, U8 Y, U8 Scale, U16 ForeColor, U16 BackColor, U8 Display_Orientation)
{
    U8   Index, Byte;
    U8   Ch;
    U8   CharHeight, CharWidth, CellWidth, CellHeight;
		U16  BytePos, Loop, Pixel, Color;
		S16  C, XPixelTmp, Charbit;

    //Werte fuer die Schrift
		CharWidth = 5;	//Anzahl der Pixel der Schriftbreite (ohne Leerzeichen f?r den Buchstabenabstand)
		CharHeight = 8;	//Anzahl der Pixel der Schrifth?he (ohne Leerzeichen f?r den Zeilenabstand)
		CellWidth = 6;	//Anzahl der Pixel der Schriftbreite inkl. Leerzeichen; hier kann man den Buchstabenabstand ver?ndern
		CellHeight = 9;	//Anzahl der Pixel der Schrifth?he inkl. Leerzeichen; hier kann man den Zeilenabstand ver?ndern

		Index = 0;
		Ch = Text[Index];				//in Ch wird der Wert (ASCII 32) des darzustellen Zeichens abgelegt
    while( Ch != 0x00 )
		{	
			if (Ch > 122)								//Definition einiger Sonderzeichen am Ende der Schrifttabelle
		{
				switch (Ch)								//Hier werden ungenutzte ASCII-Zeichen eliminiert
				{
					case 228: Ch = 127; break;			// ? ist an Pos. 127 etc.
					case 246: Ch = 128; break;			// ?
					case 252: Ch = 129; break;			// ?
					case 196: Ch = 130; break;			// ?
					case 214: Ch = 131; break;			// ?
					case 220: Ch = 132; break;			// ?
					case 223: Ch = 133; break;			// ?	
					case 176: Ch = 134; break;			// ? ist an Pos. 134					
					default: Ch = '?'; break;				// nicht erlaubt: wechsel zu ?
				}
		}
		
		Ch -= 32; 	//von Ch wird 32 abgezogen, da wir keine ASCII-Zeichen kleiner als ASCII 32 verwenden; die Schrifttabelle startet mit ASCII 32, das ist das Leerzeichen
		TFT_Window(X, Y, X+CellWidth*Scale-1, Y+CellHeight*Scale-1, Display_Orientation);//Aufruf der Funktion TFT_Window mit ?bergabe von x1, x2, y1, y2 und Display-Ausrichtung
		BytePos = Ch * CharHeight;

		for (Loop=0; Loop < CellHeight; ++Loop)			//Z?hlschleife, um Byte pro Byte eines Zeichens (insgesamt 8 Byte pro Zeichen) ein zu lesen
		{
			Byte = Font[BytePos+Loop];									//Byte-Wert des Zeichens holen (zeilenweise) aus Schrifttabelle
			if (Loop >= CharHeight) Byte = 0;						//Zeilen mit Hintergrundfarbe am unteren Ende des Zeichens
			for (Pixel=1; Pixel <= Scale; ++Pixel)			//Wiederholungen gem?? Scale-Faktor; z.B. bei scale=2 wird die Zeile zweimal gezeichnet
			{
				XPixelTmp = (CellWidth-CharWidth)*Scale;	//Anzahl der leeren Spalten abh?ngig vom Schrifttyp (hier ist nur ein Typ eingebunden) und der Scalierung
				for (Charbit=1; Charbit<=XPixelTmp; ++Charbit)
				{
					//Leere Spalte => wird immer mit der Hintergrundfarbe dargestellt
					TFT_SPI_16BitPixelSend(BackColor);			//Aufruf der Funktion TFT_SPI_16BitPixelSend mit der ?bergabe der Hintergrundfarbe
				}

				for (Charbit=CharWidth-1; Charbit>=0; --Charbit)	//pr?fen aller Bits pro Zeile eines Zeichens (ein Zeichen hat inkl. Leerzeile 9 Zeilen)
				{
					//Pr?fen, ob f?r das Schriftzeichen das Pixel in der Schriftfarbe oder in der Hintergrundfarbe dargestellt werden muss
					if ( (Byte >> Charbit) & 0x01 )
					   Color = ForeColor;						    		//pixel = 1: Schriftfarbe
					else
					    Color = BackColor;									//pixel = 0: Hintergrundfarbe
					for (C=1; C<=Scale; ++C)								//Anzahl der horizontalen Wiederholungen abh?ngig vom Skalierungsfaktor (scale),z.B. scale=2 => 2 Pixel
						TFT_SPI_16BitPixelSend(Color);  			//zeichne Pixel entweder mit der Schriftfarbe oder mit der Hintergrundfarbe
				}				//pr?fe n?chstes Bit des Schriftzeichens
			}					//Abh?ngig vom Scale-Faktor wird die Zeile erneut gezeichnet
		}
		Index++;
		Ch = Text[Index];
		X += CellWidth*Scale;		
	}
}

void Display_init(void) {
	const uint16_t InitData[] ={
		//Initialisierungsdaten fuer 16Bit-Farben-Modus
		0xFDFD, 0xFDFD,
		/* pause */
		0xEF00, 0xEE04, 0x1B04, 0xFEFE, 0xFEFE,
		0xEF90, 0x4A04, 0x7F3F, 0xEE04, 0x4306,
		/* pause */
		0xEF90, 0x0983, 0x0800, 0x0BAF, 0x0A00,
		0x0500, 0x0600, 0x0700, 0xEF00, 0xEE0C,
		0xEF90, 0x0080, 0xEFB0, 0x4902, 0xEF00,
		0x7F01, 0xE181, 0xE202, 0xE276, 0xE183,
		0x8001, 0xEF90, 0x0000
	};
	
	_delay_ms(300);
	PORTD &= !(1<<Reset);			//Reset-Eingang des Displays auf Low => Beginn Hardware-Reset
	_delay_ms(75);
	PORTB |= (1<<CS);				//SSEL auf High
	_delay_ms(75);
	PORTD |= (1<<D_C);				//Data/Command auf High
	_delay_ms(75);
	PORTD |= (1<<Reset);			//Reset-Eingang des Displays auf High => Ende Hardware Reset
	_delay_ms(75);
	SendCommandSeq(&InitData[0], 2);
	_delay_ms(75);
	SendCommandSeq(&InitData[2], 10);
	_delay_ms(75);
	SendCommandSeq(&InitData[12], 23);
}


