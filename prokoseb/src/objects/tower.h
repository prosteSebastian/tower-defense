//
// Created by prokoseb on 25.4.23.
//

#ifndef TOWERDEFENSE_TOWER_H
#define TOWERDEFENSE_TOWER_H

#include <memory>
#include "../attacks/fire.h"
#include "../maps/enemies.h"
#include "../../libs/rang.hpp"
#include "../utils/towerStats.h"

/**
 * @brief Class representing a tower
 */
class tower {
public:
    /**
     * @brief Constructor for tower
     * @param symbol Symbol to represent tower on map
     * @param p Position of tower
     * @param damage Damage of tower
     * @param range Range of tower
     * @param price Price of tower
     * @param attack Type of attack of tower
     * @param name Name of tower
     * @param color Color of tower
     */
    tower(char symbol, const position &p, int damage, int range, int price, std::unique_ptr<fire> attack,
          std::string name, rang::fg color);

    tower(const tower &other);

    tower &operator=(const tower &t);

    /**
     * @brief Attack enemies in range of tower and update kill score
     * @details call shoot() method of _attack
     * @param pos Position of tower
     * @param range Range of towera
     * @param enemyMap Map of enemies
     */
    void attack(const position &pos, int range, const enemies &enemyMap);

    /**
     * @brief Reset kill score of tower
     */
    void resetKillScore();

    /**
     * @brief Clone tower
     * @return Pointer to cloned tower
     */
    std::unique_ptr<tower> clone() const;

    /**
     * @brief Upgrade damage of tower
     * @param money Amount of money player has
     * @param tower Tower to upgrade
     * @param success True if upgrade was successful, false otherwise
     * @param dmgIncrease Amount of damage to increase
     * @param costIncrease Amount of cost to increase
     */
    void
    upgradeDamage(int &money, const std::unique_ptr<tower> &tower, bool &success, int dmgIncrease, float costIncrease);

    /**
     * @brief Upgrade range of tower
     * @param money Amount of money player has
     * @param success True if upgrade was successful, false otherwise
     * @param rangeIncrease Amount of range to increase
     * @param costIncrease Amount of cost to increase
     */
    void upgradeRange(int &money, bool &success, int rangeIncrease, float costIncrease);

    /**
     * @brief Add effect to tower to attack
     * @details Call addEffect() method of _attack
     * @param e Effect to add
     */
    void addEffect(const std::shared_ptr<effect> &e);

    /**
     * @brief Print tower
     * @param out Output stream
     */
    void print(std::ostream &out) const;

    /**
     * @brief Get stats of tower
     * @return Stats of tower
     */
    towertStats getStats() const { return _stats; }

    /**
     * @brief Increment reload time of tower
     */
    void incrementReloadTime();

    /**
     * @brief Save tower to file
     * @details Save stats of tower to file, then call save() method of _attack
     * @param buffer Output stream
     */
    void saveTower(std::ostream &buffer) const;

    /**
     * @brief Set position of tower
     * @param p Position of tower to set to
     */
    void setPosition(const position &p);

    /**
     * @brief Set stats of tower from saved game
     * @param p Position of tower
     * @param dmg Damage of tower
     * @param range Range of tower
     * @param cost Cost of tower
     * @param lvl Level of tower
     */
    void setStatsFomSavedGame(const position &p, int dmg, int range, int cost, int lvl);

    /**
     * @brief Set fire of tower
     * @param remainingReload Remaining reload time
     */
    void setRemainingReload(int remainingReload);

private:
    rang::fg _color;
    std::unique_ptr<fire> _attack;
    towertStats _stats;
};

#endif //TOWERDEFENSE_TOWER_H
