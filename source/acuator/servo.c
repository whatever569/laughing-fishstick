#include <MKL25Z4.h>
#include "servo.h"

void servo_init (void) {
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;	
	SERVO_PORT = PORT_PCR_MUX(3);									//PORTE pin 30, set to altenative 3 for TMP0 Channel 3 
										
	SERVO_CHANNEL.CnSC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;	//Edge aligned, high-true pulses PWM										
	SERVO_TIMER->MOD = 6e4;											//48 * 10^6 / 60 * 10^3 = 800 hz 
	SERVO_TIMER->SC |= TPM_SC_PS(0b100) | TPM_SC_CMOD(0b01);		//Prescaler: 16 --> 800 / 16 = 50 Hz (target frequency for servo), timer clock enabled on LPTMP clock
}

void servo_lock(int lockState) {
	//servo is unlocked: lockState = 0, servo position = 90 degree, Channel value = 4500.
	//servo is locked:   lockState = 1, servo position = 0 degree,  Channel value = 2000.	
	SERVO_CHANNEL.CnV = (lockState) ? 1500 : 4500; 		
}

