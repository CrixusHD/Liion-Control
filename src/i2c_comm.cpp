#include "i2c_comm.h"

I2CComm::I2CComm() {}

void I2CComm::begin() {
    // Wire wird bereits in gt911_touch initialisiert
}

unsigned int I2CComm::askForLength() {
    Wire.beginTransmission(I2C_SLAVE_ADDR);
    Wire.write(ASK_FOR_LENGTH);
    Wire.endTransmission();
    Wire.requestFrom(I2C_SLAVE_ADDR, 1);
    if (Wire.available()) {
        return Wire.read();
    }
    return 0;
}

void I2CComm::askForData(unsigned int responseLength, String &response) {
    Wire.beginTransmission(I2C_SLAVE_ADDR);
    Wire.write(ASK_FOR_DATA);
    Wire.endTransmission();
    
    for (unsigned int i = 0; i < responseLength; i += BUFFER_SIZE) {
        int toRead = min((int)BUFFER_SIZE, (int)(responseLength - i));
        Wire.requestFrom(I2C_SLAVE_ADDR, toRead);
        while (Wire.available()) {
            response += (char)Wire.read();
        }
    }
}

bool I2CComm::requestAkkuData() {
    Wire.beginTransmission(I2C_SLAVE_ADDR);
    int error = Wire.endTransmission();
    
    if (error != 0) return false;
    
    unsigned int responseLength = askForLength();
    if (responseLength == 0) return false;
    
    String response = "";
    askForData(responseLength, response);
    
    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, response);
    if (err) return false;
    
    JsonArray arr = doc.as<JsonArray>();
    int i = 0;
    for (JsonVariant item : arr) {
        if (i >= 8) break;
        akkuDatas[i].volt = item["volt"].as<float>();
        akkuDatas[i].isRunning = item["isRunning"].as<bool>();
        i++;
    }
    
    return true;
}