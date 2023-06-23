//
// Created by prokoseb on 5.5.23.
//

#ifndef TOWER_DEFENSE_ENEMIES_H
#define TOWER_DEFENSE_ENEMIES_H

#include <memory>
#include <iostream>
#include <list>
#include "../objects/enemy.h"
#include "../utils/position.h"

/**
 * @brief Class that holds all enemies on the map
 * @details Enemies are stored in a list of unique pointers to enemy objects
 */
struct enemies {

    enemies() = default;

    enemies(const enemies &e);

    enemies &operator=(const enemies &e);

    /**
     * @brief Adds an enemy to the list
     * @param enemy Enemy to be added
     */
    void addEnemy(std::unique_ptr<enemy> enemy);

    /**
     * @brief Tells if the object on the position is an enemy
     * @param p position to be checked
     * @return True if the object on the position is an enemy, false otherwise
     */
    bool isEnemy(const position &p) const;

    /**
     * @brief update the state of all enemies on the map
     * @details First it casts the abilities of the enemies,
     * then it evaluates the effects that are applied on them
     * and then finally it moves them
     */
    void updateEnemies();

    /**
     * @brief Prints the enemies on the map
     * @param out Output stream
     */
    void print(std::ostream &out, const position &p) const;

    /**
     * @brief Sets the base position
     * @param p Position of the base
     */
    void setBase(const position &p);

    /**
     * @brief Reset the gained money;
     */
    void resetGainedMoney();

    /**
     * @brief Increment the ability cooldowns of enemies
     */
    void incrementAbilityCds();

    /**
     * @brief Check if the applied effects on the enemies are valid
     */
    void validateEffect() const;

    position base;
    int takenDamage = 0;
    int _gainedMoney = 0;
    std::list<std::unique_ptr<enemy>> _enemyMap;
};


#endif //TOWER_DEFENSE_ENEMIES_H
