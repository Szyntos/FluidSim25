//
// Created by szynt on 06.11.2023.
//

#include "SquareHelper.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../utils/Globals.h"

SquareHelper::SquareHelper() {

}
SquareHelper::SquareHelper(int h) {
    this->h = h;
    ourShader = Shader(R"(..\src\shaders\Square\vShader.glsl)",
                          R"(..\src\shaders\Square\fShader.glsl)");
    generateArray();
    initVBOs();
}

void SquareHelper::generateArray() {
    float positions[] = {
            1, 1, 0,
            0, 1, 0,
            0, 0, 0,
            1, 0, 0
    };

    float colors[] = {
            0.9f, 0.9f, 0.9f,
            0.9f, 0.9f, 0.9f,
            0.9f, 0.9f, 0.9f,
            0.9f, 0.9f, 0.9f
    };
    int idxes[] = {
            0, 1, 2,
            2, 3, 0,
    };
    int k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; ++j) {
            vertices[i * 6 + j] = positions[k];
            k++;
        }

    }

    k = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; ++j) {
            vertices[i * 6 + j + 3] = colors[k];
            k++;
        }

    }
    for (int i = 0; i < 6; i++) {
        indices[i] = idxes[i];
    }
}

void SquareHelper::initVBOs() {
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
}


