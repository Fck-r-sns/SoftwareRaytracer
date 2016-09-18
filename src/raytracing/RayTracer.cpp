#include <iostream>
#include "RayTracer.h"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "scene/Triangle.h"

const float PI = std::acos(-1);
const float radiansToDegreesCoef = 180 / PI;
const float degreesToRadiansCoef = PI / 180;

RayTracer::RayTracer(const SceneConfiguration &cfg) :
    cfg(cfg)
{
}

void RayTracer::run(Image &outputImage)
{
    initCamera();
    const int w = cfg.width;
    const int h = cfg.height;
    const int totalPixels = w * h;
    int pixelCounter = 0;
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            ++pixelCounter;
            if (pixelCounter % 1000 == 0) {
                std::cout << pixelCounter << "/" << totalPixels << std::endl;
            }
            const Ray ray = getRayFromCameraToPixel(x, y);
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
    float fovx = std::tan((float)cfg.camera.fovy / 2 * degreesToRadiansCoef);
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
        const glm::mat4 &invTransform = primitive->inversedTransform;
        const glm::vec3 newOrigin = invTransform * glm::vec4(ray.origin, 1);
        const glm::vec3 newDirection = invTransform * glm::vec4(ray.direction, 0);
        found = primitive->findIntersection(Ray(newOrigin, newDirection), minDist, result) || found;
    }
    return found;
}

Pixel RayTracer::getColorFromIntersection(const Intersection &intersection) const
{
    glm::vec3 color;
    const Material &material = cfg.materials.at(intersection.primitive->materialIndex);
    color += material.ambient;
    color += material.emission;

    if (cfg.light.point.enabled) {
        const SceneConfiguration::Light::Source &lightSource = cfg.light.point;
        const Ray rayToLight = getRayFromPointToPoint(intersection.point, lightSource.position);
        Intersection shadowIntersection;
        const bool isShadowed = findIntersection(rayToLight, shadowIntersection);

        if (!isShadowed) {
            //    const glm::vec3 directionToTheLight = glm::normalize(lightSource.position - intersection.point);
            //    const float distanceToTheLight = glm::distance(lightSource.position, intersection.point);
            //    const float attenuation =
            //            cfg.light.attenuation.constant
            //            + cfg.light.attenuation.linear * distanceToTheLight
            //            + cfg.light.attenuation.quadratic * distanceToTheLight * distanceToTheLight;
            color = glm::vec3(1, 1, 1);
        } else {
            color = glm::vec3(0, 0, 0);
        }
    }

    return Pixel(color.r * 255, color.g * 255, color.b * 255);
}

Ray RayTracer::getRayFromCameraToPixel(int pixelXIndex, int pixelYIndex) const
{
    const float pixelXPos = pixelXIndex + 0.5; // center of pixel
    const float pixelYPos = pixelYIndex + 0.5; // center of pixel
    const float a = std::tan(fovx / 2 * degreesToRadiansCoef) * (2 * pixelXPos - cfg.width) / cfg.width;
    const float b = std::tan(cfg.camera.fovy / 2.0 * degreesToRadiansCoef) * (cfg.height - 2 * pixelYPos) / cfg.height;
    const glm::vec3 direction = glm::normalize(a * u + b * v - w);
    return Ray(cfg.camera.lookFrom, direction);
}

Ray RayTracer::getRayFromPointToPoint(const glm::vec3 &from, const glm::vec3 &to) const
{
    return Ray(from, glm::normalize(to - from));
}
