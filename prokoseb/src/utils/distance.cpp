//
// Created by s on 26.5.23.
//

#ifndef TOWER_DEFENSE_DISTANCE_CPP
#define TOWER_DEFENSE_DISTANCE_CPP

#include "position.h"
#include <math.h>

/**
 * @brief Function for calculating distance between two positions
 * @param p1 First position
 * @param p2 Second position
 * @return
 */
inline int distance(const position &p1, const position &p2) {
    position maxX, maxY, minX, minY;
    if (p1.x > p2.x) {
        maxX = p1;
        minX = p2;
    } else {
        maxX = p2;
        minX = p1;
    }
    if (p1.y > p2.y) {
        maxY = p1;
        minY = p2;
    } else {
        maxY = p2;
        minY = p1;
    }
    position vector(maxX.x - minX.x, maxY.y - minY.y);
    //euclidean norm
    int distance = static_cast<int>(std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2)));
    return distance;
}

/**
 * @brief Function for checking if two positions are in range
 * @param p1 First position
 * @param p2 Second position
 * @param range Range to check
 * @return True if in range, false otherwise
 */
inline bool inRange(const position &p1, const position &p2, int range) {
    if (distance(p1, p2) <= range) {
        return true;
    }
    return false;
}

#endif //TOWER_DEFENSE_DISTANCE_CPP
