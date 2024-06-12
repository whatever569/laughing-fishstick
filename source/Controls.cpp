#include "Controls.h"
#include <MKL25Z4.H>

#define A_BUTTON_SHIFT 4
#define A_BUTTON_PORT PORTA

#define B_BUTTON_SHIFT 5
#define B_BUTTON_PORT PORTA

#define C_BUTTON_SHIFT 12
#define C_BUTTON_PORT PORTA 

#define D_BUTTON_SHIFT 13
#define D_BUTTON_PORT PORTA 

#define MASK(x) (1UL<<x)

volatile int Controls::t0ForA = 0;
volatile int Controls::t0ForB = 0;
volatile int Controls::t0ForC = 0;
volatile int Controls::t0ForD = 0;
int Controls::debounceMillis = 50;

extern "C" void PORTA_IRQHandler()
{
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	
	if(!(PORTA->ISFR & MASK(A_BUTTON_SHIFT))) {
		PORTA->ISFR |= MASK(A_BUTTON_SHIFT);
		
		if((milliSecond - Controls::t0ForA) > Controls::debounceMillis)
		{
			Controls::t0ForA = milliSecond;

			
			Controls::controlsSingleton->APressedFunction();
		}
	}
	
	if(!(PORTA->ISFR & MASK(B_BUTTON_SHIFT))) {
		PORTA->ISFR |= MASK(B_BUTTON_SHIFT);
		
		if((milliSecond - Controls::t0ForB) > Controls::debounceMillis)
		{
			Controls::t0ForB = milliSecond; 
			Controls::controlsSingleton->BPressedFunction();
		}
	}
	
	if(!(PORTA->ISFR & MASK(C_BUTTON_SHIFT))) {
		PORTA->ISFR |= MASK(C_BUTTON_SHIFT);
		
		if((milliSecond - Controls::t0ForC) > Controls::debounceMillis)
		{
			Controls::t0ForC = milliSecond; 
			Controls::controlsSingleton->CPressedFunction();
		}
	}
	
	if(!(PORTA->ISFR & MASK(D_BUTTON_SHIFT))) {
		PORTA->ISFR |= MASK(D_BUTTON_SHIFT);
		
		if((milliSecond - Controls::t0ForD) > Controls::debounceMillis)
		{
			Controls::t0ForD = milliSecond; 
			Controls::controlsSingleton->DPressedFunction();
		}
	}
}

void Controls::initializeButtons()
{
			SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
			// MUX: GPIO, IRQC: FALLING EDGE, Pullup resistor
			A_BUTTON_PORT->PCR[A_BUTTON_SHIFT] |= PORT_PCR_MUX(1) | PORT_PCR_IRQC(0b1010) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; 
			B_BUTTON_PORT->PCR[B_BUTTON_SHIFT] |= PORT_PCR_MUX(1) | PORT_PCR_IRQC(0b1010) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; 
			C_BUTTON_PORT->PCR[C_BUTTON_SHIFT] |= PORT_PCR_MUX(1) | PORT_PCR_IRQC(0b1010) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; 
			D_BUTTON_PORT->PCR[D_BUTTON_SHIFT] |= PORT_PCR_MUX(1) | PORT_PCR_IRQC(0b1010) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;

			NVIC_ClearPendingIRQ(PORTA_IRQn);

			NVIC_SetPriority(PORTA_IRQn, 1);			

			NVIC_EnableIRQ(PORTA_IRQn);
			__enable_irq();
}