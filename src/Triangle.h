//
// Created by szynt on 04.11.2023.
//

#ifndef FLUIDSIM25_TRIANGLE_H
#define FLUIDSIM25_TRIANGLE_H

#include "Point.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

class Triangle {
public:
    Point p1;
    Point p2;
    Point p3;
    float vertices[18]{};
    unsigned int indices[3]{};
    unsigned int VAO;
    unsigned int EBO;
    unsigned int VBO;
    Shader ourShader = Shader(R"(..\src\shaders\Triangle\vShader.glsl)",
                              R"(..\src\shaders\Triangle\fShader.glsl)");

    Triangle();
    Triangle(Point p1, Point p2, Point p3);
    void show();

private:
    void generateArray();
    void initVBOs();
};


#endif //FLUIDSIM25_TRIANGLE_H
