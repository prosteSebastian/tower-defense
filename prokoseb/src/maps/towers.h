//
// Created by prokoseb on 5.5.23.
//

#ifndef TOWER_DEFENSE_TOWERS_H
#define TOWER_DEFENSE_TOWERS_H

#include "../objects/tower.h"
#include "../utils/position.h"
#include "../maps/enemies.h"
#include <iostream>
#include <list>
#include <memory>

/**
 * @brief Represents a collection of towers
 * @details Towers are stored in a list of unique pointers
 * @see tower
 */
struct towers {

    /**
     * @brief Builds a tower on a given position
     * @param money Money of the player
     * @param t Tower to build
     * @param p Position to build tower on
     * @param success True if tower was built, false otherwise
     * @details If tower was built, money is decreased by price of tower, if the player doesn't have enough money, tower is not built
     */
    void buildTower(int &money, const std::unique_ptr<tower> &t, const position &p, bool &success);

    /**
     * @brief Tells if there is a tower on a given position
     * @param p Position to check
     * @return True if there is a tower, false otherwise
     */
    bool isTower(const position &p) const;

    /**
     * @brief Prints tower on a given position
     * @param out The output stream
     * @param p The position to print tower on
     */
    void print(std::ostream &out, const position &p) const;

    /**
     * @brief Calls the attack method of all towers
     * @param enemyMap Map of enemies
     */
    void attack(const enemies &enemyMap);

    /**
     * @brief resets kill of towers
     */
    void resetKillScore();

    /**
     * @brief increments ability cooldowns
     */
    void reloadTowers();

    std::list<std::unique_ptr<tower>> _towers;
    int _killScore = 0;
};


#endif //TOWER_DEFENSE_TOWERS_H
