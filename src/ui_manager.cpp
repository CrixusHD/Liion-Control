#include "ui_manager.h"

#include "../../../../Users/Nick/.platformio/packages/toolchain-riscv32-esp/riscv32-esp-elf/include/c++/8.4.0/atomic"

// UIManager Implementation
UIManager::UIManager(LGFX *tft, GT911Touch *touch)
    : tft(tft), touch(touch), currentPage(PAGE_MAIN),
      selectedAkku(0), pageNumber(0), lastRender(0), lastI2CRequest(0) {
    mainPage = new MainPage(this);
    chargerSettingsPage = new ChargerSettingsPage(this);
    dischargerSettingsPage = new DischargerSettingsPage(this);
    settingsPage = new SettingsPage(this);
    dischargerPage = new DischargerPage(this);
    chargerPage = new ChargerPage(this);

    current_page = mainPage;
}

UIManager::~UIManager() {
    delete mainPage;
    delete chargerSettingsPage;
    delete dischargerPage;
    delete settingsPage;
}

void UIManager::begin() {
    // Initialisierung
    tft->fillScreen(TFT_WHITE);
    tft->setTextColor(TFT_BLACK);
    tft->setTextSize(3);
}

void UIManager::update() {
    // Touch-Handling
    handleTouch();

    // Rendering
    if (millis() - lastRender > 100) {
        drawPage();
        lastRender = millis();
    }

    // I2C Daten abrufen
    if (millis() - lastI2CRequest > 5000) {
        // I2C Daten abrufen
        lastI2CRequest = millis();
    }
}

volatile bool notPressed = true;

void UIManager::handleTouch() {
    uint16_t touchX, touchY;
    if (touch->read(&touchX, &touchY) && notPressed) {
        notPressed = false;
        int x = map(touchX, 0, 480, 0, 800);
        int y = map(touchY, 0, 270, 0, 480);

        // Seite aktualisieren
        current_page->handleTouch(x, y);
    }

    if (touchX == 15 && touchY == 0){
        notPressed = true;
    }
}

void UIManager::drawPage() {
    // Seiteninhalt zeichnen
    current_page->draw(tft);
}

void UIManager::switchPage(Page page) {
    currentPage = page;
    Serial.println(page);
    switch (page) {
        case PAGE_MAIN:
            current_page = mainPage;
            break;
        case PAGE_CHARGER_SETTINGS:
            current_page = chargerSettingsPage;
            break;
        case PAGE_DISCHARGER_SETTINGS:
            current_page = dischargerSettingsPage;
            break;
        case PAGE_DISCHARGER:
            current_page = dischargerPage;
        case PAGE_CHARGER:
            current_page = chargerPage;
            break;
        case PAGE_SETTINGS:
            current_page = settingsPage;
            break;
    }

    // Seite neu zeichnen
    tft->fillScreen(TFT_WHITE);
    current_page->draw(tft);
}

void UIManager::handleButtonPress(const String &pageTarget) {
    if (pageTarget.equals("m")) {
        switchPage(PAGE_MAIN);
        return;
    }
    if (pageTarget.equals("d")) {
        switchPage(PAGE_DISCHARGER);
        return;
    }
    if (pageTarget.equals("c")) {
        switchPage(PAGE_CHARGER);
        return;
    }
    if (pageTarget.equals("s-c")) {
        switchPage(PAGE_CHARGER_SETTINGS);
        return;
    }

    if (pageTarget.equals("s-d")) {
        switchPage(PAGE_DISCHARGER_SETTINGS);
        return;
    }

    if (pageTarget.equals("s")) {
        switchPage(PAGE_SETTINGS);
    }
}
