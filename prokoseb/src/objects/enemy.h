//
// Created by prokoseb on 25.4.23.
//

#ifndef TOWERDEFENSE_stats_ENEMY_stats_H
#define TOWERDEFENSE_stats_ENEMY_stats_H

#include <memory>
#include <set>
#include <deque>
#include <utility>
#include <list>
#include "../utils/position.h"
#include "../utils/eTypeOfPassage.h"
#include "../passages/passage.h"
#include "../effects/effect.h"
#include "../../libs/rang.hpp"
#include "../abilities/ability.h"
#include "../utils/properties.h"

/**
 * @brief Class representing an enemy
 */
class enemy {
public:
    /**
     * @brief Constructs an enemy
     * @param x x coordinate
     * @param y Y coordinate
     * @param symbol symbol representing the enemy
     * @param health health of the enemy
     * @param speed speed of the enemy
     * @param reward reward for killing the enemy
     * @param damage damage of the enemy to the base
     * @param name name of the enemy
     */
    enemy(int x, int y, char symbol, int health, int speed, int reward, int damage, std::string name);

    enemy(const enemy &e);

    enemy &operator=(const enemy &e);

    /**
     * @brief Moves the enemy to the next position in the _moves deque
     * @return true if the enemy moved, false otherwise
     */
    bool move();

    /**
     * @brief Returns the position of the enemy
     * @return position of the enemy
     */
    position getPosition() const;

    /**
     * @return Returns the abilities of the enemy
     */
    std::vector<std::shared_ptr<ability>> getAbilities() const;

    /**
     * @return Returns the stats of the enemy
     */
    stats getStats() const;

    /**
     * @brief Prints the enemy according to the effects applied to it and abilities it has
     * @param out output stream
     */
    void print(std::ostream &out) const;

    /**
     * @brief Generates the path for the enemy using the passage
     * @param m tileMap of the game
     */
    void generatePath(const tileMap &m);

    /**
     * @brief Clones the enemy
     * @return unique pointer to the cloned enemy
     */
    std::unique_ptr<enemy> clone() const;

    /**
     * @brief Applies the effect to the enemy
     * @param e effect to be applied
     */
    void applyEffect(const std::shared_ptr<effect> &e);

    /**
     * @brief Evaluates the applied effects according to its effect
     */
    void evalEffects();

    /**
     * @brief Validates the applied effects according to its duration and removes the expired ones
     */
    void validateEffects();

    /**
     * @return returns the properties of the enemy
     */
    properties getProperties() const;

    /**
     * @brief Sets the properties of the enemy
     * @param other properties to be set
     */
    void setProperties(const properties &other);

    /**
     *
     * @return True if the enemy can be attacked, false otherwise
     */
    bool canBeAttacked() const;

    /**
     * @brief Adds a flag to the enemy
     * @param flag flag to be added
     */
    void addFlag(const flags &flag);

    /**
     * @brief Finds out if the enemy has the flag
     * @param flag flag to be checked
     * @return True if the enemy has the flag, false otherwise
     */
    bool hasFlag(const flags &flag) const;

    /**
     * @brief Add an ability to the enemy
     * @param a  ability to be added
     */
    void addAbility(const std::shared_ptr<ability> &a);

    /**
     * @brief Saves stats of  the enemy and its appliedEffects to the buffer
     * @param buffer Buffer to be saved to
     */
    void save(std::ostream &buffer) const;

    /**
     * @brif prints the enemy to the output stream
     * @param out Stream to be printed to
     * @param e Enemy to be printed
     * @return the output stream
     */
    friend std::ostream &operator<<(std::ostream &out, const enemy &e);

    /**
     * @brief Sets the passage of the enemy
     * @param passage The passage to be set
     */
    void setPassage(std::unique_ptr<passage> passage);

    /**
     * @brief Sets the stast of the enemy from the saved game
     * @param health health of the enemy
     * @param speed speed of the enemy
     * @param reward reward for killing the enemy
     * @param damage damage of the enemy to the base
     * @param pos position of the enemy
     */
    void setStatsFromSavedGame(int health, int speed, int reward, int damage, const position &pos);

private:
    std::vector<std::shared_ptr<ability>> _abilities;
    std::vector<std::shared_ptr<effect>> _appliedEffects;

    std::unique_ptr<passage> _passage;
    std::deque<position> _moves;

    properties _propeties;

};


#endif //TOWERDEFENSE_stats.ENEMY_stats.H