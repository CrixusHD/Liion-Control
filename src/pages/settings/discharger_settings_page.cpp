#include "ui_manager.h"
#include "helper/drawing_helper.h"
// DischargerPage Implementation
DischargerSettingsPage::DischargerSettingsPage(void *uiManager) : SecondPageBase(uiManager, "s") {
    setUIManager(uiManager);

    // Address Buttons
    for (int i = 0; i < 10; i++) {
        int x = (i < 5) ? 20 : 280;
        int y = 170 + (i % 5) * 80;
        addressButtons[i] = new Button(x, y, 200, 60, String(i));
    }
}

DischargerSettingsPage::~DischargerSettingsPage() {
    for (int i = 0; i < 10; i++) {
        delete addressButtons[i];
    }
}

void DischargerSettingsPage::draw(LGFX *gfx) {
    // Seitenlayout
    draw_split_page(gfx, "Discharger Settings ");

    // Buttons zeichnen
    getBackButton()->draw(gfx);

    // Address Auswahl
    gfx->setCursor(80, 80);
    gfx->print("Select Address");

    // Zeige aktuelle Adressen
    for (int i = 0; i < 10; i++) {
        gfx->setCursor(600, 90 + i * 40);
        gfx->print(i);
        gfx->print(':');
        gfx->setCursor(650, 90 + i * 40);
        // Hier würde man die Adresse aus EEPROM anzeigen
    }

    // Button zum Auswählen von Adressen
    for (int i = 0; i < 10; i++) {
        int x = (i < 5) ? 20 : 280;
        int y = 170 + (i % 5) * 80;
        addressButtons[i]->draw(gfx);
    }
}

void DischargerSettingsPage::handleTouch(int touchX, int touchY) {
    // Back Button
    if (getBackButton()->isPressed(touchX, touchY)) {
        ((UIManager *) getUIManager())->switchPage(PAGE_SETTINGS);
    }

    // Address Auswahl
    for (int i = 0; i < 10; i++) {
        if (addressButtons[i]->isPressed(touchX, touchY)) {
            // Adresse auswählen
            addressSelection = String(i);
            address = "";
        }
    }

    // Speichern Button
    if (!addressSelection.isEmpty() && !address.isEmpty()) {
        // Speichern Button (würde hier implementiert)
    }
}

void DischargerSettingsPage::updateAkkuData() {
    // Akku-Daten aktualisieren
}
