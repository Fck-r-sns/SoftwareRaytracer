#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <limits>
#include "libs/glm/vec3.hpp"

class Primitive;

class Intersection
{
public:
    Intersection();

public:
    bool empty = true;
    float t = std::numeric_limits<float>::max();
    glm::vec3 point;
    const Primitive *primitive = nullptr;
};

#endif // INTERSECTION_H
