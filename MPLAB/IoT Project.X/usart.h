
#ifndef USART_H
#define	USART_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <avr/io.h>

#ifndef FOSC 
#define FOSC 16000000UL // Clock Speed
#endif

#ifndef BAUD
#define BAUD 9600
#endif

#ifndef MYUBRR
#define MYUBRR FOSC/16/BAUD-1
#endif

void USART_Init(unsigned int ubrr);
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);

#endif	/* XC_HEADER_TEMPLATE_H */

