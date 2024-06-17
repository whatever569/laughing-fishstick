/*! ***************************************************************************
 *
 * \brief     Low level driver for the AT24C256 EEPROM
 * \file      at24c256.h
 * \author    Hugo Arends
 * \date      April 2022
 *
 * \copyright 2022 HAN University of Applied Sciences. All Rights Reserved.
 *            \n\n
 *            Permission is hereby granted, free of charge, to any person
 *            obtaining a copy of this software and associated documentation
 *            files (the "Software"), to deal in the Software without
 *            restriction, including without limitation the rights to use,
 *            copy, modify, merge, publish, distribute, sublicense, and/or sell
 *            copies of the Software, and to permit persons to whom the
 *            Software is furnished to do so, subject to the following
 *            conditions:
 *            \n\n
 *            The above copyright notice and this permission notice shall be
 *            included in all copies or substantial portions of the Software.
 *            \n\n
 *            THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *            EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *            OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *            NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *            HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *            FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *            OTHER DEALINGS IN THE SOFTWARE.
 *
 *****************************************************************************/
#ifndef TEMP_H
#define TEMP_H

#include <MKL25Z4.H>
#include <stdbool.h>
/*
#define DHT20_ADDRESS (0x38 << 1)
#define Status_ADDRESS (0x71)

#define I2C_TIMEOUT1 10000
#define I2C_TIMEOUT (100000)


void dht20_init(void);
bool DHT20_resetRegister(uint8_t reg);
float temperaturesensor();
static uint8_t calculate_crc(uint8_t *data, uint8_t len);

bool i2c0_read_temp(const uint8_t device_address, const uint8_t address, uint8_t data[], const uint16_t n);
bool i2c0_write_temp(const uint8_t device_address, const uint8_t address, const uint8_t data[], const uint16_t n);
*/


#define DHT20_ADDRESS (0x38 << 1)
#define Status_ADDRESS (0x71)

#define I2C_TIMEOUT (100000)

bool DHT20_resetRegister(uint8_t reg);
float temperaturesensor();
static uint8_t calculate_crc(uint8_t *data, uint8_t len);

bool i2c0_read_temp(const uint8_t device_address, const uint8_t address, uint8_t data[], const uint16_t n);
bool i2c0_write_temp(const uint8_t device_address, const uint8_t address, const uint8_t data[], const uint16_t n);
	
#endif // AT24C256_H

