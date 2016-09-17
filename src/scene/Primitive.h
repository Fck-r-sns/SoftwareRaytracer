#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Material.h"
#include "raytracing/Intersection.h"
#include "raytracing/Ray.h"

class Primitive
{
public:
    Primitive(int materialIndex);
    virtual ~Primitive();
    virtual bool findIntersection(const Ray &ray, float &minDist, Intersection &result) const = 0;

public:
    const int materialIndex;
};

#endif // PRIMITIVE_H
