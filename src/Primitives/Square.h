//
// Created by szynt on 06.11.2023.
//

#ifndef FLUIDSIM25_SQUARE_H
#define FLUIDSIM25_SQUARE_H

#include "../utils/Shader.h"
#include "SquareHelper.h"
#include "../utils/utils.h"

class Square {
public:
    int a;
    glm::mat4 trans = glm::mat4(1.0f);
    SquareHelper sqh;

    Square();
    Square(int a, SquareHelper sqh);
    void translate(int x, int y);
    void show() const;
    void showSim(float u, float v, float p, float d) const;


};


#endif //FLUIDSIM25_SQUARE_H
