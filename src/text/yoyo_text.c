#include "yoyo_text.h"
#include "../yoyo_draw.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <freetype2/ft2build.h>
#include <freetype2/freetype/freetype.h>

int draw_text(const struct fb_var_screeninfo *screen, uint8_t *buffer, Rectangle space, const char *text, const char *font, BGRA colour) {
    FT_Library ft;
    if(FT_Init_FreeType(&ft)) {
        fprintf(stderr, "slkdfjc\n");
        return EXIT_FAILURE;
    }

    FT_Face face;
    if(FT_New_Face(ft, font, 0, &face)) {
        fprintf(stderr, "Cant load typeface from \"%s\"\n", font);
        return EXIT_FAILURE;
    }

    if(FT_Set_Pixel_Sizes(face, space.width, space.height)) {
        fprintf(stderr, "unable to provide requested size (%d, %d)\n", space.x, space.y);
        return EXIT_FAILURE;
    }

    for(int i = 0; i < strlen(text); i++) {
        int advance = _draw_char(screen, buffer, &face, (Coord) {space.x, space.y}, text[i], colour);
        if(advance == -1)
            return EXIT_FAILURE;

        space.x += advance;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return EXIT_SUCCESS;
}

int _draw_char(const struct fb_var_screeninfo *screen, uint8_t *buffer, FT_Face *face, Coord location, const FT_ULong character, BGRA colour) {
    FT_UInt gi = FT_Get_Char_Index(*face, character);
    if(!gi) {
        fprintf(stderr, "glyph \"%c\" does not exist in font\n", character);
        return -1;
    }

    if(FT_Load_Glyph(*face, gi, FT_LOAD_DEFAULT)) {
        fprintf(stderr, "failed to load glyph\n");
        return -1;
    }
    FT_Render_Glyph((*face)->glyph, FT_RENDER_MODE_NORMAL);

    int bbox_ymax = (*face)->bbox.yMax >> 6;
    int glyph_width = (*face)->glyph->metrics.width >> 6;
    int advance = (*face)->glyph->metrics.horiAdvance >> 6;
    int x_off = (advance - glyph_width) / 2;
    int y_off = bbox_ymax - ((*face)->glyph->metrics.horiBearingY >> 6);

    for(int i = 0; i < (int)(*face)->glyph->bitmap.rows; i++) {
        int row_offset = location.y + i + y_off;

        for(int j = 0; j < (int)(*face)->glyph->bitmap.width; j++) {
            unsigned char p = (*face)->glyph->bitmap.buffer[i * (*face)->glyph->bitmap.pitch + j];
            if(p)
                draw_pixel(screen, buffer, (Coord) {location.x + j + x_off, row_offset}, colour);
        }
    }

    return advance;
}
