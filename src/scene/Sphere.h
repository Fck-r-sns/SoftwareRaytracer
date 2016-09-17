#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"

class Sphere : public Primitive
{
public:
    Sphere(const glm::vec3 &position, float radius, int materialIndex);
    bool findIntersection(const Ray &ray, float &minDist, Intersection &result) const override;

private:
    const glm::vec3 position;
    const float radius;
};

#endif // SPHERE_H
