#include <linux/fb.h>
#include <sys/ioctl.h>
// #include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/mman.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

#include "yoyo.h"

#define FB_FILE "/dev/fb0"

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


    // memset(fbdata, 10, fb_size);

    // set_rect(&screen, fbdata, (Rectangle) {0, 0, 1000, 1000}, (BGRA) {100, 100, 100, 0});
    for(int i = 0; i < 1000; i++)
        for(int j = 0; j < 1000; j++)
            set_pixel(&screen, fbdata, (Coord) {i, j}, (BGRA) {j-i, j*i, i+j, 0});


    munmap(fbdata, fb_size);
    close(fbfd);
    return EXIT_SUCCESS;
}
