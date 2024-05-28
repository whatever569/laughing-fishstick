/*! ***************************************************************************
 *
 * \brief     Low level driver for the AT24C256 EEPROM
 * \file      at24c256.c
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
#include "at24c256.h"
#include "i2c0.h"
#include "delay.h"

/*!
 * \brief Initialises the AT24C256 EEPROM
 *
 */
void eeprom_init(void)
{
    i2c0_init();
}

/*!
 * \brief Reads data from the AT24C256 EEPROM
 *
 * This function implements random sequential read. The start address is set
 * by the address parameter.
 *
 * There is no address range checking! This means that if for whatever reason an
 * invalid address is selected, unexpected things will occur, such as 'rolling
 * over' to the start of the memory.
 *
 * Refer to the AT24C256 datasheet Section 'Read Opereations' for more
 * information on read operations en Section 'Device addressing' for device
 * addressing.
 *
 * \param[in]  address  15-bit address to start reading
 *                      Valid range: 0x0000 - 0x7FFF (0 - 32768)
 * \param[in]  data     Pointer for storing the read data
 * \param[in]  n        Number of data bytes that must be read
 *
 * \return True on successfull communication, false otherwise
 */
bool eeprom_read(const uint16_t address, uint8_t data[], const uint16_t n)
{
    // Make sure there is a t_wr delay of 10ms
    delay_us(10000);

    uint8_t device_address = 0b10100000;

    return i2c0_read(device_address, address, data, n);
}

/*!
 * \brief Writes data to the AT24C256 EEPROM
 *
 * This function implements page write. The start address is set
 * by the address parameter.
 *
 * There is no address range checking! This means that if for whatever reason an
 * invalid address is selected, unexpected things will occur, such as 'rolling
 * over' to the start of the memory.
 *
 * Refer to the AT24C256 datasheet Section 'Write Opereations' for more
 * information on write operations en Section 'Device addressing' for device
 * addressing.
 *
 * \param[in]  address  15-bit address to start writing
 *                      Valid range: 0x0000 - 0x7FFF (0 - 32768)
 * \param[in]  data     Pointer to the data that must be written
 * \param[in]  n        Number of data bytes that must be written
 *
 * \return True on successfull communication, false otherwise
 */
bool eeprom_write(const uint16_t address, const uint8_t data[], const uint16_t n)
{
    uint8_t device_address = 0b10100000;

    const uint8_t PAGE_SIZE_IN_BYTES = 64;
    uint16_t start_address = address;
    uint16_t n_written = 0;

    while(n_written < n)
    {
        // Set length that fits the current page
        uint16_t m = PAGE_SIZE_IN_BYTES - (start_address % PAGE_SIZE_IN_BYTES);

        // If the available length in the current page is larger than the
        // required length, set to required length
        m = (m > (n - n_written)) ? (n - n_written) : m;

        // Make sure there is a t_wr delay of 10ms
        delay_us(10000);

        // Write the data to the selected page
        while(!i2c0_write(device_address, start_address, &data[n_written], m))
        {
            return false;
        }

        // Calculate next start address and remaining data
        start_address += m;
        n_written += m;
    }

    return true;
}

inline bool eeprom_write_float(const uint16_t address, float var)
{
    return eeprom_write(address, (uint8_t *)(&var), sizeof(float));
}

inline bool eeprom_read_float(const uint16_t address, float *var)
{
    return eeprom_read(address, (uint8_t *)(var), sizeof(float));
}

inline bool eeprom_write_uint32_t(const uint16_t address, uint32_t var)
{
    return eeprom_write(address, (uint8_t *)(&var), sizeof(uint32_t));
}

inline bool eeprom_read_uint32_t(const uint16_t address, uint32_t *var)
{
    return eeprom_read(address, (uint8_t *)(var), sizeof(uint32_t));
}

inline bool eeprom_write_uint8_t(const uint16_t address, uint8_t var)
{
    return eeprom_write(address, (uint8_t *)(&var), sizeof(uint8_t));
}

inline bool eeprom_read_uint8_t(const uint16_t address, uint8_t *var)
{
    return eeprom_read(address, (uint8_t *)(var), sizeof(uint8_t));
}

bool eeprom_write_string(const uint16_t address, char *str)
{
    uint32_t n = 0;

    // Determine string length
    while(str[n] != '\0')
    {
        ++n;
    }
    
    // Add one more, making sure to include '\0'
    ++n;

    return eeprom_write(address, (uint8_t *)str, n);
}

// TODO. This function reads byte-by-byte, which means a delay of 10ms between
//       every byte. It makes more sense to read an entire page (for example)
//       and discard the unused bytes.
bool eeprom_read_string(const uint16_t address, char *str)
{
    uint32_t n = 0;
    uint16_t addr = address;
    
    // Read single bytes up-and-untill the '\0'
    do
    {
        // Read the single byte
        if(!eeprom_read(addr, (uint8_t *)(&(str[n])), 1))
        {
            return false;
        }

        ++n;
        ++addr;
    }
    while(str[n-1] != '\0');

    return true;
}
