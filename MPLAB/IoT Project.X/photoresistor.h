#ifndef PHOTORESISTOR_H
#define	PHOTORESISTOR_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <avr/interrupt.h>

void init_photoresistor(void);
float getPhotoValue(void);

#endif	/* PHOTORESISTOR_H */

