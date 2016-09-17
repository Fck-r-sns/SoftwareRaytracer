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
    FIBITMAP *img = FreeImage_ConvertFromRawBits(bytes, width, height, width * 3, 24, 0xff0000, 0x00ff00, 0x0000ff, false);
    const bool isOk = FreeImage_Save(FIF_PNG, img, fileName.c_str(), 0);
    return isOk;
}
