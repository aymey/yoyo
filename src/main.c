#include <linux/fb.h>
#include <sys/ioctl.h>
// #include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/mman.h>

#include <freetype2/ft2build.h>
#include <freetype2/freetype/freetype.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include "yoyo_draw.h"
#include "text/yoyo_text.h"

#define FB_FILE "/dev/fb0"
#define FONT_FILE "example/font.ttf"

int main(void) {
    if(getuid()) {
        fprintf(stderr, "run as root\n");
        return EXIT_FAILURE;
    }

    int fbfd = open(FB_FILE, O_RDWR);

    if(!fbfd) {
        fprintf(stderr, "unable to open \"%s\"\n", FB_FILE);
        return EXIT_FAILURE;
    }

    const struct fb_var_screeninfo screen;
    ioctl(fbfd, FBIOGET_VSCREENINFO, &screen);
    int fb_Bpp = screen.bits_per_pixel / 8;
    int fb_size = screen.xres * screen.yres * fb_Bpp;

    uint8_t *fbdata = mmap(NULL, fb_size,
            PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, (off_t)0
        );


    // draw_rect(&screen, fbdata, (Rectangle) {0, 0, 1000, 1000}, (BGRA) {100, 100, 100, 0});

    draw_text(&screen, fbdata, (Rectangle) {500, 500, 50, 50}, "abcdef", FONT_FILE, (BGRA) {255, 255, 255, 0});

    munmap(fbdata, fb_size);
    close(fbfd);
    return EXIT_SUCCESS;
}
