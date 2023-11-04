//
// Created by szynt on 04.11.2023.
//

#include "Triangle.h"


Triangle::Triangle() {
    p1 = Point(0, 1);
    p2 = Point(-1, -1);
    p3 = Point(1, -1);
    generateArray();
    initVBOs();
}

Triangle::Triangle(Point p1, Point p2, Point p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    generateArray();
    initVBOs();
}

void Triangle::show() {
    ourShader.use();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Triangle::generateArray() {
    float positions[] = {
            p1.x, p1.y, p1.z,
            p2.x, p2.y, p2.z,
            p3.x, p3.y, p3.z
    };

    float colors[] = {
            1.0f, 0.0f, 0.0f,   // Red
            0.0f, 1.0f, 0.0f,   // Green
            0.0f, 0.0f, 1.0f    // Blue
    };
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; ++j) {
            vertices[i * 6 + j] = positions[k];
            k++;
        }

    }

    k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; ++j) {
            vertices[i * 6 + j + 3] = colors[k];
            k++;
        }

    }
    for (int i = 0; i < 3; i++) {
        indices[i] = i;
    }
}

void Triangle::initVBOs() {

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
