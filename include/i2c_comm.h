#ifndef I2C_COMM_H
#define I2C_COMM_H

#include <Arduino.h>
#include <Wire.h>

#define I2C_SLAVE_ADDR 0x55

// I2C Bus
#define I2C1_SDA_PIN 18
#define I2C1_SCL_PIN 17

class I2CComm {
private:
    static const char ASK_FOR_LENGTH = 'L';
    static const char ASK_FOR_DATA = 'D';
    static const int BUFFER_SIZE = 128;
    
    unsigned int askForLength();
    void askForData(unsigned int responseLength, String &response);

public:
    I2CComm();
    void begin();
    bool requestAkkuData();
};

#endif