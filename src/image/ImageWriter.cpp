#include "ImageWriter.h"
#include "libs/FreeImage/FreeImage.h"

ImageWriter::ImageWriter()
{
    FreeImage_Initialise();
}

ImageWriter::~ImageWriter()
{
    FreeImage_DeInitialise();
}

bool ImageWriter::saveImage(const std::string &fileName, Image &image, int width, int height)
{
    BYTE *bytes = reinterpret_cast<BYTE*>(image.getData());
    FIBITMAP *img = FreeImage_ConvertFromRawBits(bytes, width, height, width * 3, 24, 0, 0, 0, true);
    return FreeImage_Save(FIF_PNG, img, fileName.c_str(), 0);
}
