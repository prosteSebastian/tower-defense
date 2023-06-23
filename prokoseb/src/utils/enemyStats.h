//
// Created by prokoseb on 25.5.23.
//

#ifndef TOWER_DEFENSE_ENEMYSTATS_H
#define TOWER_DEFENSE_ENEMYSTATS_H

#include "position.h"
#include <sstream>

/**
 * @brief Struct for enemy stats
 */
struct stats {

    stats(char symbol, int health, int speed, int reward, int damage, position pos, std::string name);

    /**
     * @brief Prints stats to buffer
     * @param buffer The buffer to print to
     */
    void saveStats(std::ostream &buffer) const;

    char _symbol;
    int _health;
    int _speed;
    int _reward;
    int _damage;
    position _position;
    std::string _name;
};

#endif //TOWER_DEFENSE_ENEMYSTATS_H
