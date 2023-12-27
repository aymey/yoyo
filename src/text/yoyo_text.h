#ifndef __YOYO_TEXT_H__
#define __YOYO_TEXT_H__

#include "../yoyo_draw.h"

#include <freetype2/ft2build.h>
#include <freetype2/freetype/freetype.h>

int draw_text(const struct fb_var_screeninfo *screen, uint8_t *buffer, Rectangle space, const char *text, const char *font, BGRA colour); // int to propogate errors
int _draw_char(const struct fb_var_screeninfo *screen, uint8_t *buffer, FT_Face *face, Coord location, const FT_ULong character, BGRA colour);


#endif // __YOYO_TEXT_H__
