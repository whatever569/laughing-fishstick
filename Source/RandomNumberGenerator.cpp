#include "RandomNumberGenerator.hpp"
using namespace randomNG;
uint32_t generaterandom32bitint(uint32_t pinShift, int portShift, GPIO_Type *gpioModulePort, int numberBits, PORT_Type *portModulePort)
{
    uint32_t rand = 0;
    SIM->SCGC5 |= (1UL << portShift);
    portModulePort->PCR[pinShift] = PORT_PCR_MUX(1);
    gpioModulePort->PDDR &= ~(1UL << pinShift);

    for (int i = 0; i < numberBits; i++)
    {
        if (gpioModulePort->PDIR & (1UL << pinShift))
        {
            rand |= (1UL << i);
        }
    }

    return rand;
}
