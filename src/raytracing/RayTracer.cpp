#include "RayTracer.h"
#include "libs/glm/gtc/matrix_transform.hpp"

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
            findIntersection(ray);
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

void RayTracer::findIntersection(const Ray &ray) const
{
    findIntersectionWithTriangles(ray);
}

void RayTracer::findIntersectionWithTriangles(const Ray &ray) const
{
    float minDist = std::numeric_limits<float>::max();
    const SceneConfiguration::Triangle *intersected = nullptr;
    for (const SceneConfiguration::Triangle &triangle : cfg.triangles) {
        const glm::vec3 BminusA = triangle.vertices[1] - triangle.vertices[0];
        const glm::vec3 CminusA = triangle.vertices[2] - triangle.vertices[0];
        const glm::vec3 n = glm::normalize(glm::cross(BminusA, CminusA));
        const float t = (glm::dot(triangle.vertices[0], n) - glm::dot(ray.origin, n)) / glm::dot(ray.direction, n);
        if (t > 0 && t < minDist) {
            const glm::vec3 P = ray.origin + t * ray.direction;
            const glm::vec3 PminusA = P - triangle.vertices[0];
            // solve equations: P-A=a(B-A)+b(C-A)
            const float b = (PminusA.y * BminusA.x - PminusA.x * BminusA.y) / (CminusA.y * BminusA.x - CminusA.x * BminusA.y);
            const float a = (PminusA.x - b * CminusA.x) / BminusA.x;
            if ((0 <= a) && (a <= 1)
                    && (0 <= b) && (b <= 1)
                    && (a + b <= 1)) {
                minDist = t;
                intersected = &triangle;
            }
        }
    }
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
