#include "Triangle.h"
#include "libs/glm/gtc/matrix_transform.hpp"

Triangle::Triangle(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, const Material &material) :
    Primitive(material),
    vertices({v1, v2, v3})
{
}

bool Triangle::findIntersection(const Ray &ray, float &minDist, Intersection &result) const
{
    const glm::vec3 &A = vertices[0];
    const glm::vec3 &B = vertices[1];
    const glm::vec3 &C = vertices[2];
    const glm::vec3 BminusA = B - A;
    const glm::vec3 CminusA = C - A;
    const glm::vec3 n = glm::normalize(glm::cross(BminusA, CminusA));
    const float t = (glm::dot(A, n) - glm::dot(ray.origin, n)) / glm::dot(ray.direction, n);
    if (t > 0 && t < minDist) {
        const glm::vec3 P = ray.origin + t * ray.direction;
        const glm::vec3 PminusA = P - A;
        // solve equations: P-A=a(B-A)+b(C-A)
        float PminusA_1;
        float PminusA_2;
        float BminusA_1;
        float BminusA_2;
        float CminusA_1;
        float CminusA_2;
        if (BminusA.x != 0.0) {
            PminusA_1 = PminusA.x;
            BminusA_1 = BminusA.x;
            CminusA_1 = CminusA.x;
            if (CminusA.y != 0.0) {
                PminusA_2 = PminusA.y;
                BminusA_2 = BminusA.y;
                CminusA_2 = CminusA.y;
            } else {
                PminusA_2 = PminusA.z;
                BminusA_2 = BminusA.z;
                CminusA_2 = CminusA.z;
            }
        } else if (BminusA.y != 0) {
            PminusA_1 = PminusA.y;
            BminusA_1 = BminusA.y;
            CminusA_1 = CminusA.y;
            if (CminusA.x != 0.0) {
                PminusA_2 = PminusA.x;
                BminusA_2 = BminusA.x;
                CminusA_2 = CminusA.x;
            } else {
                PminusA_2 = PminusA.z;
                BminusA_2 = BminusA.z;
                CminusA_2 = CminusA.z;
            }
        } else if (BminusA.z != 0) {
            PminusA_1 = PminusA.z;
            BminusA_1 = BminusA.z;
            CminusA_1 = CminusA.z;
            if (CminusA.x != 0.0) {
                PminusA_2 = PminusA.x;
                BminusA_2 = BminusA.x;
                CminusA_2 = CminusA.x;
            } else {
                PminusA_2 = PminusA.y;
                BminusA_2 = BminusA.y;
                CminusA_2 = CminusA.y;
            }
        } else {
            return false;
        }
        const float b1 = (PminusA_2 * BminusA_1 - PminusA_1 * BminusA_2);
        const float b2 = (CminusA_2 * BminusA_1 - CminusA_1 * BminusA_2);
        const float b = b1 / b2;
        const float a = (PminusA_1 - b * CminusA_1) / BminusA_1;
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
