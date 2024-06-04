#ifndef DELAY_H
#define DELAY_H

#include <MKL25Z4.H>

#define MILLISFREQUENCY 20 //Hz, this is for millis function, at 20Hz it updates millis every 50 milli seconds, make higher for more precision
#define MILLISUPDATE	(1000/MILLISFREQUENCY) //milli seconds, amount of milli seconds it updates 
#define SLOWINTERRUPTFREQUENCY 0.2f
#define FASTINTERRUPTFREQUENCY 1.0f
#define INTERRUPTFREQUENCY 1.5f

typedef enum {
	S_search  = 0,
	S_hotcold = 1, 
}pitFunction_e;
	
extern volatile long milliSecond;
extern volatile bool showForNSecondsCalledFlag;
extern volatile pitFunction_e pitFunction;

void millis_setup(void);
void PIT_setup(void);
void delay_ms(int ms);
void delay_us(int us);

#endif