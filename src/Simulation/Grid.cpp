//
// Created by szynt on 06.11.2023.
//

#include "Grid.h"
#include "../utils/Globals.h"

Grid::Grid(int numRows, int numCols) {
    sqh = SquareHelper((float)((float)windowHeight) / (float)numRows);
//    std::cout<<sqh.h<<"\n";
    rows = numRows;
    cols = numCols;

    // Allocate memory for the 2D array of Cell objects
    cells = new Cell*[rows];
    for (int i = 0; i < rows; i++) {
        cells[i] = new Cell[cols];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cells[i][j] = Cell(j, i, this->sqh);
            cells[i][j].isSim = 1;
        }
    }
    for (int i = 0; i < rows; ++i) {
        cells[i][0].isSim = 0;
        cells[i][cols - 1].isSim = 0;
        cells[i][0].u = 0;
        cells[i][cols - 1].u = 0;
    }
    for (int i = 0; i < cols; ++i) {
        cells[0][i].isSim = 0;
        cells[rows - 1][i].isSim = 0;
        cells[0][i].u = 0;
        cells[rows - 1][i].u = 0;
        cells[0][i].v = 0;
        cells[rows - 1][i].v = 0;
    }
}

void Grid::deleteCells(){
    for (int i = 0; i < rows; i++) {
        delete[] cells[i];
    }
    delete[] cells;
}
void Grid::copyCells(Grid other){
    if (this != &other) {
        // First, delete the existing cells
        deleteCells();

        // Copy the dimensions
        rows = other.rows;
        cols = other.cols;

        // Allocate memory for the new cells
        cells = new Cell*[rows];
        for (int i = 0; i < rows; ++i) {
            cells[i] = new Cell[cols];
        }

        // Copy the cell values from 'other' to 'this'
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cells[i][j] = other.cells[i][j];
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

        // Copy 'sqh' from 'other'
//        sqh = other.sqh;
    }
}

Cell &Grid::getCell(int i, int j) {
    if (i >= 0 && i < rows && j >= 0 && j < cols) {
        return cells[i][j];
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
            cells[i][j] = Cell(j, i, this->sqh);
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
