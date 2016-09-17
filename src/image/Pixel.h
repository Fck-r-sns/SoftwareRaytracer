#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>

using PixelColor = uint8_t;

struct Pixel {
    // BGR color order
    PixelColor b;
    PixelColor g;
    PixelColor r;

    Pixel(PixelColor r, PixelColor g, PixelColor b) :
        b(b), g(g), r(r)
    {}

    Pixel() :
        Pixel(0, 0, 0)
    {}
};

#endif // PIXEL_H
