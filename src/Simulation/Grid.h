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
private:



    Cell** cells;
    SquareHelper sqh;

public:
    int rows;
    int cols;
    Grid();
    Grid(int numRows, int numCols);

    ~Grid();



    Cell& getCell(int x, int y);

    void show();
    void showSim();
};

#endif //FLUIDSIM25_GRID_H
