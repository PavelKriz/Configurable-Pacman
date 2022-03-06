//
// Created by pavel on 24.05.20.
//

#include "functions.h"


bool areFloatsEqual(const float a, const float b){
    return (a - COMPARE_EPSILON < b) && (a + COMPARE_EPSILON > b);
}

bool areFloatsEqual(const float a, const float b, const float alpha){
    return (a - alpha < b) && (a + alpha > b);
}

float calcDistance(const SCoordinates &first, const SCoordinates &second) {
    float xDist = abs(first.x_ - second.x_);
    float yDist = abs(first.y_ - second.y_);
    return sqrt(xDist * xDist + yDist * yDist);
}