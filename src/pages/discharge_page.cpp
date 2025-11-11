#include "ui_manager.h"
#include "helper/drawing_helper.h"

// DischargerPage Implementation
DischargerPage::DischargerPage(UIManager* uiManager) : SecondPageBase(uiManager, "m"), pageNumber(0), selectedAkku(0){
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
    getBackButton()->isPressed(touchX, touchY);
    
    // Seitenwechsel
    if (prevButton->isPressed(touchX, touchY)) {
        pageNumber -= 1;
    }
    
    if (nextButton->isPressed(touchX, touchY)) {
        pageNumber += 1;
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
