#ifndef RAY_H
#define RAY_H

#include "libs/glm/vec3.hpp"

class Ray
{
public:
    Ray(const glm::vec3 &origin, const glm::vec3 &direction);

    const glm::vec3 origin;
    const glm::vec3 direction;
};

#endif // RAY_H
