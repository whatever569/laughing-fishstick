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
#ifndef AT24C256_H
#define AT24C256_H

#include <MKL25Z4.H>
#include <stdbool.h>
#include <stdint.h>

#define EEPROM_CLEAR 0xFF
#define EEPROM_PAGE	0x40
#define EEPROM_SIZE EEPROM_PAGE*512

extern uint16_t EEPROM_currentAdress;

void eeprom_init(void);
void eeprom_flush(void); 

bool eeprom_read(const uint16_t address, uint8_t data[], const uint16_t n);
bool eeprom_write(const uint16_t address, const uint8_t data[], const uint16_t n);
bool eeprom_write_float(const uint16_t address, float var);
bool eeprom_read_float(const uint16_t address, float *var);
bool eeprom_write_uint32_t(const uint16_t address, uint32_t var);
bool eeprom_read_uint32_t(const uint16_t address, uint32_t *var);
bool eeprom_write_uint8_t(const uint16_t address, uint8_t var);
bool eeprom_read_uint8_t(const uint16_t address, uint8_t *var);
bool eeprom_write_string(const uint16_t address, const char *str);
bool eeprom_read_string(const uint16_t address, char *str);

#endif 
