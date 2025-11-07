#include "ui_manager.h"
#include <EEPROM.h>

#define EEPROM_SIZE 20

UIManager uiManager;

UIManager::UIManager() {
    EEPROM.begin(EEPROM_SIZE);
}

void UIManager::begin() {
    screen = nullptr;
    showPage(PAGE_MAIN);
}

void UIManager::showPage(Page page) {
    currentPage = page;

    if (screen != nullptr) {
        lv_obj_clean(screen);
    } else {
        screen = lv_scr_act();
    }

    switch (page) {
        case PAGE_MAIN:
            createMainMenu();
            break;
        case PAGE_CHARGER:
            createChargerPage();
            break;
        case PAGE_DISCHARGER:
            createDischargerPage();
            break;
        case PAGE_SETTINGS:
            createSettingsPage();
            break;
    }
}

void UIManager::createMainMenu() {
    lv_obj_t *title = lv_label_create(screen);
    lv_label_set_text(title, "ESPControl - Main Menu");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_20, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    static Page chargerPage = PAGE_CHARGER;
    lv_obj_t *btnCharger = lv_btn_create(screen);
    lv_obj_set_size(btnCharger, 200, 60);
    lv_obj_align(btnCharger, LV_ALIGN_CENTER, 0, -80);
    lv_obj_add_event_cb(btnCharger, mainMenuButtonHandler, LV_EVENT_CLICKED, &chargerPage);

    lv_obj_t *labelCharger = lv_label_create(btnCharger);
    lv_label_set_text(labelCharger, "Charger");
    lv_obj_center(labelCharger);

    static Page dischargerPage = PAGE_DISCHARGER;
    lv_obj_t *btnDischarger = lv_btn_create(screen);
    lv_obj_set_size(btnDischarger, 200, 60);
    lv_obj_align(btnDischarger, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(btnDischarger, mainMenuButtonHandler, LV_EVENT_CLICKED, &dischargerPage);

    lv_obj_t *labelDischarger = lv_label_create(btnDischarger);
    lv_label_set_text(labelDischarger, "Discharger");
    lv_obj_center(labelDischarger);

    static Page settingsPage = PAGE_SETTINGS;
    lv_obj_t *btnSettings = lv_btn_create(screen);
    lv_obj_set_size(btnSettings, 200, 60);
    lv_obj_align(btnSettings, LV_ALIGN_CENTER, 0, 80);
    lv_obj_add_event_cb(btnSettings, mainMenuButtonHandler, LV_EVENT_CLICKED, &settingsPage);

    lv_obj_t *labelSettings = lv_label_create(btnSettings);
    lv_label_set_text(labelSettings, "Settings");
    lv_obj_center(labelSettings);
}

void UIManager::createChargerPage() {
    lv_obj_t *btnBack = lv_btn_create(screen);
    lv_obj_set_size(btnBack, 100, 40);
    lv_obj_align(btnBack, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(btnBack, backButtonHandler, LV_EVENT_CLICKED, nullptr);

    lv_obj_t *labelBack = lv_label_create(btnBack);
    lv_label_set_text(labelBack, "Back");
    lv_obj_center(labelBack);

    lv_obj_t *title = lv_label_create(screen);
    lv_label_set_text(title, "Charger Page");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_20, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
}

void UIManager::createDischargerPage() {
    lv_obj_t *btnBack = lv_btn_create(screen);
    lv_obj_set_size(btnBack, 100, 40);
    lv_obj_align(btnBack, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(btnBack, backButtonHandler, LV_EVENT_CLICKED, nullptr);

    lv_obj_t *labelBack = lv_label_create(btnBack);
    lv_label_set_text(labelBack, "Back");
    lv_obj_center(labelBack);

    lv_obj_t *title = lv_label_create(screen);
    lv_label_set_text(title, "Discharger Page");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_20, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    // Add some buttons for demonstration
    for (int i = 0; i < 8; i++) {
        lv_obj_t *btn = lv_btn_create(screen);
        lv_obj_set_size(btn, 180, 60);
        lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 20, 100 + (i * 70));

        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text_fmt(label, "Button %d", i + 1);
        lv_obj_center(label);
    }
}

void UIManager::createSettingsPage() {
    lv_obj_t *btnBack = lv_btn_create(screen);
    lv_obj_set_size(btnBack, 100, 40);
    lv_obj_align(btnBack, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(btnBack, backButtonHandler, LV_EVENT_CLICKED, nullptr);

    lv_obj_t *labelBack = lv_label_create(btnBack);
    lv_label_set_text(labelBack, "Back");
    lv_obj_center(labelBack);

    lv_obj_t *title = lv_label_create(screen);
    lv_label_set_text(title, "Settings Page");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_20, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
}

void UIManager::updateAkkuData() {
    // Implementation for updating akku data
}

void UIManager::mainMenuButtonHandler(lv_event_t *e) {
    UIManager *ui = &uiManager;
    Page *page = (Page *)lv_event_get_user_data(e);
    ui->showPage(*page);
}

void UIManager::backButtonHandler(lv_event_t *e) {
    UIManager *ui = &uiManager;
    ui->showPage(PAGE_MAIN);
}
