#ifndef SERVO_H
#define SERVO_H

#include <MKL25Z4.h>
#include "../Initializers.h"

#define SERVO_PIN 	  30			
#define SERVO_PORT 	  PORTE->PCR[SERVO_PIN] 
#define SERVO_TIMER	  TPM0	
#define SERVO_CHANNEL SERVO_TIMER->CONTROLS[3]

/*
void servo_init(void);   	      //Function to initialise timer0, and other settings for servo (declared in Initializers.h) */
void servo_lock(int lockState);	  //Function to change servo position, lockstate = 1 to lock the box, 0 to unlock the box

#endif 
