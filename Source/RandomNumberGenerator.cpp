#include "RandomNumberGenerator.hpp"
using namespace random;
uint32_t generaterandom32bitint(uint32_t pinShift, int portShift, GPIO_Type *port, int numberBits)
{
    uint32_t rand = 0;
    SIM_SCGC5 |= (1UL << portShift);
    port->PCR[pinShift] = PORT_PCR_MUX(1);
    port->PDDR &= ~(1UL << pinShift);

    for (int i = 0; i < numberBits; i++)
    {
        if (port->PDIR & (1UL << pinShift))
        {
            rand |= (1UL << i);
        }
    }

    return rand;
}