//
// Created by szynt on 06.11.2023.
//

#include "Cell.h"

Cell::Cell(int x, int y, SquareHelper sqh) {
    this->x = x;
    this->y = y;
    isSim = 1;
    repr = Square(sqh.h, sqh);
    repr.translate(1*x, 1*y);
}

Cell::Cell() {
    x = 0;
    y = 0;
    isSim = 0;
    repr = Square();
}

void Cell::show() const {
    repr.show();

}

void Cell::showSim() const {
    if (isSim){
        repr.showSim(u, v, p, d);
    }
}

void Cell::setP(float p) {
    this->p = p;

}

void Cell::copyFrom(Cell other) {
    u = other.u;
    newU = other.newU;
    v = other.v;
    newV = other.newV;
    p = other.p;
    d = other.d;
    newD = other.newD;
    isSim = other.isSim;
//    repr = other.repr;
}

