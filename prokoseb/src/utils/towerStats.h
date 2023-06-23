//
// Created by s on 28.5.23.
//

#ifndef TOWER_DEFENSE_TOWERSTATS_H
#define TOWER_DEFENSE_TOWERSTATS_H

#include <string>
#include <utility>
#include "position.h"

/**
 * @brief Struct that holds all the stats of a tower
 */
struct towertStats {
    towertStats(std::string name, char symbol, position pos, int damage, int range, int cost, int level);

    /**
     * @brief Saves stats of tower to buffer
     * @param buffer Buffer to save to
     */
    void saveStats(std::ostream &buffer) const;

    std::string _name;
    char _symbol;
    position _position;
    int _damage;
    int _range;
    int _cost;
    int _level;
    int _killScore = 0;
};

#endif //TOWER_DEFENSE_TOWERSTATS_H
