#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Material.h"
#include "raytracing/Intersection.h"
#include "raytracing/Ray.h"

class Primitive
{
public:
    Primitive(const Material &material);
    virtual ~Primitive();
    virtual bool findIntersection(const Ray &ray, float &minDist, Intersection &result) const = 0;

public:
    const Material &material;
};

#endif // PRIMITIVE_H
