#include "ui/button.h"
#include "helper/drawing_helper.h"

// Button Implementation
Button::Button(int x, int y, int width, int height, String text, const String &pageTarget, bool disabled)
    : x(x), y(y), width(width), height(height), text(text), pageTarget(pageTarget), disabled(disabled), uiManager(nullptr) {}

void Button::draw(LGFX* gfx) {
    if (disabled) {
        // Zeichne deaktivierten Button (z.B. grau)
        gfx->fillRect(x, y, width, height, TFT_LIGHTGREY);
        gfx->drawRect(x, y, width, height, TFT_BLACK);
    } else {
        draw_button(gfx, x, y, width, height, text);
    }
}

bool Button::isPressed(int touchX, int touchY) {
    if (disabled) return false;
    return (touchX > x && touchX < (x + width) &&
            touchY > y && touchY < (y + height));
}

// PagingButton Implementation
PagingButton::PagingButton(int x, int y, int width, int height, String text, const String& pageTarget)
    : Button(x, y, width, height, text, pageTarget) {}

void PagingButton::draw(LGFX* gfx) {
    Button::draw(gfx);
}

bool PagingButton::isPressed(int touchX, int touchY) {
    if (Button::isPressed(touchX, touchY) && uiManager != nullptr) {
        uiManager->handleButtonPress(pageTarget);
        return true;
    }
    return Button::isPressed(touchX, touchY);
}

// ActionButton Implementation
ActionButton::ActionButton(int x, int y, int width, int height, String text, ActionFunction action, void* param)
    : Button(x, y, width, height, text), action(action), param(param) {}

void ActionButton::draw(LGFX* gfx) {
    Button::draw(gfx);
}

bool ActionButton::isPressed(int touchX, int touchY) {
    if (Button::isPressed(touchX, touchY) && uiManager != nullptr) {
        executeAction();
        return true;
    }
    return Button::isPressed(touchX, touchY);
}

void ActionButton::executeAction() {
    if (action != nullptr) {
        action(param);
    }
}
