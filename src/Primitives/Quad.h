//
// Created by szynt on 06.11.2023.
//

#ifndef FLUIDSIM25_QUAD_H
#define FLUIDSIM25_QUAD_H

#include "Point.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <cstdlib>
#include "../utils/Shader.h"

class Quad {
public:
    Point p1;
    Point p2;
    Point p3;
    Point p4;
    float vertices[24]{};
    unsigned int indices[6]{};
    unsigned int VAO;
    unsigned int EBO;
    unsigned int VBO;
    Shader ourShader = Shader(R"(..\src\shaders\Quad\vShader.glsl)",
                              R"(..\src\shaders\Quad\fShader.glsl)");
    Quad();
    Quad(Point p1, Point p2, Point p3, Point p4);
    void show() const;
    void translate();

private:
    void generateArray();
    void initVBOs();
};


#endif //FLUIDSIM25_QUAD_H
