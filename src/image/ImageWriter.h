#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H

#include <string>
#include "Image.h"

class ImageWriter
{
public:
    ImageWriter();
    ~ImageWriter();

    bool saveImage(const std::string &fileName, Image &image, int width, int height);
};

#endif // IMAGEWRITER_H
