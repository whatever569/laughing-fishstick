#include "pc_uart.h"

PC_UART::PC_UART(void) {
    QString COM;
    DEBUG_PRINT << "Available serial ports:" << std::endl;
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        DEBUG_PRINT << "Port: " << info.portName().toStdString() << std::endl;
        COM = QString(info.portName());
    }

    //setup should be same as microcontroller uart setup
    serial.setPortName(COM);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    if (!serial.open(QIODevice::ReadWrite)) {
        DEBUG_PRINT << "ERROR: PC_UART::PC_UART(void); cannot open serial port: " << serial.errorString().toStdString() << std::endl;
        initFlag = false;
    }
}

bool PC_UART::flush(char TxorRx) {
    if (initFlag == false) return false;
    bool successfullyFlushed = true;

    switch (TxorRx) {
    case 'T':
        DEBUG_PRINT << serial.bytesToWrite() << " Bytes Flushed" << std::endl;
        serial.clear(QSerialPort::Output);
        break;
    case 'R':
        DEBUG_PRINT << serial.bytesAvailable() << " Bytes Flushed" << std::endl;
        serial.clear(QSerialPort::Input);
        serial.flush();
        break;
    case 'B':
        DEBUG_PRINT << serial.bytesAvailable() + serial.bytesToWrite() << " Bytes Flushed" << std::endl;
        serial.clear();
        break;
    default:
        successfullyFlushed = false;
        break;
    }

    return successfullyFlushed;
}

void PC_UART::transmitData(const QByteArray data) {
    if (initFlag == false) {
        DEBUG_PRINT << "failed to transmit data" << std::endl;
        return;
    }

    if(!serial.bytesToWrite() || IGNOREWARNINGS) {
        serial.write(data);
    }

    serial.waitForReadyRead(UARTDELAY);
}

//leaving bytes argument empty will use base value which will practically always be the full buffer
QByteArray PC_UART::receiveData(const int Bytes) {
    if (initFlag == false) return QByteArray();

    while (serial.waitForReadyRead(UARTDELAY));
    QByteArray receivedData;
    int bufferSize = (Bytes <= serial.bytesAvailable()) ? Bytes : serial.bytesAvailable();
    DEBUG_PRINT << "bufferSize = " << serial.bytesAvailable() << std::endl;

    receivedData = (serial.read(bufferSize));
    DEBUG_PRINT << "Received data: " << std::endl << receivedData.toStdString() << std::endl;
    return receivedData;
}

PC_UART::~PC_UART(void) {
    if (initFlag == false || (serial.bytesAvailable() || serial.bytesToWrite())) {
        if (IGNOREWARNINGS) {
            DEBUG_PRINT << serial.bytesAvailable() + serial.bytesToWrite() << " Bytes Flushed" << std::endl;
            serial.flush();
        }
        else {
            DEBUG_PRINT << "WARNING: PC_UART::~PC_UART(bool); unsend/unreceived data available. --ignore with ignoreWarnings = true" << std::endl;
            return;
        }
    }
    serial.clear();
    serial.close();
}
