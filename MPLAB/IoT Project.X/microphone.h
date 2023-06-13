#ifndef MICROPHONE_H
#define	MICROPHONE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <avr/interrupt.h>

void init_microphone(void);
float getMicValue(void);


#endif	/* MICROPHONE_H */

