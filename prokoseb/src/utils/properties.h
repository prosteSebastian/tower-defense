//
// Created by s on 27.5.23.
//

#ifndef TOWER_DEFENSE_PROPERTIES_H
#define TOWER_DEFENSE_PROPERTIES_H

#include "enemyStats.h"
#include "flags.h"
#include <set>
#include <utility>

/**
 * @brief Struct for storing properties of enemies
 */
struct properties {
    properties(char symbol, int health, int speed, int reward, int damage, size_t x, size_t y, std::string name);

    /**
     * @brief Removes flag from enemy
     * @param f Flag to be removed
     */
    void removeFlag(const flags &f);

    /**
     * @brief Saves properties of enemy to buffer
     * @param buffer Buffer to save to
     */
    void saveProperties(std::ostream &buffer) const;

    stats _stats;
    stats _originalStats;
    std::set<flags> _flags;
};

#endif //TOWER_DEFENSE_PROPERTIES_H
