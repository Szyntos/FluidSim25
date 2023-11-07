//
// Created by szynt on 06.11.2023.
//

#include "Sim.h"


Sim::Sim() : grid(50, 50){
    h = grid.getCell(0, 0).repr.a;
}
Sim::Sim(int a, int b) : grid(a, b){
    h = grid.getCell(0, 0).repr.a;
}


void Sim::updateVelocity(float dt) {
    for (int i = 0; i < grid.rows; ++i) {
        for (int j = 0; j < grid.cols; ++j) {
            if (grid.getCell(j, i).isSim){
                grid.getCell(j, i).v += dt * g;
            }

        }
    }

}

void Sim::incompressibility(int count, float dt) {
    float div;
    int s;
    int sx0;
    int sx1;
    int sy0;
    int sy1;
    for (int k = 0; k < count; ++k) {
        for (int i = 0; i < grid.rows; i++) {
            for (int j = 0; j < grid.cols; j++) {
//                Cell currentCell = grid.getCell(j, i);
//                grid.getCell(j, i).setP(100);
                if (grid.getCell(j, i).isSim){
                    sx0 = grid.getCell(j-1, i).isSim;
                    sx1 = grid.getCell(j+1, i).isSim;
                    sy0 = grid.getCell(j, i-1).isSim;
                    sy1 = grid.getCell(j, i+1).isSim;
                    s = sx0 + sx1 + sy0 + sy1;
                    div  = grid.getCell(j + 1, i).u;
                    div -= grid.getCell(j, i).u;
                    div += grid.getCell(j , i+1).v;
                    div -= grid.getCell(j, i).v;
                    div *= -o;
                    div /= s;

                    if (s){
                        grid.getCell(j, i).u -= sx0 * div;
                        grid.getCell(j+1, i).u += sx1 * div;
                        grid.getCell(j, i).v -= sy0 * div;
                        grid.getCell(j, i+1).v += sy1 * div;
                        grid.getCell(j, i).p  += div / s * d * h / dt;

                    }

                }
            }
        }
    }

}



void Sim::extrapolate() {
    for (int i = 0; i < grid.cols; i++) {
        grid.getCell(i, 0).u = grid.getCell(i, 1).u;
        grid.getCell(i, grid.rows - 1).u = grid.getCell(i, grid.rows - 2).u;
    }
    for (int i = 0; i < grid.rows; i++) {
        grid.getCell(0, i).v = grid.getCell(1, i).v;
        grid.getCell(grid.cols - 1, i).v = grid.getCell(grid.cols - 2, i).v;
    }
}


float Sim::avgU(int i, int j) {
    float u = (grid.getCell(i, j - 1).u +
               grid.getCell(i, j).u +
               grid.getCell(i + 1, j - 1).u +
               grid.getCell(i + 1, j).u)/4;
    return u;
}

float Sim::avgV(int i, int j) {
    float v = (grid.getCell(i - 1, j).v +
               grid.getCell(i, j).v +
               grid.getCell(i - 1, j + 1).v +
               grid.getCell(i, j + 1).v)/4;
    return v;
}

void Sim::advectVel(float dt) {




    float x;
    float y;
    float u;
    float v;


    float h2 = 0.5f * h;

    for (int i = 0; i < grid.cols; i++) {
        for (int j = 0; j < grid.rows; j++) {


            // u component
            if (grid.getCell(i, j).isSim) {
                x = i*h;
                y = j*h + h2;
                u = grid.getCell(i, j).u;
                v = avgV(i, j);
//						var v = this.sampleField(x,y, V_FIELD);
                x = x - dt*u;
                y = y - dt*v;
                u = sampleField(x,y, 0);
                grid.getCell(i, j).newU = u;
            }
            // v component
            if (grid.getCell(i, j).isSim) {
                x = i*h + h2;
                y = j*h;
                u = avgU(i, j);
//						var u = this.sampleField(x,y, U_FIELD);
                v = grid.getCell(i, j).v;
                x = x - dt*u;
                y = y - dt*v;
                v = sampleField(x,y, 1);
                grid.getCell(i, j).newV = v;
            }
        }
    }
    for (int i = 0; i < grid.rows; ++i) {
        for (int j = 0; j < grid.cols; ++j) {
            if (grid.getCell(i, j).isSim){
                grid.getCell(i, j).u = grid.getCell(i, j).newU;
                grid.getCell(i, j).v = grid.getCell(i, j).newV;
            }

        }
    }
}
void Sim::advectSmoke(float dt) {

    int n = grid.rows;
    float h2 = 0.5f * h;
    float u;
    float v;
    float x;
    float y;
    for (int i = 0; i < grid.cols; i++) {
        for (int j = 0; j < grid.rows; j++) {

            if (grid.getCell(i, j).isSim) {
                u = (grid.getCell(i, j).u + grid.getCell(i+1, j).u) * 0.5f;
                v = (grid.getCell(i,j).v + grid.getCell(i, j+1).v) * 0.5f;
                x = i*h + h2 - dt*u;
                y = j*h + h2 - dt*v;
//                std::cout<<sampleField(x,y, 2)<<std::endl;

                grid.getCell(i, j).newD = sampleField(x,y, 2);
            }
        }
    }
    for (int i = 0; i < grid.rows; ++i) {
        for (int j = 0; j < grid.cols; ++j) {
            grid.getCell(i, j).d = grid.getCell(i, j).newD;
        }
    }
}

void Sim::update(int count, float dt) {
    updateVelocity(dt);
    incompressibility(count, dt);
    extrapolate();
    advectVel(dt);
    advectSmoke(dt);


}

float Sim::sampleField(float x, float y, int field) {
//    field = 0 -> u; field = 1 -> v; field = 2 -> d;

    float  h1 = 1.0f / h;
    float  h2 = 0.5f * h;

    x = fmax(fmin(x, grid.cols * h), h);
    y = fmax(fmin(y, grid.rows * h), h);

    float dx = 0.0;
    float dy = 0.0;


    switch (field) {
        case 0:
            dy = h2;
            break;
        case 1:
            dx = h2;
            break;
        case 2:
            dx = h2;
            dy = h2;
            break;

    }

    float  x0 = fmin(floor((x-dx)*h1), grid.cols-1);
    float  tx = ((x-dx) - x0*h) * h1;
    float  x1 = fmin(x0 + 1, grid.cols-1);

    float y0 = fmin(floor((y-dy)*h1), grid.rows-1);
    float ty = ((y-dy) - y0*h) * h1;
    float y1 = fmin(y0 + 1, grid.rows-1);

    float sx = 1.0f - tx;
    float sy = 1.0f - ty;
    float val;
    switch (field) {
        case 0:
            val = sx*sy * grid.getCell(x0, y0).u +
                  tx*sy * grid.getCell(x1, y0).u +
                  tx*ty * grid.getCell(x1, y1).u +
                  sx*ty * grid.getCell(x0, y1).u;
            break;
        case 1:
            val = sx*sy * grid.getCell(x0, y0).v +
                  tx*sy * grid.getCell(x1, y0).v +
                  tx*ty * grid.getCell(x1, y1).v +
                  sx*ty * grid.getCell(x0, y1).v;
            break;
        case 2:
            val = sx*sy * grid.getCell(x0, y0).d +
                  tx*sy * grid.getCell(x1, y0).d +
                  tx*ty * grid.getCell(x1, y1).d +
                  sx*ty * grid.getCell(x0, y1).d;
            break;

    }


    return val;

}

void Sim::show() {
    grid.showSim();

}




