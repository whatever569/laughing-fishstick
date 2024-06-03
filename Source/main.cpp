#include "pc communication/Microcontroller/uart0.h"
#include "delay.h"
#include "eeprom/at24c256.h"
#include <stdio.h>
#include "pc communication/Microcontroller/dataMC.h"

int main() {
	uart0_init();
	eeprom_init();
	millis_setup();
	
	/*
	eeprom_write_string(EEPROM_currentAdress, "ninokuniW:2|");
	eeprom_write_string(EEPROM_currentAdress, "D51.34343, 343.43434C23.34|");
	eeprom_write_string(EEPROM_currentAdress, "W0R1P1T40|");
	eeprom_write_string(EEPROM_currentAdress, "D52.34343, 102.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D52.34343, 102.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D52.34343, 102.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D52.34343, 102.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D52.34343, 102.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D52.34343, 102.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D52.34343, 102.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D52.34343, 102.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D52.34343, 102.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D52.34343, 102.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D52.34343, 102.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D52.34343, 102.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "D51.343443, 101.43434C26.34|");
	eeprom_write_string(EEPROM_currentAdress, "W1R1P1T50|");
	eeprom_write_string(EEPROM_currentAdress, "E55B3|");
	*/
	
	EEPROM_currentAdress = 0x350;
	GameDataReturn();
	
	delay_ms(100);
	
	while (1) {
	}

	return 0;
}
