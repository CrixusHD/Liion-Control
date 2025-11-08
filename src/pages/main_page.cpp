#include "ui_manager.h"

// MainPage Implementation
MainPage::MainPage(void* uiManager) {
    setUIManager(uiManager);
    buttons[0] = new Button(20, 80, 200, 60, "Charger", "c");
    buttons[1] = new Button(20, 160, 200, 60, "Discharger", "d");
    buttons[2] = new Button(20, 240, 200, 60, "Settings", "s");

    // Buttons auf UIManager referenzieren
    for (int i = 0; i < 3; i++) {
        buttons[i]->setUIManager(uiManager);
    }
}

MainPage::~MainPage() {
    for (int i = 0; i < 3; i++) {
        delete buttons[i];
    }
}

void MainPage::draw(LGFX* gfx) {
    // Seitenlayout
    gfx->writeFastHLine(0, 70, 800, TFT_BLACK);
    gfx->writeFastHLine(0, 71, 800, TFT_BLACK);
    gfx->writeFastHLine(0, 72, 800, TFT_BLACK);

    // Titel
    gfx->setCursor(300, 20);
    gfx->print("ESPControl - Main Menu");

    // Buttons zeichnen
    for (int i = 0; i < 3; i++) {
        buttons[i]->draw(gfx);
    }
}

void MainPage::handleTouch(int touchX, int touchY) {
    for (int i = 0; i < 3; i++) {
        if (buttons[i]->isPressed(touchX, touchY)) {
            String& pageTarget = buttons[i]->pageTarget;
            if (pageTarget.equals("m")) {
                ((UIManager*)getUIManager())->switchPage(PAGE_MAIN);
            } else if (pageTarget.equals("c")) {
                ((UIManager*)getUIManager())->switchPage(PAGE_CHARGER);
            } else if (pageTarget.equals("d") ) {
                ((UIManager*)getUIManager())->switchPage(PAGE_DISCHARGER);
            } else if (pageTarget.equals("s")) {
                ((UIManager*)getUIManager())->switchPage(PAGE_SETTINGS);
            }
        }
    }
}
