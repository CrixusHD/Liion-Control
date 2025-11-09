#include "helper/drawing_helper.h"
#include "color_space.h"
#include "display.h"

void draw_base_page(LGFX* gfx, const String &title) {
    gfx->writeFastHLine(0, 70, 800, MAIN_FONT_COLOR);
    gfx->writeFastHLine(0, 71, 800, MAIN_FONT_COLOR);
    gfx->writeFastHLine(0, 72, 800, MAIN_FONT_COLOR);
    // Titel
    gfx->setCursor(300, 20);
    gfx->print(title);
}

void draw_split_page(LGFX* gfx, const String &title) {
    draw_base_page(gfx, title);
    gfx->writeFastVLine(499, 70, 480, MAIN_FONT_COLOR);
    gfx->writeFastVLine(500, 70, 480, MAIN_FONT_COLOR);
    gfx->writeFastVLine(501, 70, 480, MAIN_FONT_COLOR);
}

void draw_button(LGFX* gfx, const int x, const int y, const int width, const int height, const String &text) {
    // Zeichne Button-Rahmen
    gfx->drawRect(x, y, width, height, MAIN_BUTTON_LINE_COLOR);

    // Zeichne Button-Inhalt
    gfx->setCursor(x + 10, y + (height / 2) - 10);
    gfx->print(text);
}

void clear_header(LGFX* gfx) {
    // Alten Header Bereich übermalen (ab y=0 bis y=72)
    gfx->fillRect(0, 0, 800, 72, TFT_WHITE);
}
