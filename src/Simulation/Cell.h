//
// Created by szynt on 06.11.2023.
//

#ifndef FLUIDSIM25_CELL_H
#define FLUIDSIM25_CELL_H

#include "../Primitives/Square.h"

class Grid;

class Cell {
public:
    int x;
    int y;
    float u = 0;
    float newU = 0;
    float v = 0;
    float newV = 0;
    float p = 0;
    float d = 0;
    float newD = 0;
    int isSim = 0;



    Square repr;

    Cell();

    Cell(int x, int y, SquareHelper sqh);

    void show() const;
    void showSim() const;
};


#endif //FLUIDSIM25_CELL_H
