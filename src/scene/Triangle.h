#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>
#include "Primitive.h"

class Triangle : public Primitive {
public:
    Triangle(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, int materialIndex, const glm::mat4 &inversedTransform);
    Intersection findIntersection(const Ray &ray, float &minDist) const override;

private:
    const glm::vec3 A;
    const glm::vec3 B;
    const glm::vec3 C;
    const glm::vec3 normal;
};

#endif // TRIANGLE_H
