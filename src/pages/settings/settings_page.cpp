#include "ui_manager.h"
#include "helper/drawing_helper.h"

// SettingsPage Implementation
SettingsPage::SettingsPage(UIManager* uiManager) : SecondPageBase(uiManager, "m")
{
    setUIManager(uiManager);
    backButton = new PagingButton(20, 2, 120, 60, "Back", "m", uiManager);
    chargerButton = new PagingButton(20, 120, 200, 60, "Charge", "s-c", uiManager);
    dischargerButton = new PagingButton(20, 200, 200, 60, "Discharge", "s-d", uiManager);
}

SettingsPage::~SettingsPage()
{
    delete backButton;
    delete chargerButton;
    delete dischargerButton;
}

void SettingsPage::draw(LGFX* gfx)
{
    // Seitenlayout
    draw_base_page(gfx, "Settings Page");

    // Back Button
    backButton->draw(gfx);

    chargerButton->draw(gfx);
    dischargerButton->draw(gfx);
}

void SettingsPage::handleTouch(int touchX, int touchY)
{
    backButton->isPressed(touchX, touchY);
    chargerButton->isPressed(touchX, touchY);
    dischargerButton->isPressed(touchX, touchY);
}

void SettingsPage::saveAddress()
{
    // Adresse speichern
}

void SettingsPage::saveChargerAddress()
{
    // Charger Adresse speichern
}
