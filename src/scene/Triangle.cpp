#include "Triangle.h"
#include "libs/glm/gtc/matrix_transform.hpp"

Triangle::Triangle(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const Material &material) :
    Primitive(material),
    vertices({v1, v2, v3})
{
}

bool Triangle::findIntersection(const Ray &ray, float &minDist, Intersection &result) const
{
    const glm::vec3 BminusA = vertices[1] - vertices[0];
    const glm::vec3 CminusA = vertices[2] - vertices[0];
    const glm::vec3 n = glm::normalize(glm::cross(BminusA, CminusA));
    const float t = (glm::dot(vertices[0], n) - glm::dot(ray.origin, n)) / glm::dot(ray.direction, n);
    if (t > 0 && t < minDist) {
        const glm::vec3 P = ray.origin + t * ray.direction;
        const glm::vec3 PminusA = P - vertices[0];
        // solve equations: P-A=a(B-A)+b(C-A)
        const float b = (PminusA.y * BminusA.x - PminusA.x * BminusA.y) / (CminusA.y * BminusA.x - CminusA.x * BminusA.y);
        const float a = (PminusA.x - b * CminusA.x) / BminusA.x;
        if ((0 <= a) && (a <= 1)
                && (0 <= b) && (b <= 1)
                && (a + b <= 1)) {
            minDist = t;
            result.t = t;
            result.primitive = this;
            return true;
        }
    }
    return false;
}
