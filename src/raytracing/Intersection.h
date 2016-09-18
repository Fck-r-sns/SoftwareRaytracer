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
    glm::vec3 normal;
    const Primitive *primitive = nullptr;
    static const Intersection EMPTY;
};

#endif // INTERSECTION_H
