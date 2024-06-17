#include <MKL25Z4.H>
#include <stdio.h>
#include "delay.h"
#include "eeprom/at24c256.h"
#include "User.h"
#include "display/Display.h"
#include "StateMachineInternals.h"
#include "temprature/temp.h"
#include "pc communication/Microcontroller/uart0.h"

volatile long milliSecond = 0;
volatile pitFunction_e pitFunction = pitfunction_nothing;

void millis_setup() {
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;
    PIT->MCR |= PIT_MCR_FRZ_MASK;
    PIT->CHANNEL[1].LDVAL = PIT_LDVAL_TSV((24e6 / MILLISFREQUENCY) - 1);
	
    NVIC_SetPriority(PIT_IRQn, 0);
    NVIC_ClearPendingIRQ(PIT_IRQn);
    NVIC_EnableIRQ(PIT_IRQn);
	
	PIT->CHANNEL[1].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;
}

void PIT_setup(void) {
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;
    PIT->MCR |= PIT_MCR_FRZ_MASK;
    PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV((24e6 / SLOWINTERRUPTFREQUENCY) - 1);
	
    NVIC_SetPriority(PIT_IRQn, 3);
    NVIC_ClearPendingIRQ(PIT_IRQn);
    NVIC_EnableIRQ(PIT_IRQn);
}

void delay_ms(int ms) {
#if (CLOCK_SETUP != 1)
#warning This function is made for CLOCK_SETUP = 1, with other values the delay is bigger/smaller
#endif	

	for(volatile int t = 4000*ms; t>0; t--)
    {
        __asm("nop");
        __asm("nop");
    }
}

void delay_us(int us) {
#if (CLOCK_SETUP != 1)
#warning This function is made for CLOCK_SETUP = 1, with other values the delay is bigger/smaller
#endif	

	for(volatile int t = 4*us; t>0; t--)
    {
        __asm("nop");
        __asm("nop");
    }
}

void updateTempAndCoord(void) {
	static float temprature = 0;
	float tempTemprature = temperaturesensor();
	if (tempTemprature) {
		temprature = tempTemprature;
	}
	
	if ((milliSecond % 30000) == 0) {
		char dataEeprom[40];
		char coordin[30] = {0};
		User::userSingleton->setUsersCurrentLocation(coordin);
		GPSLocation coord = User::userSingleton->getUsersCurrentLocation();
		
		sprintf(dataEeprom, "D:%lf, %lfC%.2f|", coord.getLatitude(), coord.getLongitude(), temprature);
		eeprom_write_string(EEPROM_currentAdress, dataEeprom);
	}
}

void displayShowForTime(void) {	
	if (showForNSecondsCalledFlag && ((milliSecond - millisWhenShowForNSecondsCalled) > nScreenMilliseconds)) {
			showForNSecondsCalledFlag = false;
			returnScreen();
	}
}
 
extern "C" void PIT_IRQHandler(void) {
	NVIC_ClearPendingIRQ(PIT_IRQn);
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;	
		
		switch (pitFunction) {
			case pitfunction_hotcold:  
				timerInterruptHotCold();
				break;
			case pitfunction_search: 
				interruptFunctionS_SEARCH();
				break;	
			case pitfunction_nothing:
				break;
		}
	}	
	
	if (PIT->CHANNEL[1].TFLG & PIT_TFLG_TIF_MASK) {
		PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;
		
		milliSecond += MILLISUPDATE;
		
		displayShowForTime();
		updateTempAndCoord();
	}
}
