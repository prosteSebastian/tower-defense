//
// Created by prokoseb on 25.5.23.
//

#ifndef TOWER_DEFENSE_CLOSESTATTACK_H
#define TOWER_DEFENSE_CLOSESTATTACK_H

#include "fire.h"

/**
 * @brief Attack that targets the closest enemy in range
 * @inherit fire
 * @see fire
 */
class closestAttack : public fire {
public:
    closestAttack(int reloadTime) : fire(reloadTime) {}

    void shoot(const position &towerPos, int range, const enemies &enemyLoc) override;

    std::unique_ptr<fire> clone() const override;
};


#endif //TOWER_DEFENSE_CLOSESTATTACK_H
