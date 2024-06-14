#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "GPS.h"
#include "../delay.h"
#include "../PC communication/Microcontroller/queue.h"
#include "../PC communication/Microcontroller/uart0.h"

static queue_t Rx1;

int number(char c) {
	return (int)(c - 48);
}

void gps_init(void) {
    // Enable clock to UART1 and Port E
    SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
  
    // Select UART pins
    GPS_TX_PORT &= ~PORT_PCR_MUX_MASK;
    GPS_TX_PORT |= PORT_PCR_MUX(3);

    GPS_RX_PORT &= ~PORT_PCR_MUX_MASK;
    GPS_RX_PORT |= PORT_PCR_MUX(3);
    
    // Ensure Tx and RX pin disable before configuration 
    UART1->C2 &= ~((UART_C2_TE_MASK) & (UART_C2_RE_MASK));
        
    // Set baud rate to 9600
    uint32_t divisor = ((DEFAULT_SYSTEM_CLOCK) / 2) / (9600 * 16);
    UART1->BDH = UART_BDH_SBR(divisor >> 8);
    UART1->BDL = UART_BDL_SBR(divisor);
    
    // No parity, 8 bits, one stop bit, other settings;
    UART1->C1 = 0; 
    UART1->S2 = 0;
    UART1->C3 = 0;
	
	// Enable transmitter and receiver
    UART1->C2 |= UART_C2_RE_MASK;
    
    // Enable UART1 IRQ in NVIC
	NVIC_SetPriority(UART1_IRQn, 2); // 0, 1, 2 or 3
    NVIC_ClearPendingIRQ(UART1_IRQn);
    NVIC_EnableIRQ(UART1_IRQn);
	
	// Enable receiver interrupt
    UART1->C2 |= UART_C2_RIE_MASK;
		
    q_init(&Rx1);
}

void UART1_IRQHandler(void) {
	   
	uint8_t c;
	static int previousTime = 0;
  
    NVIC_ClearPendingIRQ(UART1_IRQn);
	
    if (UART1->S1 & UART_S1_RDRF_MASK) {
        c = UART1->D;
        q_enqueue(&Rx1, c);
    }
	
	if (milliSecond - previousTime > GPS_FLUSH_INTERVAL) {
		q_flush(&Rx1);
		previousTime = milliSecond;
	}
} 

void gps_receive_data(char* str) {
	int bufferSize = (UART_BUFFER_SIZE - 1 < q_size(&Rx1)) ? UART_BUFFER_SIZE - 1 : q_size(&Rx1);
	uint8_t  c = 0;
	
	for (int i = 0; i < bufferSize; i++) 
    { 
        q_dequeue(&Rx1, &c);
		str[i] = (char)c;
    }
	str[bufferSize] = '\0';
}

void gps(char* coordinates) {
	char GPSData[UART_BUFFER_SIZE];
	char subCoord[15] = {0};
	gps_receive_data(GPSData);			//reads everything it can from the uart

	if (GPSData[0] != NULL) {
		char *gnrmc_start = strstr(GPSData, "$GNRMC");
		if (gnrmc_start != NULL) {
			char *token = strstr(gnrmc_start, ",V"); 											// if it encounters ",V" it means no fix can be found
			if (token[1] == 'V') strcpy(coordinates, "DISCONECTED");
			else if (strchr(gnrmc_start, '\r') == NULL) strcpy(coordinates, "INVALID_DATA_NFR");	// if the endline cannot befound the GPSData string didnt read full line
			else {
				int token_index = 0;
				token = strtok(gnrmc_start, ",");
				
				while (token != NULL) {
					// Latitude is at token index 3
					if (token_index == 3) {
						strncpy(subCoord, token, sizeof(subCoord) - 1);
						subCoord[sizeof(subCoord) - 1] = '\0';
						
						//translate coordinate from minutes to degree
						int latDegree = 10*number(subCoord[0]) + number(subCoord[1]);
						double latMinute = atof(&subCoord[2]);
						sprintf(subCoord, "%.8lf", latDegree + (latMinute / 60.0));
						
						strcpy(coordinates, subCoord);
						strcat(coordinates, ", ");
					}
					
					// Longitude is at token index 5
					else if (token_index == 5) {
						strncpy(subCoord, token, sizeof(subCoord) - 1);
						subCoord[sizeof(subCoord) - 1] = '\0';
						
						//translate coordinate from minutes to degree
						int lonDegree = 100 * number(subCoord[0]) + 10 * number(subCoord[1]) + number(subCoord[2]);
						double lonMinute = atof(&subCoord[3]);
						sprintf(subCoord, "%.8f", lonDegree + (lonMinute / 60.0));
						
						strcat(coordinates, subCoord);
						break;
					}
					token_index++;
					token = strtok(NULL, ",");
				}
			}
			q_flush(&Rx1);		//empty the rest of the data left, so it wont search the same data for coordinates that are already found.
		}
		
		else strcpy(coordinates, "INVALID_DATA_NF");
	}
	else strcpy(coordinates, "NO_DATA_IN_BUFFER");
}
