//
// Created by szynt on 06.11.2023.
//

#ifndef FLUIDSIM25_SQUAREHELPER_H
#define FLUIDSIM25_SQUAREHELPER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <cstdlib>
#include "../utils/Shader.h"

class SquareHelper {
public:
    float h;
    float r;
    float vertices[24]{};
    unsigned int indices[6]{};
    unsigned int VAO;
    unsigned int EBO;
    unsigned int VBO;
    Shader ourShader;
    SquareHelper();
    explicit SquareHelper(float x);

private:
    void generateArray();
    void initVBOs();
};


#endif //FLUIDSIM25_SQUAREHELPER_H
