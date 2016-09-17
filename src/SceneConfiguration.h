#ifndef SCENECONFIGURATION_H
#define SCENECONFIGURATION_H

#include <string>
#include "libs/glm/vec3.hpp"

class SceneConfiguration
{
public:
    SceneConfiguration();

    int width = 0;
    int height = 0;
    int maxDepth = 5;
    std::string outputFileName = "output.png";

    class Camera {
        glm::vec3 lookFrom = { 0, 0, -1 };
        glm::vec3 lookAt = { 0, 0, 0 };
        glm::vec3 up = { 0, 1, 0 };
        int fov = 45;
    } camera;


};

#endif // SCENECONFIGURATION_H
