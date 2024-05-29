#include <math.h>
#include "PIT.h"

PITObject* PITObject::PITSingleton = nullptr;
void (*PITObject::PIT_function)(void) = nullptr;

PITObject::~PITObject()
{
    PIT_function = doNothing;
    NVIC_ClearPendingIRQ(PIT_IRQn);
    NVIC_DisableIRQ(PIT_IRQn);
}

PITObject::PITObject(double interruptFreq, void (*functionToBeExecutedAtInterrupt)(void), int channel)
{
    interruptfrequency = interruptFreq;
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;
    PIT->MCR |= PIT_MCR_FRZ_MASK;
    PIT->CHANNEL[channel].TCTRL |= PIT_TCTRL_TIE_MASK;

    int starting_value = int(floor(busFreq / interruptfrequency) - 1);
    PIT->CHANNEL[channel].LDVAL |= starting_value;
    PIT->CHANNEL[channel].TCTRL |= PIT_TCTRL_TEN_MASK;

    PIT_function = functionToBeExecutedAtInterrupt;
    NVIC_SetPriority(PIT_IRQn, NVIC_PRIORITY);
    NVIC_ClearPendingIRQ(PIT_IRQn);
    NVIC_EnableIRQ(PIT_IRQn);
}
void PITObject::deleteInstance()
{
    delete PITSingleton;
    PITSingleton = nullptr;
}
void PITObject::setInterruptFrequency(double interruptFreq, int channel)
{
    interruptfrequency = interruptFreq;
    int starting_value = int(floor(busFreq / interruptfrequency) - 1);
    PIT->CHANNEL[channel].LDVAL |= starting_value;
}

void PIT_Handler()
{
    if (PITObject::PIT_function)
    {
        PITObject::PIT_function();
    }
    else
    {
        PITObject::doNothing();
    }
}

void PITObject::doNothing()
{

}
