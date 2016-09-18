#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "libs/glm/vec3.hpp"
#include "image/Image.h"
#include "scene/SceneConfiguration.h"
#include "Ray.h"

class RayTracer
{
public:
    RayTracer(const SceneConfiguration &cfg);
    void run(Image &outputImage);

private:
    void initCamera();
    Ray getRayFromCameraToPixel(int pixelXIndex, int pixelYIndex) const;
    Ray getRayFromPointToPoint(const glm::vec3 &from, const glm::vec3 &to) const;
    Ray getReflectedRay(const glm::vec3 &direction, const glm::vec3 &reflectionPoint, const glm::vec3 &normal) const;
    Intersection findIntersection(const Ray &ray, bool countRecursion) const;
    glm::vec3 getColorFromIntersection(const Intersection &intersection) const;
    glm::vec3 processLightSource(const Intersection &intersection,
            const SceneConfiguration::Light::Source &lightSource,
            const Material &material,
            const glm::vec3 &directionToTheLight,
            bool checkDistanceToLightSourceForShadows) const;

private:
    const SceneConfiguration &cfg;
    // camera coordinate frame
    glm::vec3 w;
    glm::vec3 u;
    glm::vec3 v;
    float fovx;
    mutable int recursionDepth = 0;
};

#endif // RAYTRACER_H
