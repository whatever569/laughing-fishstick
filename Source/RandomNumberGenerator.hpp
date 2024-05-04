using namespace std;
#include <stdint.h>

namespace random
{
    /// @brief Give this function a dangling pin and it will give you back a random number based on that
    /// @param pinShift the pin's shift
    /// @param portShift is where the port is from the 0 index of SIM_SCGC5
    /// @param port is the PORTx name
    /// @param numberBits is how big the number you want to be is, from 1 to 32
    /// @return a 32bit random integer based on the readings from the pin
    /// @note that the ports in SIM_SCGC5 start from 9 and end at 13 and from PORTA through PORTE respectivly
    uint32_t generaterandom32bitint(uint32_t pinShift, int portShift, GPIO_Type *port, int numberBits)
    {
        uint32_t rand = 0;
        SIM_SCGC5 |= (1UL << portShift);
        port->PCR[pinShift] = PORT_PCR_MUX(1);
        port->PDDR &= ~(1UL << pinShift);

        for (int i = 0; i < numberBits; i++)
        {
            if(port->PDIR & (1UL<<pinShift))
            {
                rand |= (1UL << i);
            }
        }

        return rand;
    }
}