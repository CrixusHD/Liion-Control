
#ifndef LIION_CONTROL_BUTTON_H
#define LIION_CONTROL_BUTTON_H

#include <Arduino.h>

#include "display.h"

class Button {
public:
    int x, y, width, height;
    String text;
    String pageTarget;
    int pageNumber;
    bool isAction;

    Button(int x, int y, int width, int height, String text, const String& pageTarget = "m", int pageNumber = 0, bool isAction = false);
    void draw(LGFX* gfx);
    bool isPressed(int touchX, int touchY);
    void setUIManager(void* ui_Manager) { this->uiManager = ui_Manager; }

private:
    void* uiManager; // Referenz auf UIManager
};

#endif //LIION_CONTROL_BUTTON_H