#include <Arduino.h>
#include "display.h"
#include "gt911_touch.h"
#include "ui_manager.h"
#include "akku_data.h"
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
}

void loop() {
    uiManager.update();
}
