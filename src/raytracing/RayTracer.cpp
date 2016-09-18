#include <iostream>
#include "RayTracer.h"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "scene/Triangle.h"

const float PI = std::acos(-1);
const float radiansToDegreesCoef = 180 / PI;
const float degreesToRadiansCoef = PI / 180;
const float EPSILON = std::numeric_limits<float>::epsilon() * 2000;

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
            recursionDepth = 0;
            const Ray ray = getRayFromCameraToPixel(x, y);
            const Intersection intersection = findIntersection(ray, true);
            const glm::vec3 color = !intersection.empty ? getColorFromIntersection(intersection) : glm::vec3();
            outputImage.setPixel(x, y, Pixel(color.r * 255, color.g * 255, color.b * 255));
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

Intersection RayTracer::findIntersection(const Ray &ray, bool countRecursion) const
{
    if (countRecursion) {
        if (recursionDepth >= cfg.maxDepth) {
            return Intersection::EMPTY;
        }
        ++recursionDepth;
    }
    float minDist = std::numeric_limits<float>::max();
    Intersection result;
    for (const auto &primitive : cfg.primitives) {
        const glm::mat4 &invTransform = primitive->inversedTransform;
        const glm::vec3 newOrigin = invTransform * glm::vec4(ray.origin, 1);
        const glm::vec3 newDirection = invTransform * glm::vec4(ray.direction, 0);
        const Ray transformedRay(newOrigin, newDirection);
        const Intersection intersection = primitive->findIntersection(transformedRay, minDist);
        if (!intersection.empty && intersection.t < result.t) {
            result = intersection;
            result.eyePosition = ray.origin;
            result.eyeDirection = ray.direction;
        }
    }
    if (!result.empty) {
        result.point = result.primitive->directTransform * glm::vec4(result.point, 1);
        result.normal = glm::normalize(result.primitive->normalTransform * result.normal);
    }
    return result;
}

glm::vec3 RayTracer::getColorFromIntersection(const Intersection &intersection) const
{
    glm::vec3 color;
    const Material &material = cfg.materials.at(intersection.primitive->materialIndex);
    color += material.ambient;
    color += material.emission;

    if (cfg.light.point.enabled) {
        color += processLightSource(intersection, cfg.light.point, material, glm::normalize(cfg.light.point.coordinate - intersection.point));
    }
    if (cfg.light.directional.enabled) {
        color += processLightSource(intersection, cfg.light.directional, material, glm::normalize(cfg.light.directional.coordinate));
    }
    const Ray reflectedRay = getReflectedRay(intersection.eyeDirection, intersection.point + EPSILON * intersection.normal, intersection.normal);
    Intersection reflection = findIntersection(reflectedRay, true);
    if (!reflection.empty) {
        color += material.specular * getColorFromIntersection(reflection);
    }

    return color;
}

glm::vec3 RayTracer::processLightSource(const Intersection &intersection, const SceneConfiguration::Light::Source &lightSource, const Material &material, const glm::vec3 &directionToTheLight) const
{
    const Ray rayToLight = getRayFromPointToPoint(intersection.point + EPSILON * intersection.normal, lightSource.coordinate);
    const Intersection shadowIntersection = findIntersection(rayToLight, false);

    if (shadowIntersection.empty) {
        const float distanceToTheLight = glm::distance(lightSource.coordinate, intersection.point);
        const float attenuation =
                cfg.light.attenuation.constant
                + cfg.light.attenuation.linear * distanceToTheLight
                + cfg.light.attenuation.quadratic * distanceToTheLight * distanceToTheLight;
        const glm::vec3 diffuseColor = material.diffuse * std::max(glm::dot(directionToTheLight, intersection.normal), 0.0f);
        const glm::vec3 halfVec = glm::normalize(glm::normalize(intersection.eyePosition - intersection.point) + directionToTheLight);
        const glm::vec3 specularColor = material.specular * std::pow(std::max(glm::dot(halfVec, intersection.normal), 0.0f), material.shininess);
        return lightSource.color / attenuation * (diffuseColor + specularColor);
    }
    return glm::vec3();
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

Ray RayTracer::getReflectedRay(const glm::vec3 &direction, const glm::vec3 &reflectionPoint, const glm::vec3 &normal) const
{
    return Ray(reflectionPoint, glm::normalize(direction - 2 * glm::dot(direction, normal) * normal));
}
