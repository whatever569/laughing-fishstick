#include "pc communication/Microcontroller/uart0.h"
#include "delay.h"
#include "eeprom/at24c256.h"

int main() {
	uart0_init();
	eeprom_init();
	millis_setup();

	delay_ms(3000);
	
	while (1) {
	}

	return 0;
}
