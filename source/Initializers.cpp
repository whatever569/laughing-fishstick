#include "Initializers.h"
#include "acuator/servo.h"
#include "pc communication/Microcontroller/uart0.h"
#include "GPS/GPS.h"
#include "eeprom/at24c256.h"
#include "delay.h"
#include "display/Display.h"
#include "Controls.h"

void initializeModules() {
	millis_setup();
	servo_init();		
	uart0_init();
	gps_init();
	eeprom_init();
	PIT_setup();
	Display::displayInit();
	Controls::controlsSingleton->initializeButtons();
}
