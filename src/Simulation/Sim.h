//
// Created by szynt on 06.11.2023.
//

#ifndef FLUIDSIM25_SIM_H
#define FLUIDSIM25_SIM_H

#include "Grid.h"
#include <cmath>

class Sim {
public:
    Grid grid;
    float g = 0;
    float d = 0;
    float h = 100000;
    float o = 0.5;
    Sim();
    Sim(int a, int b);
    void updateVelocity(float dt);
    void incompressibility(int count, float dt);
    void extrapolate();
    void advectVel(float dt);
    void advectSmoke(float dt);
    float sampleField(float x, float y, int f);
    float avgU(int i, int j);
    float avgV(int i, int j);
    void update(int count, float dt);
    void show();



};


#endif //FLUIDSIM25_SIM_H
