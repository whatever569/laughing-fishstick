#ifndef DELAY_H
#define DELAY_H

#define MILLISFREQUENCY 20 //Hz, this is for millis function, at 20Hz it updates millis every 50 milli seconds, make higher for more precision
#define MILLISUPDATE	(1000/MILLISFREQUENCY) //milli seconds, amount of milli seconds it updates 
	
extern volatile long milliSecond;
void millis_setup(void);
void delay_ms(int ms);
void delay_us(int us);

#endif