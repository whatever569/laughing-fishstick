#include <stdint.h>
#include "MKL25Z4.h"
#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H
using namespace std;


namespace randomNG
{
    /// @brief Give this function a dangling pin and it will give you back a random number based on that
    /// @param pinShift the pin's shift
    /// @param portShift is where the port is from the 0 index of SIM_SCGC5
    /// @param port is the PORTx name
    /// @param numberBits is how big the number you want to be is, from 1 to 32
    /// @return a 32bit random integer based on the readings from the pin
    /// @note that the ports in SIM_SCGC5 start from 9 and end at 13 and from PORTA through PORTE respectivly
uint32_t generaterandom32bitint(uint32_t pinShift, int portShift, GPIO_Type *gpioModulePort, int numberBits, PORT_Type *portModulePort);

}
#endif
