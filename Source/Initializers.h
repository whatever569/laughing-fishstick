#ifndef INITIALIZER_H
#define INITIALIZER_H
//put all the initalization code here

#ifdef __cplusplus
extern "C" {
#endif

void initializeModules(void);

void servo_init(void);				//Initialise timer0, and other settings for servo
void uart0_init(void);				//Initialise uart0, setup queue's for rx and tx.
void gps_init(void);				//Initialise GPS, setup uart1.
	
static void delay(int ms);			//usefull function while testing stuff, change if you have a better place for it

#ifdef __cplusplus
}
#endif
	
#endif
