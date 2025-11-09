#ifndef DRAWING_HELPER_H
#define DRAWING_HELPER_H

#include <LovyanGFX.hpp>

// Forward declaration
class LGFX;

void draw_base_page(LGFX* gfx, const String &title);
void draw_split_page(LGFX* gfx, const String &title);
void draw_button(LGFX* gfx, const int x, const int y, const int width, const int height, const String &text);
void clear_header(LGFX* gfx);

#endif
