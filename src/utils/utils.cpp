//
// Created by szynt on 07.11.2023.
//

#include "utils.h"
#include <cmath>
double sigmoid(double x) {
    float positive_cutoff = 1000000;
    float negative_cutoff = -1000000;
    if (x > positive_cutoff) {
        return 1.0;
    }
    if (x < negative_cutoff) {
        return 0.0;
    }
    return 1.0 / (1.0 + std::exp(-x));
}
float bound(float a, float b, float val){
    if (val < a) {
        return a;
    } else if (val > b) {
        return b;
    } else {
        return val;
    }
}