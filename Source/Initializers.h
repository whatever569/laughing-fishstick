#ifndef INITIALIZER_H
#define INITIALIZER_H
//put all the initalization code here

void initializeModules();

void servo_init(void);				//Initialise timer0, and other settings for servo
void uart0_init(void);				//Initialise uart0, setup queue's for rx and tx.

#endif