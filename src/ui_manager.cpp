#include "ui_manager.h"

// UIManager Implementation
UIManager::UIManager(LGFX *tft, GT911Touch *touch)
    : tft(tft), touch(touch), currentPage(PAGE_MAIN),
      selectedAkku(0), pageNumber(0), lastRender(0), lastI2CRequest(0), lastTouch(0) {
    // mainPage = new MainPage(this);
    // chargerSettingsPage = new ChargerSettingsPage(this);
    // dischargerSettingsPage = new DischargerSettingsPage(this);
    // settingsPage = new SettingsPage(this);
    // dischargerPage = new DischargerPage(this);
    // chargerPage = new ChargerPage(this);

    current_page = new MainPage(this);;
}

UIManager::~UIManager() {
    delete mainPage;
    delete chargerSettingsPage;
    delete dischargerPage;
    delete settingsPage;
    delete dischargerSettingsPage;
    delete chargerPage;
}

void UIManager::begin() {
    // Initialisierung
    tft->fillScreen(TFT_WHITE);
    tft->setTextColor(TFT_BLACK);
    tft->setTextSize(3);
}

void UIManager::update() {
    // Touch-Handling
    if (millis() - lastTouch > 10) {
        lastTouch = millis();
        handleTouch();
    }

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
    uint16_t touchX, touchY = 0;

    if (touch->read(&touchX, &touchY) && notPressed) {
        notPressed = false;
        int x = map(touchX, 0, 480, 0, 800);
        int y = map(touchY, 0, 270, 0, 480);

        // Seite aktualisieren
        current_page->handleTouch(x, y);
    }

    if (touchX == 0 && touchY == 0){
        notPressed = true;
    }
}

void UIManager::drawPage() {
    // Seiteninhalt zeichnen
    current_page->draw(tft);
}

void UIManager::switchPage(Page page) {

    auto old_page = current_page;
    switch (page) {
        case PAGE_MAIN:
            current_page = new MainPage(this);
            break;
        case PAGE_CHARGER_SETTINGS:
            current_page = new ChargerSettingsPage(this);
            break;
        case PAGE_DISCHARGER_SETTINGS:
            current_page = new DischargerSettingsPage(this);
            break;
        case PAGE_DISCHARGER:
            current_page = new DischargerPage(this);
            break;
        case PAGE_CHARGER:
            current_page = new ChargerPage(this);
            break;
        case PAGE_SETTINGS:
            current_page = new SettingsPage(this);
            break;
    }

    // Seite neu zeichnen
    tft->fillScreen(TFT_WHITE);
    current_page->draw(tft);
    delete old_page;
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
