//
// Created by prokoseb on 25.5.23.
//

#ifndef TOWER_DEFENSE_SNIPEATTACK_H
#define TOWER_DEFENSE_SNIPEATTACK_H

#include "fire.h"

/**
 * @brief Attack that targets the farthest enemy in range
 * @inherit fire
 * @see fire
 */
class snipeAttack : public fire {
public:
    explicit snipeAttack(int reloadTime) : fire(reloadTime) {}

    void shoot(const position &towerPos, int range, const enemies &enemyLoc) override;

    std::unique_ptr<fire> clone() const override;
};


#endif //TOWER_DEFENSE_SNIPEATTACK_H
