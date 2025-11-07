#include "../include/gt911_touch.h"

GT911Touch::GT911Touch() : _addr(0) {}

void GT911Touch::reset(uint8_t addr) {
    pinMode(TOUCH_RST, OUTPUT);
    pinMode(TOUCH_INT, OUTPUT);
    digitalWrite(TOUCH_RST, LOW);
    delay(10);
    digitalWrite(TOUCH_INT, (addr == GT911_ADDR1) ? HIGH : LOW);
    delay(1);
    digitalWrite(TOUCH_RST, HIGH);
    delay(50);
    pinMode(TOUCH_INT, INPUT);
    delay(50);
}

uint8_t GT911Touch::detectAddress() {
    Wire.begin(TOUCH_SDA, TOUCH_SCL);
    Wire.setClock(400000);
    delay(100);
    Wire.beginTransmission(GT911_ADDR1);
    Wire.write(highByte(GT911_PRODUCT_ID));
    Wire.write(lowByte(GT911_PRODUCT_ID));
    Wire.endTransmission();
    return (Wire.requestFrom(GT911_ADDR1, (uint8_t)1) == 0) ? GT911_ADDR2 : GT911_ADDR1;
}

bool GT911Touch::begin() {
    reset(GT911_ADDR1);
    delay(100);
    _addr = detectAddress();
    if (_addr == GT911_ADDR2) {
        reset(GT911_ADDR2);
        delay(100);
    }
    Wire.beginTransmission(_addr);
    return (Wire.endTransmission() == 0);
}

bool GT911Touch::read(uint16_t *x, uint16_t *y) {
    Wire.beginTransmission(_addr);
    Wire.write(0x81);
    Wire.write(0x4E);
    if (Wire.endTransmission() != 0) return false;
    if (Wire.requestFrom(_addr, (uint8_t)1) != 1) return false;
    
    uint8_t touch_num = Wire.read() & 0x0F;
    if (touch_num == 0 || touch_num > 5) {
        Wire.beginTransmission(_addr);
        Wire.write(0x81);
        Wire.write(0x4E);
        Wire.write(0x00);
        Wire.endTransmission();
        return false;
    }
    
    Wire.beginTransmission(_addr);
    Wire.write(0x81);
    Wire.write(0x50);
    if (Wire.endTransmission() != 0) return false;
    if (Wire.requestFrom(_addr, (uint8_t)4) != 4) return false;
    
    *x = Wire.read();
    *x |= (Wire.read() << 8);
    *y = Wire.read();
    *y |= (Wire.read() << 8);
    
    Wire.beginTransmission(_addr);
    Wire.write(0x81);
    Wire.write(0x4E);
    Wire.write(0x00);
    Wire.endTransmission();
    
    return true;
}
