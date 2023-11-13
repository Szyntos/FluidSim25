//
// Created by szynt on 06.11.2023.
//

#include "../utils/Globals.h"
#include "Square.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

Square::Square() {
    a = 10;
}

Square::Square(int a, SquareHelper sqh) {
    this->a = a;
    this->sqh = sqh;
}

void Square::translate(int x, int y) {
    trans = glm::translate(trans, glm::vec3(a*x, a*y, 0));
}

void Square::show() const {
    sqh.ourShader.use();
    sqh.ourShader.setFloat("colorOffr", sin(4*glfwGetTime())/2);
    sqh.ourShader.setFloat("colorOffg", cos(3*glfwGetTime())/2);
    sqh.ourShader.setFloat("colorOffb", sin(3*cos(2*glfwGetTime()))/2);
    sqh.ourShader.setMat4("model",
                      glm::scale(glm::mat4(1.0f), glm::vec3(a, a, 1)));
    sqh.ourShader.setMat4("view",
                      trans);
//    ourShader.setMat4("projection",
//                      glm::mat4(1.0f));
    sqh.ourShader.setMat4("projection",
                      glm::ortho(0.0f, (float)windowWidth, 0.0f,
                                 (float)windowHeight, 0.1f, 100.0f));


    glBindVertexArray(sqh.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Square::showSim(float u, float v, float p, float d) const {
    sqh.ourShader.use();

    sqh.ourShader.setFloat("colorOffr", -sigmoid((d/(2)-40)));
    sqh.ourShader.setFloat("colorOffg", -sigmoid((d/5-9)));
    sqh.ourShader.setFloat("colorOffb", -sigmoid((d/20-10)));
//    sqh.ourShader.setFloat("colorOffr", -v);
    sqh.ourShader.setMat4("model",
                          glm::scale(glm::mat4(1.0f), glm::vec3(a, a, 1)));
    sqh.ourShader.setMat4("view",
                          trans);
//    ourShader.setMat4("projection",
//                      glm::mat4(1.0f));
    sqh.ourShader.setMat4("projection",
                          glm::ortho(0.0f, (float)windowWidth, 0.0f,
                                     (float)windowHeight, 0.1f, 100.0f));


    glBindVertexArray(sqh.VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

