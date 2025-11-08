#include "ui/button.h"
#include "helper/drawing_helper.h"
// Button Implementation
Button::Button(int x, int y, int width, int height, String text, const String &pageTarget, int pageNumber, bool isAction)
    : x(x), y(y), width(width), height(height), text(text), pageTarget(pageTarget), pageNumber(pageNumber), isAction(isAction), uiManager(nullptr) {}

void Button::draw(LGFX* gfx) {
    draw_button(gfx, x, y, width, height, text);
}

bool Button::isPressed(int touchX, int touchY) {
    return (touchX > x && touchX < (x + width) && 
            touchY > y && touchY < (y + height));
}
