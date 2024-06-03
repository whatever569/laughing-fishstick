#include "pc communication/Microcontroller/uart0.h"
#include "delay.h"
#include "eeprom/at24c256.h"
#include <stdio.h>
#include "pc communication/Microcontroller/dataMC.h"

int main() {
	uart0_init();
	eeprom_init();
	millis_setup();
	
	delay_ms(100);
	
	while (1) {
	}

	return 0;
}
