//
// Created by szynt on 04.11.2023.
//

#ifndef FLUIDSIM25_POINT_H
#define FLUIDSIM25_POINT_H


class Point {
public:
    float x{};
    float y{};
    float z{};

    Point();
    Point(float x, float y, float z);
    Point(float x, float y);
};


#endif //FLUIDSIM25_POINT_H
