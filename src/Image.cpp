#include "Image.h"
#include <stdexcept>

Image::Image(int width, int height) :
    width(width),
    height(height)
{
    try {
        data = new Pixel[width * height];
        valid = true;
    } catch (std::bad_alloc &e) {
        data = nullptr;
        valid = false;
    }
}

Image::~Image()
{
    delete[] data;
}

Pixel Image::getPixel(int x, int y) const
{
    return data[y * height + x];
}

void Image::setPixel(int x, int y, const Pixel &pixel)
{
    data[y * height + x] = pixel;
}

bool Image::isValid() const
{
    return valid;
}

Pixel *Image::getData()
{
    return data;
}
