#include "ui_manager.h"
#include "helper/drawing_helper.h"

// SettingsPage Implementation
SettingsPage::SettingsPage(void *uiManager) : SecondPageBase(uiManager, "m"), secondPage('m') {
    setUIManager(uiManager);
    backButton = new Button(20, 2, 120, 60, "Back", "m");
    chargerButton = new Button(20, 120, 200, 60, "Charge", "s-c");
    dischargerButton = new Button(20, 200, 200, 60, "Discharge", "s-d");

    // Buttons auf UIManager referenzieren
    backButton->setUIManager(uiManager);
    chargerButton->setUIManager(uiManager);
    dischargerButton->setUIManager(uiManager);
}

SettingsPage::~SettingsPage() {
    delete backButton;
    delete chargerButton;
    delete dischargerButton;
}

void SettingsPage::draw(LGFX *gfx) {
    // Seitenlayout
    draw_base_page(gfx, "Settings Page");

    // Back Button
    backButton->draw(gfx);

    chargerButton->draw(gfx);
    dischargerButton->draw(gfx);
}

void SettingsPage::handleTouch(int touchX, int touchY) {
    if (backButton->isPressed(touchX, touchY)) {
        ((UIManager *) getUIManager())->switchPage(PAGE_MAIN);
    }
    if (chargerButton->isPressed(touchX, touchY)) {
        // Wechsel zur Charger-Seite
        ((UIManager *) getUIManager())->switchPage(PAGE_CHARGER_SETTINGS);
    }
    if (dischargerButton->isPressed(touchX, touchY)) {
        // Wechsel zur Charger-Seite
        ((UIManager *) getUIManager())->switchPage(PAGE_DISCHARGER_SETTINGS);
    }

}

void SettingsPage::saveAddress() {
    // Adresse speichern
}

void SettingsPage::saveChargerAddress() {
    // Charger Adresse speichern
}
