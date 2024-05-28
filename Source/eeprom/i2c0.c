/*! ***************************************************************************
 *
 * \brief     I2C low level peripheral driver
 * \file      i2c0.c
 * \author    Hugo Arends
 * \date      April 2022
 *
 * \remark    Hardware connection
 * <pre>                                   AT24C256                      </pre>
 * <pre>                          P3V3 +-------------+                   </pre>
 * <pre>      FRDM-KL25Z            |  |             |                   </pre>
 * <pre>      -------------+        +--+Vcc          |                   </pre>
 * <pre>                   |   GND|----+GND          |                   </pre>
 * <pre>      I2C0_SCL/PTC8+-----------+SCL          |                   </pre>
 * <pre>      I2C0_SDA/PTC9+-----------+SDA          |                   </pre>
 * <pre>                   |           |             |                   </pre>
 * <pre>      -------------+           +-------------+                   </pre>
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
#include <MKL25Z4.H>
#include "i2c0.h"

/*!
 * \brief Initialises the I2C peripheral
 *
 * Initialises I2C0
 * The I2C baud rate is set to 375000 bps
 * The following I2C pins are configured:
 * - PTC8: SCL
 * - PTC9: SDA
 */
void i2c0_init(void)
{
    // Clock i2c peripheral and port
    SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
    
    // Set pins to I2C function
    PORTC->PCR[8] = PORT_PCR_MUX(2);
    PORTC->PCR[9] = PORT_PCR_MUX(2);
    
    // Make sure i2c is disabled
    I2C0->C1 &= ~(I2C_C1_IICEN_MASK);
        
    // MUL[1:0] : The MULT bits define the multiplier factor mul.
    // ICR[5:0] : Prescales the bus clock for bit rate selection.
    //
    // I2C baud rate = bus speed (Hz)/(mul � SCL divider)
    //        1MHz   =     24MHz     /( 1  *    24)
    I2C0->F = (I2C_F_MULT(0) | I2C_F_ICR(0x2));   
    
    // Clear any flags
    I2C0->S |= (I2C_S_ARBL_MASK | I2C_S_IICIF_MASK);
    
    // Enable i2c and set to master mode
    I2C0->C1 |= (I2C_C1_IICEN_MASK);
}

/*!
 * \brief Reads data by using I2C0
 *
 * This function reads a number of successive bytes from an I2C slave. The slave
 * must be able set an inital address and automatically increment it's internal
 * address counter on each read operation.
 *
 * \param[in]  device_address  7-bit device address
 * \param[in]  address         16-bit address to start reading
 * \param[in]  data            Pointer to the data for staring the read data
 * \param[in]  n               Number of data bytes that must be read
 *
 * \return True on successfull communication, false otherwise
 */
bool i2c0_read(const uint8_t device_address, const uint16_t address, uint8_t data[], const uint16_t n)
{   
    // Set to transmit mode
    I2C0->C1 |= I2C_C1_TX_MASK;    

    // Generate start condition
    I2C0->C1 |= I2C_C1_MST_MASK;

    // Send the address
    I2C0->D = device_address;
    
    // Wait for acknowledge
    // Return anyway if it takes too long
    uint32_t timeout = I2C_TIMEOUT;
    while((I2C0->S & I2C_S_IICIF_MASK)==0)
    {
        if(--timeout == 0)
        {
            return false;
        }
    }
        
    // Clear the flag
    I2C0->S |= I2C_S_IICIF_MASK;
    
    // Send register
    I2C0->D = (uint8_t)(address >> 8);
        
    // Wait for acknowledge
    // If timeout occurs, try to reinitialise i2c and return from this function
    timeout = I2C_TIMEOUT;
    while((I2C0->S & I2C_S_IICIF_MASK)==0)
    {
        if(--timeout == 0)
        {
            return false;
        }
    }        
        
    // Clear the flag
    I2C0->S |= I2C_S_IICIF_MASK;    
    
    // Send register
    I2C0->D = (uint8_t)address;
        
    // Wait for acknowledge
    // If timeout occurs, try to reinitialise i2c and return from this function
    timeout = I2C_TIMEOUT;
    while((I2C0->S & I2C_S_IICIF_MASK)==0)
    {
        if(--timeout == 0)
        {
            return false;
        }
    }        
        
    // Clear the flag
    I2C0->S |= I2C_S_IICIF_MASK;       

    // Repeated start
    I2C0->C1 |= I2C_C1_RSTA_MASK;
    
    // Send device address (read)
    I2C0->D = (device_address | 0x01);
        
    // Wait for acknowledge
    // If timeout occurs, try to reinitialise i2c and return from this function
    timeout = I2C_TIMEOUT;
    while((I2C0->S & I2C_S_IICIF_MASK)==0)
    {
        if(--timeout == 0)
        {
            return false;
        }
    }        
        
    // Clear the flag
    I2C0->S |= I2C_S_IICIF_MASK; 

    // Receive mode
    I2C0->C1 &= ~I2C_C1_TX_MASK;

   
    // ACK after read
    I2C0->C1 &= ~I2C_C1_TXAK_MASK;

    uint32_t i;
    for(i=0; i<n; ++i)
    {               
        // Last byte?
        if(i == n-1)
        {
            // NACK after read
            I2C0->C1 |= I2C_C1_TXAK_MASK;
        }
        
        // Dummy read
        data[i] = I2C0->D;
        
        // Wait for acknowledge
        // If timeout occurs, try to reinitialise i2c and return from this function
        timeout = I2C_TIMEOUT;
        while((I2C0->S & I2C_S_IICIF_MASK)==0)
        {
            if(--timeout == 0)
            {
                return false;
            }
        }        
            
        // Clear the flag
        I2C0->S |= I2C_S_IICIF_MASK; 
        
        // Last byte?
        if(i == n-1)
        {
            // Send stop
            I2C0->C1 &= ~I2C_C1_MST_MASK;
        }        
     
        // Read data
        data[i] = I2C0->D;
    }
    
    return true;
}

