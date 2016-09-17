#include "RayTracer.h"
#include "libs/glm/gtc/matrix_transform.hpp"

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
            findIntersection(ray);
        }
    }
}

void RayTracer::initCamera()
{
    w = glm::normalize(cfg.camera.lookFrom - cfg.camera.lookAt);
    u = glm::normalize(glm::cross(cfg.camera.up, w));
    v = glm::cross(w, u);
    fovx = 2 * std::atan(tan(cfg.camera.fovy / 2) * cfg.width / cfg.height);
}

void RayTracer::findIntersection(const Ray &ray) const
{

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
