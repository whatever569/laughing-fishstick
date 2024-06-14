/*! ***************************************************************************
 *
 * \brief     Low level driver for the AT24C256 EEPROM
 * \file      at24c256.c
 * \author    Hugo Arends
 * \date      April 2022
 *

 *
 *****************************************************************************/
#include "temp.h"
#include "../delay.h"
#include <MKL25Z4.H>

  // Timeout value for I2C communication

/*!
 * \brief Calculates CRC for the given data
 *
 * \param[in] data Pointer to the data buffer
 * \param[in] len Length of the data buffer
 *
 * \return Calculated CRC value
 */
static uint8_t calculate_crc(uint8_t *data, uint8_t len) {
    uint8_t crc = 0xFF;
	
    for (uint8_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x31;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

float temperatureSensor(void) {
    uint8_t buffer[7];
    uint8_t status_word;
	uint8_t status_word1;
    static int state = 0;
    static uint32_t start_time = 0;
    static float temperature = 0.0f;
	uint32_t raw_temperature;
    uint32_t current_time = milliSecond;
	uint8_t command_params[2] = {0x33, 0x00};   //Send the 0xAC instruction (trigger measurement) after waiting 10ms. There are two bytes in this command parameter: 0x33 for the first byte and 0x00 for the second. 

    switch(state) {
        case 0:
            start_time = current_time;
            state++;
            break;

        case 1:
            if (current_time - start_time < 100) {   //Wait for at least 100 ms after turning on.
                state++;
            }
			break;
						
        case 2: 
            if (!i2c0_read_temp(DHT20_ADDRESS, Status_ADDRESS, &status_word, 1)) { //Before obtaining the temperature and humidity readings, transmit 0x71 to obtain a status word byte.
                return false;
            }

            if ((status_word & 0x18) != 0x18) {   // The 0x1B, 0x1C, and 0x1E registers should be initialized if the status word and 0x18 do not equal 0x18.
                uint8_t count = 0;
                if (DHT20_resetRegister(0x1B)) count++;
                if (DHT20_resetRegister(0x1C)) count++;
                if (DHT20_resetRegister(0x1E)) count++;
                delay_ms(10);
                return count;
            }
            
            delay_ms(10);
            if (!i2c0_write_temp(DHT20_ADDRESS, 0xAC, command_params, 2)) {
                return false;
            }

            start_time = current_time;
            state++;
            break;

        case 3:
            if (current_time - start_time < 80) {
                state++;
            }
            break;
						
						
		case 4:
            if (!i2c0_read_temp(DHT20_ADDRESS, 0x71, &status_word1, 1)) {
                return false;
            }

            if ((status_word1 & 0b10000000) == 0) {
                if (!i2c0_read_temp(DHT20_ADDRESS, 0x71, buffer, 7)) {
                    return false;
                }
                state++;
            } else {
                delay_ms(1);
            }
            break;

        case 5:
            raw_temperature = ((buffer[3] & 0x0F) << 16) | (buffer[4] << 8) | buffer[5];
            temperature = (((float)raw_temperature / (1 << 20)) * 200.0f) - 50.0f;

            uint8_t crc = calculate_crc(buffer, 6);
            if (crc != buffer[6]) {
                return false;  // CRC mismatch
            }

            state = 0;
            return temperature;
			break;
    }

    return false;
}


// Function to reset a register on the DHT20 sensor
bool DHT20_resetRegister(uint8_t reg) {
    uint8_t value[3] = {0, 0, 0};

    // Write the register and two 0x00 bytes
    uint8_t data[] = {0x18, 0x00, 0x00};
    if (!i2c0_write_temp(DHT20_ADDRESS, reg, data, 3)) {
        return false;
    }
    //delay_us(5000); // 5 ms delay
    delay_ms(5);
    // Read 3 bytes from the sensor
    if (!i2c0_read_temp(DHT20_ADDRESS, reg, value, 3)) {
        return false;
    }
    //delay_us(10000); // 10 ms delay
    delay_ms(10);
		
    // Write the reset command with the read values
    uint8_t reset_data[] = {0x18, value[1], value[2]};
    if (!i2c0_write_temp(DHT20_ADDRESS, (0xB0 | reg), reset_data, 3)) {
        return false;
    }
    //delay_us(5000); // 5 ms delay
		delay_ms(5);

    return true;
}



bool i2c0_read_temp(const uint8_t device_address, const uint8_t address, uint8_t data[], const uint16_t n)
{   
    // Set to transmit mode
    I2C0->C1 |= I2C_C1_TX_MASK;    

    // Generate start condition
    I2C0->C1 |= I2C_C1_MST_MASK;

    // Send the address
    I2C0->D = (device_address);
    
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
    
    // Select which reguster you want to read
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
    I2C0->D = ((device_address) | 0x01);
        
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
bool i2c0_write_temp(const uint8_t device_address, const uint8_t address, const uint8_t data[], const uint16_t n)
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
    I2C0->D = (uint8_t)(address);
        
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

