#ifndef STRING_H
#define	STRING_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <avr/io.h>

char* PercentageToString(unsigned char p);
char* getCurrentMode();

#endif	

