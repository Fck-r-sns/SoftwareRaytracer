#include <iostream>
#include "Image.h"
#include "ImageWriter.h"

int main(int argc, char *argv[])
{
    const int w = 256;
    const int h = 256;
    Image image(w, h);
    for (int row = 0; row < h; ++row) {
        for (int column = 0; column < w; ++column) {
            image.setPixel(row, column, Pixel(column, row, (column + row) / 2));
        }
    }
    ImageWriter().saveImage("test.png", image, w, h);
    return 0;
}
