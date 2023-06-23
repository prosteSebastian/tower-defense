//
// Created by prokoseb on 25.5.23.
//

#include "closestAttack.h"
#include "../utils/distance.cpp"
#include <limits>

void closestAttack::shoot(const position &towerPos, int range, const enemies &enemyLoc) {
    if (isReady()) {
        int minDistance = std::numeric_limits<int>::max();
        enemy *closestE;

        for (auto &enemy: enemyLoc._enemyMap) {
            if (inRange(towerPos, enemy->getPosition(), range) && enemy->canBeAttacked()) {
                if (distance(towerPos, enemy->getPosition()) < minDistance) {
                    minDistance = distance(towerPos, enemy->getPosition());
                    closestE = enemy.get();
                }
            }
        }
        if (minDistance != std::numeric_limits<int>::max()) {
            for (const auto &effect: _effects) {
                closestE->applyEffect(effect->clone());
            }
            _remainingReloadTime = 0;
        }
    }
}

std::unique_ptr<fire> closestAttack::clone() const {
    return std::make_unique<closestAttack>(*this);
}
