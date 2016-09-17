#include <iostream>
#include "scene/SceneConfiguration.h"
#include "scene/Parser.h"
#include "image/Image.h"
#include "raytracing/RayTracer.h"
#include "image/ImageWriter.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        return 1;
    }
    const std::string inputFileName = argv[1];
    SceneConfiguration cfg = Parser::parse(inputFileName);
    Image image(cfg.width, cfg.height);
    RayTracer rayTracer(cfg);
    rayTracer.run(image);
    ImageWriter().saveImage("test.png", image, cfg.width, cfg.height);
    return 0;
}
