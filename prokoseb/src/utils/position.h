//
// Created by s on 6.5.23.
//

#ifndef TOWER_DEFENSE_POSITION_H
#define TOWER_DEFENSE_POSITION_H

#include<iostream>

/**
 * @brief Struct for position in the grid (x, y)
 */
struct position {
    position() = default;

    position(size_t x, size_t y);

    bool operator==(const position &rhs) const;

    bool operator!=(const position &rhs) const;

    /**
     * @brief Compares two positions by their x and y
     * @param rhs
     * @return True if this position is smaller than rhs position
     */
    bool operator<(const position &rhs) const;

    friend std::ostream &operator<<(std::ostream &out, const position &p);

    size_t x = 0;
    size_t y = 0;
};

#endif //TOWER_DEFENSE_POSITION_H
