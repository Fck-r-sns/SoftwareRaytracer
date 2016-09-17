#include <iostream>
#include "RayTracer.h"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "scene/Triangle.h"

const float PI = std::acos(-1);
const float radiansToDegreesCoef = 180 / PI;

RayTracer::RayTracer(const SceneConfiguration &cfg) :
    cfg(cfg)
{
}

void RayTracer::run(Image &outputImage)
{
    initCamera();
    const int w = cfg.width;
    const int h = cfg.height;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            Ray ray = getRay(x, y);
            Intersection intersection;
            const bool intersected = findIntersection(ray, intersection);
            const Pixel pixel = intersected ? getColorFromIntersection(intersection) : Pixel();
            outputImage.setPixel(x, y, pixel);
        }
    }
}

void RayTracer::initCamera()
{
    w = glm::normalize(cfg.camera.lookFrom - cfg.camera.lookAt);
    u = glm::normalize(glm::cross(cfg.camera.up, w));
    v = glm::cross(w, u);
    float fovx = std::tan((float)cfg.camera.fovy / 2 / radiansToDegreesCoef);
    fovx *= cfg.width / (float)cfg.height;
    fovx = 2 * std::atan(fovx);
    fovx = fovx * radiansToDegreesCoef;
    this->fovx = fovx;
}

bool RayTracer::findIntersection(const Ray &ray, Intersection &result) const
{
    float minDist = std::numeric_limits<float>::max();
    bool found = false;
    for (const auto &primitive : cfg.primitives) {
        found = primitive->findIntersection(ray, minDist, result);
    }
    return found;
}

Pixel RayTracer::getColorFromIntersection(const Intersection &intersection) const
{
    const glm::vec3 &diffuse = intersection.primitive->material.diffuse;
    return Pixel(diffuse.r * 255, diffuse.g * 255, diffuse.b * 255);
}

Ray RayTracer::getRay(int pixelXIndex, int pixelYIndex) const
{
    const float pixelXPos = pixelXIndex + 0.5; // center of pixel
    const float pixelYPos = pixelYIndex + 0.5; // center of pixel
    const float a = std::tan(fovx / 2) * (2 * pixelXPos - cfg.width) / cfg.width;
    const float b = std::tan(cfg.camera.fovy / 2) * (cfg.height - 2 * pixelYPos) / cfg.height;
    const glm::vec3 direction = glm::normalize(a * u + b * v - w);
    return Ray(cfg.camera.lookFrom, direction);
}
