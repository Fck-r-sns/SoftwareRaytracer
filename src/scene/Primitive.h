#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Material.h"
#include "raytracing/Intersection.h"
#include "raytracing/Ray.h"
#include "libs/glm/mat4x4.hpp"

class Primitive
{
public:
    Primitive(int materialIndex);
    virtual ~Primitive();
    virtual Intersection findIntersection(const Ray &ray, float &minDist) const = 0;

public:
    const int materialIndex;
    glm::mat4 directTransform;
    glm::mat4 inversedTransform;
    glm::mat3 normalTransform;
};

#endif // PRIMITIVE_H
