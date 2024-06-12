/*! ***************************************************************************
 *
 * \brief     I2C low level peripheral driver
 * \file      i2c1.h
 * \author    Hugo Arends
 * \date      April 2021
 *
 * \remark    Hardware connection
 * <pre>                                SSD1306 Oled display             </pre>
 * <pre>                           Vdd +-------------+                   </pre>
 * <pre>      FRDM-KL25Z            |  |             |                   </pre>
 * <pre>      -------------+        +--+Vcc          |                   </pre>
 * <pre>                   |   GND|----+GND          |                   </pre>
 * <pre>      I2C1_SCL/PTE1+-----------+SCL          |                   </pre>
 * <pre>      I2C1_SDA/PTE0+-----------+SDA          |                   </pre>
 * <pre>                   |           |             |                   </pre>
 * <pre>      -------------+           +-------------+                   </pre>
 *
 * \copyright 2021 HAN University of Applied Sciences. All Rights Reserved.
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
#ifndef I2C1_H
#define I2C1_H

#ifdef __cplusplus
extern "C" {
#endif

#include <MKL25Z4.h>
#include <stdint.h> 
#include <stdbool.h>

/*!
 * \brief Definition for the I2C timeout
 *
 * This timeout value is used in loops to wait for a bit to set/reset. If the
 * bit doesn't get set, the function returns.
 */
#define I2C_TIMEOUT1 (10000)

// Function prototypes
void i2c1_init(void);

bool i2c1_write_cmd(const uint8_t address, const uint8_t cmd[], const uint32_t n);
bool i2c1_write_data(const uint8_t address, const uint8_t data[], const uint32_t n);
	
#ifdef __cplusplus
}
#endif	

#endif // I2C1_H
