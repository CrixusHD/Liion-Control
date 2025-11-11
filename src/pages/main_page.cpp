#include "ui_manager.h"
#include "helper/drawing_helper.h"

// MainPage Implementation
MainPage::MainPage(UIManager* uiManager) {
    setUIManager(uiManager);
    buttons[0] = new PagingButton(20, 80, 200, 60, "Charger", "c", uiManager);
    buttons[1] = new PagingButton(20, 160, 200, 60, "Discharger", "d", uiManager);
    buttons[2] = new PagingButton(20, 240, 200, 60, "Settings", "s", uiManager);

    buttons[0]->disabled = false;
    buttons[1]->disabled = false;
    buttons[2]->disabled = false;
}

MainPage::~MainPage() {
    for (int i = 0; i < 3; i++) {
        delete buttons[i];
    }
}

void MainPage::draw(LGFX* gfx) {
    // Seitenlayout
    draw_base_page(gfx, "ESPControl - Main Menu");

    // Buttons zeichnen
    for (int i = 0; i < 3; i++) {
        buttons[i]->draw(gfx);
    }
}

void MainPage::handleTouch(int touchX, int touchY) {
    for (int i = 0; i < 3; i++) {
        buttons[i]->isPressed(touchX, touchY);
    }
}
