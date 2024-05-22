#include "Initializers.h"

void initializeModules() {
	servo_init();
	uart0_init();
	gps_init();
}

static void delay(int ms) {
#if (CLOCK_SETUP != 1)
#warning This function is made for CLOCK_SETUP = 1, with other values the delay is bigger/smaller
#endif	

	for(volatile int t = 4000*ms; t>0; t--)
    {
        __asm("nop");
        __asm("nop");
    }
}
