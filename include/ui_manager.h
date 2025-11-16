#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <Arduino.h>
#include "display.h"
#include "gt911_touch.h"
#include "ui/button.h"

// Seiten
enum Page {
    PAGE_MAIN,
    PAGE_CHARGER_SETTINGS,
    PAGE_DISCHARGER_SETTINGS,
    PAGE_DISCHARGER,
    PAGE_CHARGER,
    PAGE_SETTINGS
};

class PageBase {
private:
    UIManager* uiManager;
public:
    virtual void draw(LGFX* gfx) = 0;
    virtual void handleTouch(int touchX, int touchY) = 0;
    virtual ~PageBase() = default;

    void setUIManager(UIManager* manager) { uiManager = manager; }
    UIManager* getUIManager() const { return uiManager; }
};

class SecondPageBase : public PageBase {
private:
    PagingButton* backButton;
public:
    SecondPageBase(UIManager* uiManager, const String &targetPage);

    virtual ~SecondPageBase();

    Button* getBackButton() { return backButton; }
};

class MainPage : public PageBase {
private:
    PagingButton* buttons[3];

public:
    MainPage(UIManager* uiManager);
    ~MainPage();
    void draw(LGFX* gfx) override;
    void handleTouch(int touchX, int touchY) override;
};

class ChargerSettingsPage : public SecondPageBase {
    Button* addressButtons[10];
    String addressSelection;
    String address;
public:
    ChargerSettingsPage(UIManager* uiManager);
    ~ChargerSettingsPage();
    void draw(LGFX* gfx) override;
    void handleTouch(int touchX, int touchY) override;
};

class DischargerSettingsPage : public SecondPageBase {
private:
    Button* addressButtons[10];
    String addressSelection;
    String address;

public:
    DischargerSettingsPage(UIManager* uiManager);
    ~DischargerSettingsPage();
    void draw(LGFX* gfx) override;
    void handleTouch(int touchX, int touchY) override;
    void updateAkkuData();
};

class SettingsPage : public SecondPageBase {
private:
    PagingButton* backButton;
    PagingButton* chargerButton;
    PagingButton* dischargerButton;

public:
    SettingsPage(UIManager* uiManager);
    ~SettingsPage();
    void draw(LGFX* gfx) override;
    void handleTouch(int touchX, int touchY) override;
    void saveAddress();
    void saveChargerAddress();
};

class DischargerPage : public SecondPageBase {
private:
    Button* prevButton;
    Button* nextButton;
    Button* startButton;
    Button* stopButton;
    Button* resetButton;
    Button* akkuButtons[8];
    int selectedAkku = 0;
    int pageNumber = 0;

public:
    DischargerPage(UIManager* uiManager);
    ~DischargerPage();
    void draw(LGFX* gfx) override;
    void handleTouch(int touchX, int touchY) override;
    void updateAkkuData();
};

class ChargerPage : public SecondPageBase {
private:
    Button* prevButton;
    Button* nextButton;
    int pageNumber = 0;
    float voltages[8] = {0,0,0,0,0,0,0,0};

public:
    ChargerPage(UIManager* uiManager);
    ~ChargerPage();
    void draw(LGFX* gfx) override;
    void handleTouch(int touchX, int touchY) override;
    void updateAkkuData();
};

class UIManager {
private:
    LGFX* tft;
    GT911Touch* touch;
    Page currentPage;
    PageBase* current_page;
    int selectedAkku = 0;
    int pageNumber = 0;
    unsigned long lastRender = 0;
    unsigned long lastI2CRequest = 0;
    unsigned long lastTouch = 0;

    // Seiten
    MainPage* mainPage;
    ChargerSettingsPage* chargerSettingsPage;
    DischargerSettingsPage* dischargerSettingsPage;
    SettingsPage* settingsPage;
    DischargerPage* dischargerPage;
    ChargerPage* chargerPage;

public:
    UIManager(LGFX* tft, GT911Touch* touch);
    ~UIManager();

    void begin();
    void update();
    void handleTouch();
    void drawPage();
    void switchPage(Page page);

    // Getter
    Page getCurrentPage() const { return currentPage; }
    int getSelectedAkku() const { return selectedAkku; }
    int getPageNumber() const { return pageNumber; }

    // Für Buttons benötigt
    void handleButtonPress(const String &pageTarget);
    void* getUIManager() { return this; }
    LGFX* getTft() const { return tft; }
};

#endif
