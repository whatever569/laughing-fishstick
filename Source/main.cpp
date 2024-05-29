#include "pc communication/Microcontroller/uart0.h"
#include "delay.h"
#include "eeprom/at24c256.h"
#include "PIT.h"

int main() {
	uart0_init();
	eeprom_init();
	
	uart0_put_char('L');
	delay_ms(3000);
	while (1) {
	}

	return 0;
}