/*!
 * \brief Writes data by using I2C0
 *
 * This function sends a number of successive bytes to an I2C slave. The slave
 * must be able set an inital address and automatically increment it's internal
 * address counter on each write operation.
 *
 * \param[in]  device_address  7-bit device address
 * \param[in]  address         16-bit address to start writing
 * \param[in]  data            Pointer to the data that must be written
 * \param[in]  n               Number of data bytes that must be written
 *
 * \return True on successfull communication, false otherwise
 */
bool i2c0_write(const uint8_t device_address, const uint16_t address, const uint8_t data[], const uint16_t n)
{    
    // Set to transmit mode
    I2C0->C1 |= I2C_C1_TX_MASK;    

    // Generate start condition
    I2C0->C1 |= I2C_C1_MST_MASK;

    // Send the address
    I2C0->D = device_address;
    
    // Wait for acknowledge
    // Return anyway if it takes too long
    uint32_t timeout = I2C_TIMEOUT;
    while((I2C0->S & I2C_S_IICIF_MASK)==0)
    {
        if(--timeout == 0)
        {
            return false;
        }
    }
        
    // Clear the flag
    I2C0->S |= I2C_S_IICIF_MASK;
    
    // Send register
    I2C0->D = (uint8_t)(address >> 8);
        
    // Wait for acknowledge
    // If timeout occurs, try to reinitialise i2c and return from this function
    timeout = I2C_TIMEOUT;
    while((I2C0->S & I2C_S_IICIF_MASK)==0)
    {
        if(--timeout == 0)
        {
            return false;
        }
    }        
        
    // Clear the flag
    I2C0->S |= I2C_S_IICIF_MASK;    
    
    // Send register
    I2C0->D = (uint8_t)address;
        
    // Wait for acknowledge
    // If timeout occurs, try to reinitialise i2c and return from this function
    timeout = I2C_TIMEOUT;
    while((I2C0->S & I2C_S_IICIF_MASK)==0)
    {
        if(--timeout == 0)
        {
            return false;
        }
    }        
        
    // Clear the flag
    I2C0->S |= I2C_S_IICIF_MASK;      
    
    for(uint32_t i=0; i<n; ++i)
    {
         // Send register
        I2C0->D = data[i];
            
        // Wait for acknowledge
        // If timeout occurs, try to reinitialise i2c and return from this function
        timeout = I2C_TIMEOUT;
        while((I2C0->S & I2C_S_IICIF_MASK)==0)
        {
            if(--timeout == 0)
            {
                return false;
            }
        }        
           
        // Clear the flag
        I2C0->S |= I2C_S_IICIF_MASK; 
    }
    
    // Send stop
    I2C0->C1 &= ~I2C_C1_MST_MASK;
    
    return true;
}
