#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>
#include "Primitive.h"

class Triangle : public Primitive {
public:
    Triangle(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, int materialIndex, const glm::mat4 &inversedTransform);
    bool findIntersection(const Ray &ray, float &minDist, Intersection &result) const override;

private:
    const std::array<glm::vec3, 3> vertices;
};

#endif // TRIANGLE_H
