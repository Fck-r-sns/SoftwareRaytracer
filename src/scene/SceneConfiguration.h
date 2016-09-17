#ifndef SCENECONFIGURATION_H
#define SCENECONFIGURATION_H

#include <string>
#include <vector>
#include <memory>
#include "libs/glm/vec3.hpp"
#include "Material.h"
#include "Primitive.h"

struct SceneConfiguration
{
    struct Camera {
        glm::vec3 lookFrom = { 0, 0, -1 };
        glm::vec3 lookAt = { 0, 0, 0 };
        glm::vec3 up = { 0, 1, 0 };
        int fovy = 45;
    };

    struct Light {
        struct Source {
            glm::vec3 position;
            glm::vec3 color;
        };

        struct Attenuation {
            float constant = 1;
            float linear = 0;
            float quadratic = 0;
        };

        Source directional;
        Source point;
        Attenuation attenuation;
    };

    int width = 0;
    int height = 0;
    int maxDepth = 5;
    std::string outputFileName = "output.png";
    Camera camera;
    Light light;
    std::vector<Material> materials;
    std::vector<glm::vec3> vertices;
    std::vector<std::unique_ptr<Primitive>> primitives;
};

#endif // SCENECONFIGURATION_H
