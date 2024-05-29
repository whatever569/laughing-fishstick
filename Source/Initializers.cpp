#include "Initializers.h"
#include "acuator/servo.h"
#include "pc communication/Microcontroller/uart0.h"
#include "GPS/GPS.h"
#include "eeprom/at24c256.h"
#include "delay.h"

void initializeModules() {
	servo_init();		
	uart0_init();
	gps_init();
	eeprom_init();
	millis_setup();
}
