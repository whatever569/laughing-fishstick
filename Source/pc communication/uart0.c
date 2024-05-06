/*! ***************************************************************************
 *
 * \brief     Uart driver
 * \file      uart0.c
 * \author    Hugo Arends
 * \date      July 2021
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
#include "uart0.h"

static queue_t TxQ, RxQ;

void uart0_init(void)
{  
    // enable clock to UART and Port A
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

    // Set UART clock to 48 MHz
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
    SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
  
    // select UART pins
    PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
    PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2);
  
    UART0->C2 &=  ~(UARTLP_C2_TE_MASK | UARTLP_C2_RE_MASK);
        
    // Set baud rate to baud rate
    uint32_t divisor = 480000UL/(96*16);
    UART0->BDH = UART_BDH_SBR(divisor>>8);
    UART0->BDL = UART_BDL_SBR(divisor);
    
    // No parity, 8 bits, one stop bit, other settings;
    UART0->C1 = 0; 
    UART0->S2 = 0;
    UART0->C3 = 0;
    
    // Enable transmitter and receiver but not interrupts
    UART0->C2 |= UART_C2_TE_MASK | UART_C2_RE_MASK;
    
    NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2 or 3
    NVIC_ClearPendingIRQ(UART0_IRQn); 
    NVIC_EnableIRQ(UART0_IRQn);

    UART0->C2 |= UART_C2_RIE_MASK;
    
    q_init(&TxQ);
    q_init(&RxQ);  
}

void UART0_IRQHandler(void)
{
    uint8_t c;
  
    NVIC_ClearPendingIRQ(UART0_IRQn);
  
    if (UART0->S1 & UART_S1_TDRE_MASK)
    {
        // can send another character
        if(q_dequeue(&TxQ, &c))
        {
			UART0->D = c;
        } 
        else
        {
            // queue is empty so disable transmitter
            UART0->C2 &= ~UART_C2_TIE_MASK;
        }
    }
    if (UART0->S1 & UART_S1_RDRF_MASK)
    {
        c = UART0->D;
        
        if(!q_enqueue(&RxQ, c))
        {
            // error - queue full.
            while (1)
            {}
        }
    }
    if (UART0->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK))
    {
        // handle the error
        // clear the flag
        UART0->S1 = UART_S1_OR_MASK | UART_S1_NF_MASK | UART_S1_FE_MASK | UART_S1_PF_MASK;
    }
}

void uart0_send_string(char* str)
{   
    // Enqueue string
    while (*str != '\0') 
    { 
        // Wait for space to open up
        while(!q_enqueue(&TxQ, *str)) {}
        str++;
    }
    
    //Start transmitter if it isn't already running
    if (!(UART0->C2 & UART_C2_TIE_MASK)) 
    {
        UART0->C2 |= UART_C2_TIE_MASK;
    }
}

void uart0_get_string(char* str, const int stringSize) {
	int bufferSize = uart0_num_rx_chars_available();
	uint8_t  c = 0;
	bufferSize = (stringSize <= bufferSize) ? stringSize : bufferSize;
	
	for (int i = 0; i < bufferSize; i++) 
    { 
        q_dequeue(&RxQ, &c);
		str[i] = (char)c;
    }
	str[bufferSize] = '\0';
}

uint32_t uart0_num_rx_chars_available(void)
{
    return q_size(&RxQ);
}

char uart0_get_char(void) 
{
    uint8_t c=0;
    if (uart0_num_rx_chars_available()) q_dequeue(&RxQ, &c);
    return (char)c;
}

void uart0_put_char(char c) 
{
    // Wait for space to open up
    while(!q_enqueue(&TxQ, c)) {}
            
    // Start transmitter if it isn't already running
    if (!(UART0->C2 & UART_C2_TIE_MASK)) 
    {
        UART0->C2 |= UART_C2_TIE_MASK;
    }        
}

//char = T to flush transmit, R to flush receive, B to flush both
//doenst work as inteded because data get send with interrupt (BE AWARE WHEN USING)
bool uart0_flush(char TxorRx) { 
	bool flushed = true;
	uint8_t toilet = 0;
	
	switch (TxorRx) {
		case 'T':
			q_flush(&TxQ);
			UART0->D = toilet;
			break;
		case 'R':
			q_flush(&RxQ);
			toilet = UART0->D;
			break;
		case 'B':
			q_flush(&TxQ);
			UART0->D = toilet;
			q_flush(&RxQ);
			toilet = UART0->D;
			break;
		default:
			flushed = false;
			break;
	}
	return flushed;
}
