#include "ui/button.h"

#include "ui_manager.h"
#include "helper/drawing_helper.h"

// Button Implementation
Button::Button(int x, int y, int width, int height, String text, const String& pageTarget)
    : x(x), y(y), width(width), height(height), text(text), pageTarget(pageTarget)
{
}

void Button::draw(LGFX* gfx)
{
    draw_button(gfx, x, y, width, height, text, disabled);
}

bool Button::isPressed(int touchX, int touchY)
{
    if (disabled) return false;
    return (touchX > x && touchX < (x + width) &&
        touchY > y && touchY < (y + height));
}

// PagingButton Implementation
PagingButton::PagingButton(int x, int y, int width, int height, String text, const String& pageTarget,
                           UIManager* uiManager)
    : Button(x, y, width, height, text, pageTarget), uiManager(uiManager)
{
}

void PagingButton::draw(LGFX* gfx)
{
    Button::draw(gfx);
}

bool PagingButton::isPressed(int touchX, int touchY)
{
    if (Button::isPressed(touchX, touchY) && uiManager != nullptr)
    {
        uiManager->handleButtonPress(pageTarget);
        return true;
    }
    return Button::isPressed(touchX, touchY);
}
