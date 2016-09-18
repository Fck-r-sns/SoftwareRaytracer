#include "Triangle.h"
#include "libs/glm/gtc/matrix_transform.hpp"

Triangle::Triangle(const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3, int materialIndex, const glm::mat4 &inversedTransform) :
    Primitive(materialIndex, inversedTransform),
    A(v1),
    B(v2),
    C(v3),
    normal(glm::normalize(glm::cross(B - A, C - A)))
{
}

Intersection Triangle::findIntersection(const Ray &ray, float &minDist) const
{
    const glm::vec3 BminusA = B - A;
    const glm::vec3 CminusA = C - A;
    const float t = (glm::dot(A, normal) - glm::dot(ray.origin, normal)) / glm::dot(ray.direction, normal);
    if (t > 0 && t < minDist) {
        const glm::vec3 P = ray.origin + t * ray.direction;
        const glm::vec3 PminusA = P - A;
        // solve equations: P-A=a(B-A)+b(C-A)
        // TODO: refactor this shit
        float PminusA_1;
        float PminusA_2;
        float BminusA_1;
        float BminusA_2;
        float CminusA_1;
        float CminusA_2;
        bool ready = false;
        if (!ready && BminusA.x != 0.0) {
            PminusA_1 = PminusA.x;
            BminusA_1 = BminusA.x;
            CminusA_1 = CminusA.x;
            if (CminusA.y != 0.0) {
                PminusA_2 = PminusA.y;
                BminusA_2 = BminusA.y;
                CminusA_2 = CminusA.y;
                ready = true;
            } else if (CminusA.z != 0.0) {
                PminusA_2 = PminusA.z;
                BminusA_2 = BminusA.z;
                CminusA_2 = CminusA.z;
                ready = true;
            }
        }
        if (!ready && BminusA.y != 0) {
            PminusA_1 = PminusA.y;
            BminusA_1 = BminusA.y;
            CminusA_1 = CminusA.y;
            if (CminusA.x != 0.0) {
                PminusA_2 = PminusA.x;
                BminusA_2 = BminusA.x;
                CminusA_2 = CminusA.x;
                ready = true;
            } else if (CminusA.z != 0.0) {
                PminusA_2 = PminusA.z;
                BminusA_2 = BminusA.z;
                CminusA_2 = CminusA.z;
                ready = true;
            }
        }
        if (!ready && BminusA.z != 0) {
            PminusA_1 = PminusA.z;
            BminusA_1 = BminusA.z;
            CminusA_1 = CminusA.z;
            if (CminusA.x != 0.0) {
                PminusA_2 = PminusA.x;
                BminusA_2 = BminusA.x;
                CminusA_2 = CminusA.x;
                ready = true;
            } else if (CminusA.y != 0.0) {
                PminusA_2 = PminusA.y;
                BminusA_2 = BminusA.y;
                CminusA_2 = CminusA.y;
                ready = true;
            }
        }
        if (!ready) {
            return Intersection::EMPTY;
        }
        const float b1 = (PminusA_2 * BminusA_1 - PminusA_1 * BminusA_2);
        const float b2 = (CminusA_2 * BminusA_1 - CminusA_1 * BminusA_2);
        const float b = b1 / b2;
        const float a = (PminusA_1 - b * CminusA_1) / BminusA_1;
        if ((0 <= a) && (a <= 1)
                && (0 <= b) && (b <= 1)
                && (a + b <= 1)) {
            minDist = t;
            Intersection result;
            result.t = t;
            result.point = P;
            result.normal = normal;
            result.primitive = this;
            result.empty = false;
            return result;
        }
    }
    return Intersection::EMPTY;
}
