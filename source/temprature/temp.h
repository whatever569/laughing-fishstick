#ifndef TEMP_H
#define TEMP_H

#include "eeprom/i2c0.h"
#include <stdbool.h>
#include <stdint.h>

#define DHT20_ADDRESS (0x38 << 1)
#define Status_ADDRESS (0x71)

bool DHT20_resetRegister(uint8_t reg);
float temperatureSensor();
static uint8_t calculate_crc(uint8_t *data, uint8_t len);

bool i2c0_read_temp(const uint8_t device_address, const uint8_t address, uint8_t data[], const uint16_t n);
bool i2c0_write_temp(const uint8_t device_address, const uint8_t address, const uint8_t data[], const uint16_t n);
	
#endif

