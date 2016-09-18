#include <iostream>
#include <ctime>
#include <chrono>
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

    time_t started = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "started: " << ctime(&started);

    const std::string inputFileName = argv[1];
    SceneConfiguration cfg = Parser::parse(inputFileName);
    Image image(cfg.width, cfg.height);
    RayTracer rayTracer(cfg);
    rayTracer.run(image);
    ImageWriter().saveImage(cfg.outputFileName, image, cfg.width, cfg.height);

    time_t finished = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << "started: " << ctime(&started);
    std::cout << "finished: " << ctime(&finished);

    return 0;
}
