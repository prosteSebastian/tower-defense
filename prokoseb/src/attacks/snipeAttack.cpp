//
// Created by prokoseb on 25.5.23.
//

#include "snipeAttack.h"
#include <limits.h>
#include "../utils/distance.cpp"

void snipeAttack::shoot(const position &towerPos, int range, const enemies &enemyLoc) {
    if (isReady()) {
        int maxDistance = INT_MIN;
        enemy *farthestEnemy;

        for (auto &enemy: enemyLoc._enemyMap) {
            if (inRange(towerPos, enemy->getPosition(), range) && enemy->canBeAttacked()) {
                if (distance(towerPos, enemy->getPosition()) > maxDistance) {
                    maxDistance = distance(towerPos, enemy->getPosition());
                    farthestEnemy = enemy.get();
                }
            }
        }
        if (maxDistance != INT_MIN) {
            for (const auto &effect: _effects) {
                farthestEnemy->applyEffect(effect->clone());
            }
            _remainingReloadTime = 0;
        }
    }
}

std::unique_ptr<fire> snipeAttack::clone() const {
    return std::make_unique<snipeAttack>(*this);
}
