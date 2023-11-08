//
// Created by szynt on 06.11.2023.
//

#ifndef FLUIDSIM25_GRID_H
#define FLUIDSIM25_GRID_H


#include "Cell.h"
#include <vector>
#include "iostream"
#include "../Primitives/SquareHelper.h"

class Grid {
public:
    Cell** cells;
    SquareHelper sqh;
    int rows;
    int cols;
    Grid();
    Grid(int numRows, int numCols);


    void deleteCells();
    void copyCells(Grid other);


    Cell& getCell(int i, int j);

    void show();
    void showSim();
};

#endif //FLUIDSIM25_GRID_H
