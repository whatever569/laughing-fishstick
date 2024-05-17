#ifndef PIT_H
#define PIT_H
#include <math.h>
using namespace std;
#include "MKL25Z4.h"
class PITObject
{
    private:
        const int busFreq = 10550000;
        const int NVIC_PRIORITY = 3;
        double interruptfrequency;
        ~ PITObject();
    public:
        static void(*PIT_function)(void);
        /// @brief print "PIT is executing nothing"
        static void doNothing();
        static PITObject * PITSingleton;
        void deleteInstance();
        PITObject(double interruptFreq, void(*functionToBeExecutedAtInterrupt)(void));
        /// @brief The load value will only update after the current PIT is finished and therefore the effect will be on the next cycle
        /// @param interruptFreq frequency at which the function will be executed
        void setInterruptFrequency(double interruptFreq);
};
#endif
