
#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <Arduino.h>
#include <lvgl.h>

#include "akku_data.h"

// Seiten
enum Page {
    PAGE_MAIN,
    PAGE_CHARGER,
    PAGE_DISCHARGER,
    PAGE_SETTINGS
};

// // Akku-Datenstruktur
// struct AkkuData {
//     float volt;
//     bool isRunning;
// };

// UI Manager Klasse
class UIManager {
public:
    UIManager();
    void begin();
    void showPage(Page page);
    void updateAkkuData();

    // Handler-Funktionen
    static void mainMenuButtonHandler(lv_event_t *e);
    static void akkuButtonHandler(lv_event_t *e);
    static void backButtonHandler(lv_event_t *e);

    // Aktuelle Seite
    Page currentPage;
    int selectedAkku;
    int pageNumber;

    // Akku-Daten
    AkkuData akkuDatas[8];

private:
    // Seiten-Erstellungsfunktionen
    void createMainMenu();
    void createChargerPage();
    void createDischargerPage();
    void createSettingsPage();

    // Widgets
    lv_obj_t *screen;
    lv_obj_t *mainMenuButtons[3]; // Charger, Discharger, Settings
    lv_obj_t *dischargerButtons[8]; // 8 Akku Buttons
    lv_obj_t *dischargerDetailsLabel;
};

// Globale Instanz
extern UIManager uiManager;

#endif