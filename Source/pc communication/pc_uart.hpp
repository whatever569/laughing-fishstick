#ifndef PC_UART_HPP
#define PC_UART_HPP

#include <iostream>
#include <QSerialPort>
#include <QSerialPortInfo>

#define UARTDELAY 200   //delay implemented to give the uart time to send/receive data
#define MAXBYTES 512
#define IGNOREWARNINGS 0

//#define PC_UART_DEBUG
#ifdef PC_UART_DEBUG
    #define DEBUG_PRINT std::cout
#else
    #define DEBUG_PRINT false && std::cout
#endif

class PC_UART {
public:
    PC_UART(void);							//Initialization
    ~PC_UART(void);							//cleanup

    bool flush(char TxorRx = 'B');
    void transmitData(const QByteArray data);
    QByteArray receiveData(const int Bytes = MAXBYTES);

private:
    QSerialPort serial;
	bool initFlag = true;					//shows whether initialization went correctly
};

#endif

