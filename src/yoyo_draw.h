#ifndef __YOYO_DRAW_H__
#define __YOYO_DRAW_H__

#include <linux/fb.h>

#include <stddef.h>
#include <stdint.h>

// TODO: support both 8 and u32 mem mapping for the fb via translation functions, but primarily use u32 for writing since its faster;

// TODO: something like double buffering so we can render everything at once per frame

typedef struct {
    uint8_t b;
    uint8_t g;
    uint8_t r;
    uint8_t a;
} BGRA;

typedef struct {
    uint32_t x;
    uint32_t y;
} Coord;

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
} Rectangle;

void draw_pixel(const struct fb_var_screeninfo *screen, uint8_t *buffer, Coord location, BGRA value);
void draw_rect(const struct fb_var_screeninfo *screen, uint8_t *buffer, Rectangle rect, BGRA value);

#endif // __YOYO_DRAW_H__
