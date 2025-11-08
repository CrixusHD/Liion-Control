#include "ui_manager.h"
#include "helper/drawing_helper.h"

// DischargerPage Implementation
DischargerPage::DischargerPage(void* uiManager) : SecondPageBase(uiManager, "s"){
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

DischargerPage::~DischargerPage() {
    delete prevButton;
    delete nextButton;
    delete startButton;
    delete stopButton;
    delete resetButton;

    for (int i = 0; i < 8; i++) {
        delete akkuButtons[i];
    }
}

void DischargerPage::draw(LGFX* gfx) {
    // Seitenlayout
    draw_split_page(gfx, "Discharger " + String(pageNumber + 1));

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

void DischargerPage::handleTouch(int touchX, int touchY) {
    // Back Button
    if (getBackButton()->isPressed(touchX, touchY)) {
        ((UIManager*)getUIManager())->switchPage(PAGE_MAIN);
    }
    
    // Seitenwechsel
    if (prevButton->isPressed(touchX, touchY)) {
        // Vorherige Seite
    }
    
    if (nextButton->isPressed(touchX, touchY)) {
        // Nächste Seite
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

void DischargerPage::updateAkkuData() {
    // Akku-Daten aktualisieren
}
