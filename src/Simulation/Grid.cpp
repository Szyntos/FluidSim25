//
// Created by szynt on 06.11.2023.
//

#include "Grid.h"
#include "../utils/Globals.h"

Grid::Grid(int numRows, int numCols) {
    sqh = SquareHelper(windowHeight / numRows);
    rows = numRows;
    cols = numCols;

    // Allocate memory for the 2D array of Cell objects
    cells = new Cell*[rows];
    for (int i = 0; i < rows; i++) {
        cells[i] = new Cell[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cells[i][j] = Cell(i, j, this->sqh);
            cells[i][j].isSim = 1;
        }
    }
    for (int i = 0; i < rows; ++i) {
        cells[i][0].isSim = 0;
        cells[i][cols - 1].isSim = 0;
    }
    for (int i = 0; i < cols; ++i) {
        cells[0][i].isSim = 0;
        cells[rows - 1][i].isSim = 0;
    }
}

Grid::~Grid() {
    for (int i = 0; i < rows; i++) {
        delete[] cells[i];
    }
    delete[] cells;
}

Cell &Grid::getCell(int x, int y) {
    if (x >= 0 && x < rows && y >= 0 && y < cols) {
        return cells[x][y];
    } else {
        std::cout <<"Cell coordinates out of bounds."<<"\n";
        // Handle out-of-bounds access, you can customize this part.
        throw std::out_of_range("Cell coordinates out of bounds.");
    }
}

void Grid::show() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells[i][j].show();
        }
    }

}

void Grid::showSim() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cells[i][j].showSim();
        }
    }
}

Grid::Grid() {
    sqh = SquareHelper(windowHeight / 1);
    rows = 1;
    cols = 1;

    // Allocate memory for the 2D array of Cell objects
    cells = new Cell*[rows];
    for (int i = 0; i < rows; i++) {
        cells[i] = new Cell[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cells[i][j] = Cell(i, j, this->sqh);
            cells[i][j].isSim = 1;
        }
    }
    for (int i = 0; i < rows; ++i) {
        cells[i][0].isSim = 0;
        cells[i][cols - 1].isSim = 0;
    }
    for (int i = 0; i < cols; ++i) {
        cells[0][i].isSim = 0;
        cells[rows - 1][i].isSim = 0;
    }

}
