#ifndef RAY_H
#define RAY_H

#include "libs/glm/vec3.hpp"

class Ray
{
public:
    Ray(const glm::vec3 &origin, const glm::vec3 &direction);
    const glm::vec3 &getOrigin() const;
    const glm::vec3 &getDirection() const;

private:
    glm::vec3 origin;
    glm::vec3 direction;
};

#endif // RAY_H
