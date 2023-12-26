#include "yoyo.h"

#include <linux/fb.h>

#include <stddef.h>
#include <stdint.h>

void set_pixel(const struct fb_var_screeninfo *screen, uint8_t *buffer, Coord location, BGRA value) {
    const size_t offset = (location.y * screen->xres + location.x) * 4;

    buffer[offset + 0] = value.b;
    buffer[offset + 1] = value.g;
    buffer[offset + 2] = value.r;
    buffer[offset + 3] = value.a;
}

void set_rect(const struct fb_var_screeninfo *screen, uint8_t *buffer, Rectangle rect, BGRA value) {
    for(uint32_t x = rect.x; x < rect.width + rect.x; x++)
        for(uint32_t y = rect.y; y < rect.height + rect.y; y++)
            set_pixel(screen, buffer, (Coord) {x, y}, value);
}
