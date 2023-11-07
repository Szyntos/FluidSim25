//
// Created by szynt on 06.11.2023.
//

#include "Quad.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "../utils/Globals.h"

Quad::Quad() {
    p1 = Point(2, 2);
    p2 = Point(0, 2);
    p3 = Point(0, 0);
    p4 = Point(2, 0);
    generateArray();
    initVBOs();
}

Quad::Quad(Point p1, Point p2, Point p3, Point p4) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
    generateArray();
    initVBOs();
}

void Quad::show() const {
    ourShader.use();
    ourShader.setFloat("colorOffr", sin(4*glfwGetTime())/2);
    ourShader.setFloat("colorOffg", cos(3*glfwGetTime())/2);
    ourShader.setFloat("colorOffb", sin(3*cos(2*glfwGetTime()))/2);
    ourShader.setMat4("model",
                      glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1)));
    ourShader.setMat4("view",
                      glm::mat4(1.0f));
//    ourShader.setMat4("projection",
//                      glm::mat4(1.0f));
    ourShader.setMat4("projection",
                      glm::ortho(0.0f, (float)windowWidth, 0.0f,
                                 (float)windowHeight, 0.1f, 100.0f));


    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Quad::translate() {

}

void Quad::generateArray() {
    float positions[] = {
            p1.x, p1.y, p1.z,
            p2.x, p2.y, p2.z,
            p3.x, p3.y, p3.z,
            p4.x, p4.y, p4.z
    };

    float colors[] = {
            1.0f, 0.0f, 0.0f,   // Red
            0.0f, 1.0f, 0.0f,   // Green
            0.0f, 0.0f, 1.0f,   // Blue
            1.0f, 0.0f, 1.0f   // Purple
    };
    int idxes[] = {
            0, 1, 2,   // Red
            2, 3, 0,   // Green
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
            vertices[i * 6 + j + 3] = colors[k] + (float)(rand()%100-10)/200;
            k++;
        }

    }
    for (int i = 0; i < 6; i++) {
        indices[i] = idxes[i];
    }
}

void Quad::initVBOs() {
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
