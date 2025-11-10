#ifndef LIION_CONTROL_BUTTON_H
#define LIION_CONTROL_BUTTON_H

#include <Arduino.h>
#include "display.h"

// Forward declaration
class UIManager;

class Button {
public:
    int x, y, width, height;
    String text;
    String pageTarget;
    bool disabled;

    Button(int x, int y, int width, int height, String text, const String& pageTarget = "m", bool disabled = false);
    virtual void draw(LGFX* gfx);
    virtual bool isPressed(int touchX, int touchY);
};

class PagingButton : public Button {
public:
    PagingButton(int x, int y, int width, int height, String text, const String& pageTarget);
    void draw(LGFX* gfx) override;
    bool isPressed(int touchX, int touchY) override;
    void setUIManager(UIManager* ui_Manager) { this->uiManager = ui_Manager; }

protected:
    UIManager* uiManager; // Referenz auf UIManager
};
#endif //LIION_CONTROL_BUTTON_H
