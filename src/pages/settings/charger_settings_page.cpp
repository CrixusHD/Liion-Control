#include "ui_manager.h"
#include "helper/drawing_helper.h"

// ChargerSettingsPage Implementation
ChargerSettingsPage::ChargerSettingsPage(void *uiManager) : SecondPageBase(uiManager, "s") {
    // backButton wird bereits in SecondPageBase initialisiert

    // Address Buttons
    for (int i = 0; i < 10; i++) {
        int x = (i < 5) ? 20 : 280;
        int y = 170 + (i % 5) * 80;
        addressButtons[i] = new Button(x, y, 200, 60, String(i));
    }
}

ChargerSettingsPage::~ChargerSettingsPage() {
    // backButton wird bereits in SecondPageBase zerstört

    for (int i = 0; i < 10; i++) {
        delete addressButtons[i];
    }
}

void ChargerSettingsPage::draw(LGFX *gfx) {
    // Seitenlayout
    draw_base_page(gfx, "Charger Settings");

    // Back Button
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

void ChargerSettingsPage::handleTouch(int touchX, int touchY) {
    if (getBackButton()->isPressed(touchX, touchY)) {
        // Zurück zur Hauptseite
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
