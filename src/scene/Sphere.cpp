#include "Sphere.h"
#include "libs/glm/gtc/matrix_transform.hpp"

Sphere::Sphere(const glm::vec3 &position, float radius, const Material &material) :
    Primitive(material),
    position(position),
    radius(radius)
{
}

bool Sphere::findIntersection(const Ray &ray, float &minDist, Intersection &result) const
{
    const float a = glm::dot(ray.direction, ray.direction);
    const glm::vec3 PminusC = ray.origin - position;
    const float b = 2 * glm::dot(ray.direction, PminusC);
    const float c = glm::dot(PminusC, PminusC) - radius * radius;
    const float D = b * b - 4 * a * c;
    if (D < 0) {
        return false;
    }
    const float sqrtD = std::sqrt(D);
    const float t1 = (-b - sqrtD) / (2 * a);
    const float t2 = (-b + sqrtD) / (2 * a);
    const float t = (t1 > 0) ? t1 : t2;
    if (t > 0 && t < minDist) {
        minDist = t;
        result.t = t;
        result.primitive = this;
        return true;
    }
    return false;
}
