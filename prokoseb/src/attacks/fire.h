//
// Created by prokoseb on 15.5.23.
//

#ifndef TOWER_DEFENSE_FIRE_H
#define TOWER_DEFENSE_FIRE_H

#include "../maps/enemies.h"
#include <memory>

/**
 * @brief Base class for all attacks
 * @details Attacks are used by towers to attack enemies
 */
class fire {
public:
    /**
     * @brief Constructor for the fire
     * @param reloadTime Reload time of the fire to be ready to shoot again
     * @var _remainingReloadTime Remaining reload time of the fire
     */
    explicit fire(int reloadTime) : _reloadTime(reloadTime), _remainingReloadTime(reloadTime) {}

    virtual ~fire() = default;

    /**
     * @brief Shoots at the enemy
     * @param towerPos Position of the tower
     * @param range Range of the tower
     * @param enemyLoc Location of the enemies
     */
    virtual void shoot(const position &towerPos, int range, const enemies &enemyLoc) = 0;

    /**
     * @brief Clones the fire
     * @return The pointer to the cloned fire
     */
    virtual std::unique_ptr<fire> clone() const = 0;

    /**
     * @return Return the rewards of killed enemies
     */
    int getKillScore() const;

    /**
     * @brief Resets the kill score
     */
    void resetKillScore();

    /**
     * @brief Checks if the fire is ready to shoot
     * @return True if the fire is ready to shoot
     */
    bool isReady() const;

    /**
     * @brief Adds effect to the fire
     * @param e Effect to be added
     */
    void addEffect(const std::shared_ptr<effect> &e);

    /**
     * @brief Increments the remaining reload time if it is not ready
     */
    void incrementReloadTime();

    /**
     * @brief Upgrades the effect of the fire
     * @param newEffectPower New effect power
     */
    void upgradeEffect(int newEffectPower);

    /**
     * @brief Serializes the fire
     * @details Saved the remaining reload time of the fire to the buffer
     * @param buffer Buffer to save the fire to
     */
    void saveFire(std::ostream &buffer) const;

    /**
     * @brief Sets the remaining reload time of the fire
     * @details Used to load the fire from the buffer
     * @param remainingReloadTime New remaining reload time of the fire
     */
    void setRemainingReload(int remainingReloadTime);

protected:
    std::vector<std::shared_ptr<effect>> _effects;
    int _killScore = 0;
    int _reloadTime = 0;
    int _remainingReloadTime = 0;
};


#endif //TOWER_DEFENSE_FIRE_H
