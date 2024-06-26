#ifndef GPS_H
#define GPS_H

#ifdef __cplusplus
extern "C" {
#endif

#define UART_BUFFER_SIZE 400
#define GPS_FLUSH_INTERVAL 3e4 //every 10 seconds, it is flushed to ensure recent data when read

#define GPS_RX_PIN 0
#define GPS_TX_PIN 1
#define GPS_RX_PORT PORTE->PCR[GPS_RX_PIN]
#define GPS_TX_PORT PORTE->PCR[GPS_TX_PIN]

void gps_init(void); 
void gps_receive_data (char* str);
void gps (char* coordinates);
int number(char c);

#ifdef __cplusplus
}
#endif
#endif
