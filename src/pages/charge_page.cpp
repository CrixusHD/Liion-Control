#include "akku_data.h"
#include "ui_manager.h"
#include "helper/drawing_helper.h"

// ChargerPage Implementation

ChargerPage::ChargerPage(UIManager* uiManager) : SecondPageBase(uiManager, "m"), pageNumber(0) {
    setUIManager(uiManager);
    prevButton = new Button(20, 80, 200, 60, "Prev");
    nextButton = new Button(280, 80, 200, 60, "Forw");
}

ChargerPage::~ChargerPage() {
    delete prevButton;
    delete nextButton;
}

void ChargerPage::draw(LGFX *gfx) {
    draw_split_page(gfx, "Charger " + String(pageNumber + 1));

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

    for (int i = 0; i < 8; i++) {
        int x = (i < 4) ? 20 : 280;
        int y = 170 + (i % 4) * 80;
        gfx->setCursor(x, y);
        gfx->print(String(i + 1) + ": ");
        gfx->print(voltages[i]);
    }

    // Akku Daten zeichnen
    // (In der echten Implementierung hier die Akku-Daten anzeigen)
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
    // Akku-Daten aktualisieren
}
