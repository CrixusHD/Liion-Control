#ifndef GT911_TOUCH_H
#define GT911_TOUCH_H

#include <Arduino.h>
#include <Wire.h>
#include "display_config.h"

#define GT911_ADDR1 0x5D
#define GT911_ADDR2 0x14
#define GT911_PRODUCT_ID 0x8140

class GT911Touch {
private:
    uint8_t _addr;
    
    void reset(uint8_t addr);
    uint8_t detectAddress();

public:
    GT911Touch();
    bool begin();
    bool read(uint16_t *x, uint16_t *y);
};

#endif
