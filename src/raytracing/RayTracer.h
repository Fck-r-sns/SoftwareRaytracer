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
    Ray getRay(int pixelXIndex, int pixelYIndex) const;
    bool findIntersection(const Ray &ray, Intersection &result) const;
    Pixel getColorFromIntersection(const Intersection &intersection) const;

private:
    const SceneConfiguration &cfg;
    // camera coordinate frame
    glm::vec3 w;
    glm::vec3 u;
    glm::vec3 v;
    float fovx;
};

#endif // RAYTRACER_H
