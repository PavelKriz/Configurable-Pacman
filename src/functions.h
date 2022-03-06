//
// Created by pavel on 24.05.20.
//

#ifndef PA2_2_SEMESTRALKA_FUNCTIONS_H
#define PA2_2_SEMESTRALKA_FUNCTIONS_H

#include "parameters.h"
#include "SCoordinates.h"
#include <cmath>


const float COMPARE_EPSILON = 0.002f; ///< compare epsilon
/// compares two floats with default compare accuracy
/**
 * @param[in] a first fload to be compared
 * @param[in] b second float to be compared
 * @return if the a and b are the same
 * */
bool areFloatsEqual(const float a,const float b);
/// compares two floats with given accuracy
/**
 * @param[in] a first fload to be compared
 * @param[in] b second float to be compared
 * @param[in] alpha threshold that determinates the accuracy and tolerance of the comparison
 * @return if the a and b are the same
 * */
bool areFloatsEqual(const float a, const float b, const float alpha);
/// Calculating euclidean distance between two points (coordinates)
/**
 * @param[in] first coordinates of first point
 * @param[in] second coordinates of second point
 * @return the euclidean distance between given points
 * */
float calcDistance(const SCoordinates &first, const SCoordinates &second);

#endif //PA2_2_SEMESTRALKA_FUNCTIONS_H