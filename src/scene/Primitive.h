#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Material.h"
#include "raytracing/Intersection.h"
#include "raytracing/Ray.h"
#include "libs/glm/mat4x4.hpp"

class Primitive
{
public:
    Primitive(int materialIndex, const glm::mat4 &inversedTransform);
    virtual ~Primitive();
    virtual bool findIntersection(const Ray &ray, float &minDist, Intersection &result) const = 0;

public:
    const int materialIndex;
    const glm::mat4 inversedTransform;
};

#endif // PRIMITIVE_H
