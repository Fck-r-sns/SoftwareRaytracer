#include <iostream>
#include "Image.h"
#include "ImageWriter.h"
#include "SceneConfiguration.h"
#include "Parser.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }
    const std::string inputFileName = argv[1];
    SceneConfiguration cfg = Parser::parse(inputFileName);
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
