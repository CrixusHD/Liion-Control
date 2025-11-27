#include "ui_manager.h"
#include "helper/drawing_helper.h"
#include <Wire.h>

ChargerPage::ChargerPage(UIManager *uiManager) : SecondPageBase(uiManager, "m"), pageNumber(0) {
    setUIManager(uiManager);
    prevButton = new Button(20, 80, 200, 60, "Prev");
    nextButton = new Button(280, 80, 200, 60, "Forw");
}

ChargerPage::~ChargerPage() {
    delete prevButton;
    delete nextButton;
}

unsigned long lastI2c = 0;
float *internVoltages;
LGFX *internGfx;

void drawData() {
    internGfx->fillRect(20, 170, 450, 300, TFT_WHITE);
    for (int i = 0; i < 8; i++) {
        int x = (i < 4) ? 20 : 280;
        int y = 170 + (i % 4) * 80;
        internGfx->setCursor(x, y);
        internGfx->print(String(i + 1) + ": ");
        internGfx->print(internVoltages[i]);
    }
}

bool isInit = true;

void ChargerPage::draw(LGFX *gfx) {
    draw_split_page(gfx, "Charger " + String(pageNumber + 1));
    internGfx = gfx;
    internVoltages = voltages;

    if (millis() - lastI2c > 5000) {
        updateAkkuData();
        lastI2c = millis();
    }
    // Buttons zeichnen
    getBackButton()->draw(gfx);

    // Seitennummerierung
    if (pageNumber > 0) {
        prevButton->disabled = false;
        prevButton->draw(gfx);
    } else {
        prevButton->disabled = true;
        gfx->fillRect(20, 80, 200, 60, TFT_WHITE);
    }

    if (pageNumber < 7) {
        nextButton->disabled = false;
        nextButton->draw(gfx);
    } else {
        nextButton->disabled = true;
        gfx->fillRect(280, 80, 200, 60, TFT_WHITE);
    }

    // Akku Daten zeichnen
    // (In der echten Implementierung hier die Akku-Daten anzeigen)
    if (isInit) {
        isInit = false;
        drawData();
    }
}

void ChargerPage::handleTouch(int touchX, int touchY) {
    // Back Button
    getBackButton()->isPressed(touchX, touchY);

    // Seitenwechsel
    if (prevButton->isPressed(touchX, touchY)) {
        pageNumber -= 1;
        clear_header(((UIManager *) getUIManager())->getTft());
        // Neu zeichnen mit neuem Titel
        draw(((UIManager *) getUIManager())->getTft());
    }

    if (nextButton->isPressed(touchX, touchY)) {
        pageNumber += 1;
        clear_header(((UIManager *) getUIManager())->getTft());
        // Neu zeichnen mit neuem Titel
        draw(((UIManager *) getUIManager())->getTft());
    }
}

void ChargerPage::updateAkkuData() {
    // I2C-Kommunikation mit Adresse 0x50
    uint8_t bytesReceived = Wire.requestFrom(0x50, 8);

    if (bytesReceived == 8) {
        int index = 0;
        while (Wire.available() && index < 8) {
            uint8_t rawValue = Wire.read();

            // Rückrechnung mit Offset: Wert / 100 + 2.0V
            // Beispiel: Empfangen 170 -> 1.70 + 2.0 = 3.70V
            Serial.println((rawValue / 100.0) + 2.0);
            voltages[index] = (rawValue / 100.0) + 2.0;
            internVoltages = voltages;
            index++;
        }
        drawData();
    } else {
        // Fehlerbehandlung - I2C-Kommunikation fehlgeschlagen
        Serial.println("I2C communication with 0x50 failed");

        // Optional: Voltages auf Fehlerwerte setzen
        for (int i = 0; i < 8; i++) {
            voltages[i] = -1.0; // Oder 0.0 als Fehlerwert
        }
    }
}
