#ifndef IMAGE_H
#define IMAGE_H

#include "defines.h"

class Image
{
public:
    Image(int width, int height);
    ~Image();
    Pixel getPixel(int x, int y) const;
    void setPixel(int x, int y, const Pixel &pixel);
    bool isValid() const;
    Pixel *getData();

private:
    Pixel *data = nullptr;
    int width;
    int height;
    bool valid = false;
};

#endif // IMAGE_H
