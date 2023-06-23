//
// Created by s on 20.5.23.
//

#ifndef TOWER_DEFENSE_AOEATTACK_H
#define TOWER_DEFENSE_AOEATTACK_H

#include "fire.h"

/**
 * @brief Attack that targets all enemies in range
 * @inherit fire
 * @see fire
 */
class aoeAttack : public fire {
public:
    aoeAttack(int reloadTime) : fire(reloadTime) {}

    void shoot(const position &towerPos, int range, const enemies &enemyLoc) override;

    std::unique_ptr<fire> clone() const override;
};


#endif //TOWER_DEFENSE_AOEATTACK_H
