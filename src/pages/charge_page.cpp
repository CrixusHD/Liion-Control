#include "ui_manager.h"
#include "helper/drawing_helper.h"

// ChargerPage Implementation
ChargerPage::ChargerPage(void* uiManager) : SecondPageBase(uiManager, "s"), pageNumber(0), selectedAkku(0){
    setUIManager(uiManager);
    prevButton = new Button(20, 80, 200, 60, "Prev");
    nextButton = new Button(280, 80, 200, 60, "Forw");
    startButton = new Button(550, 330, 200, 60, "Start");
    stopButton = new Button(550, 330, 200, 60, "Stop");
    resetButton = new Button(550, 410, 200, 60, "Reset");

    // Akku Buttons
    for (int i = 0; i < 8; i++) {
        int x = (i < 4) ? 20 : 280;
        int y = 170 + (i % 4) * 80;
        akkuButtons[i] = new Button(x, y, 200, 60, "Akku " + String(i + 1));
    }

    // Buttons auf UIManager referenzieren
    prevButton->setUIManager(uiManager);
    nextButton->setUIManager(uiManager);
    startButton->setUIManager(uiManager);
    stopButton->setUIManager(uiManager);
    resetButton->setUIManager(uiManager);

    for (int i = 0; i < 8; i++) {
        akkuButtons[i]->setUIManager(uiManager);
    }
}

ChargerPage::~ChargerPage() {
    delete prevButton;
    delete nextButton;
    delete startButton;
    delete stopButton;
    delete resetButton;

    for (int i = 0; i < 8; i++) {
        delete akkuButtons[i];
    }
}

void ChargerPage::draw(LGFX* gfx) {
    // Seitenlayout
    draw_split_page(gfx, "Charger " + String(pageNumber + 1));

    // Buttons zeichnen
    getBackButton()->draw(gfx);
    
    // Seitennummerierung
    if (pageNumber > 0) {
        prevButton->draw(gfx);
    } else {
        gfx->writeFillRect(20, 80, 200, 60, TFT_WHITE);
    }

    if (pageNumber < 7) {
        nextButton->draw(gfx);
    } else {
        gfx->writeFillRect(280, 80, 200, 60, TFT_WHITE);
    }

    // Akku Buttons zeichnen
    for (int i = 0; i < 8; i++) {
        akkuButtons[i]->draw(gfx);
    }

    // Akku Daten zeichnen
    // (In der echten Implementierung hier die Akku-Daten anzeigen)
}

void ChargerPage::handleTouch(int touchX, int touchY) {
    // Back Button
    if (getBackButton()->isPressed(touchX, touchY)) {
        ((UIManager*)getUIManager())->switchPage(PAGE_MAIN);
    }
    
    // Seitenwechsel
    if (prevButton->isPressed(touchX, touchY)) {
        pageNumber -= 1;
    }
    
    if (nextButton->isPressed(touchX, touchY)) {
        pageNumber *= 1;
    }
    
    // Akku Auswahl
    for (int i = 0; i < 8; i++) {
        if (akkuButtons[i]->isPressed(touchX, touchY)) {
            selectedAkku = i;
            // Akku ausgewählt
        }
    }
    
    // Aktionen
    if (startButton->isPressed(touchX, touchY)) {
        // Starten
    }
    
    if (stopButton->isPressed(touchX, touchY)) {
        // Stoppen
    }
    
    if (resetButton->isPressed(touchX, touchY)) {
        // Zurücksetzen
    }
}

void ChargerPage::updateAkkuData() {
    // Akku-Daten aktualisieren
}
