#ifndef DEFINES_H
#define DEFINES_H

#include <stdint.h>

using PixelColor = uint8_t;

struct Pixel {
    PixelColor r;
    PixelColor g;
    PixelColor b;

    Pixel(PixelColor r, PixelColor g, PixelColor b) :
        r(r), g(g), b(b)
    {}

    Pixel() :
        Pixel(0, 0, 0)
    {}
};

#endif // DEFINES_H
