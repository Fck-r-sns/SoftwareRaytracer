#ifndef MATERIAL_H
#define MATERIAL_H

#include "libs/glm/vec3.hpp"

struct Material {
    glm::vec3 ambient = { 0.2, 0.2, 0.2 };
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emission;
    float shininess = 1;
};

#endif // MATERIAL_H
