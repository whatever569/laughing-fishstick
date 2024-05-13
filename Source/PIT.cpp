#include "PIT.hpp"
#include <iostream>

PITObject::~PITObject()
{
    PIT_function = doNothing;
    NVIC_ClearPendingIRQ(PIT_IRQn);
    NVIC_DisableIRQ(PIT_IRQn);
}

PITObject::PITObject(double interruptFreq, void (*functionToBeExecutedAtInterrupt)(void))
{
    interruptfrequency = interruptFreq;
    SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;
    PIT->MCR &= ~PIT_MCR_FRZ_MASK;
    PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;

    int starting_value = int(floor(busFreq / interruptfrequency) - 1);
    PIT->CHANNEL[0].LDVAL |= starting_value;
    PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;

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
void PITObject::setInterruptFrequency(double interruptFreq)
{
    interruptfrequency = interruptFreq;
    int starting_value = int(floor(busFreq / interruptfrequency) - 1);
    PIT->CHANNEL[0].LDVAL |= starting_value;
}

void PIT_Handler()
{
    PITObject::PIT_function();
}

void PITObject::doNothing()
{
    std::cout<< "PIT is executing nothing" << std::endl;
}