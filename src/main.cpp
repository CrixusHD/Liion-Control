#include <Arduino.h>
#include "display.h"
#include "gt911_touch.h"
#include "ui_manager.h"
#include "i2c_comm.h"

static LGFX tft;
static GT911Touch touch;
static I2CComm i2cComm;
static UIManager uiManager(&tft, &touch);

void setup() {
    Serial.begin(115200);

    // Display initialisieren
    tft.begin();
    tft.setRotation(0);
    tft.setBrightness(255);

    // Touch initialisieren
    if (!touch.begin()) {
        Serial.println("Touch controller initialization failed!");
    } else {
        Serial.println("Touch controller initialized successfully");
    }

    // UI Manager initialisieren
    uiManager.begin();
    i2cComm.begin();
    Serial.println("Setup complete!");

    byte error, address;
    int nDevices = 0;

    Serial.println("Scanning...");

    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16) Serial.print("0");
            Serial.print(address,HEX);
            Serial.println("  !");
            nDevices++;
        } else if (error == 4) {
            Serial.print("Unknown error at address 0x");
            if (address < 16) Serial.print("0");
            Serial.println(address,HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");
}

void loop() {
    uiManager.update();
}
