#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include "Parser.h"
#include "Transform.h"
#include "Triangle.h"
#include "Sphere.h"

SceneConfiguration Parser::parse(const std::string &fileName)
{
    SceneConfiguration cfg;
    Material *currentMaterial = nullptr;
    std::string str, cmd;
    std::ifstream in;
    in.open(fileName.c_str());
    if (in.is_open()) {

        // I need to implement a matrix stack to store transforms.
        // This is done using standard STL Templates
        std::stack <glm::mat4> transfstack;
        transfstack.push(glm::mat4(1.0));  // identity

        getline(in, str);
        while (in) {
            if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
                // Ruled out comment and blank lines

                std::stringstream s(str);
                s >> cmd;
                int i;
                float values[10]; // Position and color for light, colors for others
                // Up to 10 params for cameras.
                bool validinput; // Validity of input

                if (cmd == "size") {
                    validinput = readvals(s, 2, values);
                    if (validinput) {
                        cfg.width = (int)values[0];
                        cfg.height = (int)values[1];
                    }
                }

                else if (cmd == "maxdepth") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        cfg.maxDepth = (int)values[0];
                    }
                }

                else if (cmd == "output") {
                    s >> cfg.outputFileName;
                }

                else if (cmd == "camera") {
                    validinput = readvals(s, 10, values); // 10 values eye cen up fov
                    if (validinput) {

                        for (int i = 0; i < 3; ++i) {
                            cfg.camera.lookFrom[i] = values[i];
                            cfg.camera.lookAt[i] = values[3 + i];
                            cfg.camera.up[i] = values[6 + i];
                        }
                        cfg.camera.fovy = values[9];
                    }
                }

                // Process the light
                else if (cmd == "directional") {
                    validinput = readvals(s, 6, values);
                    if (validinput) {
                        cfg.light.directional.position = { values[0], values[1], values[2] };
                        cfg.light.directional.color = { values[3], values[4], values[5] };
                    }
                }

                else if (cmd == "point") {
                    validinput = readvals(s, 6, values);
                    if (validinput) {
                        cfg.light.point.position = { values[0], values[1], values[2] };
                        cfg.light.point.color = { values[3], values[4], values[5] };
                    }
                }

                // Material Commands
                // Ambient, diffuse, specular, shininess properties for each object.
                // Filling this in is pretty straightforward, so I've left it in
                // the skeleton, also as a hint of how to do the more complex ones.
                // Note that no transforms/stacks are applied to the colors.

                else if (cmd == "ambient") {

                    cfg.materials.push_back(Material());
                    currentMaterial = &cfg.materials.back();

                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            currentMaterial->ambient[i] = values[i];
                        }
                    }
                }

                else if (cmd == "diffuse") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            currentMaterial->diffuse[i] = values[i];
                        }
                    }
                }

                else if (cmd == "specular") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 3; i++) {
                            currentMaterial->specular[i] = values[i];
                        }
                    }
                }

                else if (cmd == "emission") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        for (i = 0; i < 4; i++) {
                            currentMaterial->emission[i] = values[i];
                        }
                    }
                }

                else if (cmd == "shininess") {
                    validinput = readvals(s, 1, values);
                    if (validinput) {
                        currentMaterial->shininess = values[0];
                    }
                }

                // geometry

                else if (cmd == "maxverts") {
                    // ignore
                }

                else if (cmd == "vertex") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        cfg.vertices.push_back({ values[0], values[1], values[2] });
                    }
                }

                else if (cmd == "tri") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        const glm::vec3 v1 = cfg.vertices.at((int)values[0]);
                        const glm::vec3 v2 = cfg.vertices.at((int)values[1]);
                        const glm::vec3 v3 = cfg.vertices.at((int)values[2]);
                        const Triangle *t = new Triangle(v1, v2, v3, cfg.materials.size() - 1, transfstack.top());
                        cfg.primitives.emplace_back(t);
                    }
                }

                else if (cmd == "sphere") {
                    validinput = readvals(s, 4, values);
                    if (validinput) {
                        const glm::vec3 center = {values[0], values[1], values[2]};
                        const Sphere *t = new Sphere(center, values[3], cfg.materials.size() - 1, transfstack.top());
                        cfg.primitives.emplace_back(t);
                    }
                }

                else if (cmd == "translate") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        transfstack.top() *= Transform::translate(values[0], values[1], values[2]);
                    }
                }
                else if (cmd == "scale") {
                    validinput = readvals(s, 3, values);
                    if (validinput) {
                        transfstack.top() *= Transform::scale(values[0], values[1], values[2]);
                    }
                }
                else if (cmd == "rotate") {
                    validinput = readvals(s, 4, values);
                    if (validinput) {
                        transfstack.top() *= glm::mat4(Transform::rotate(values[3], glm::vec3(values[0], values[1], values[2])));
                    }
                }

                // I include the basic push/pop code for matrix stacks
                else if (cmd == "pushTransform") {
                    transfstack.push(transfstack.top());
                }
                else if (cmd == "popTransform") {
                    if (transfstack.size() <= 1) {
                        std::cerr << "Stack has no elements.  Cannot Pop\n";
                    }
                    else {
                        transfstack.pop();
                    }
                }

                else {
                    std::cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            getline(in, str);
        }
    } else {
        std:: cerr << "Unable to Open Input Data File " << fileName << "\n";
        throw std::runtime_error("Unable to Open Input Data File");
    }
    return cfg;
}

bool Parser::readvals(std::stringstream &s, int numvals, float *values)
{
    for (int i = 0; i < numvals; i++) {
        s >> values[i];
        if (s.fail()) {
            std::cout << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}
