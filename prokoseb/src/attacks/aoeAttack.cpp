//
// Created by s on 20.5.23.
//

#include "aoeAttack.h"
#include "../utils/distance.cpp"

void aoeAttack::shoot(const position &towerPos, int range, const enemies &enemyLoc) {
    if (isReady()) {
        for (auto &enemy: enemyLoc._enemyMap) {
            if (inRange(towerPos, enemy->getPosition(), range) && enemy->canBeAttacked()) {
                for (const auto &effect: _effects) {
                    enemy->applyEffect(effect->clone());
                }
            }
        }
        _remainingReloadTime = 0;
    }
}

std::unique_ptr<fire> aoeAttack::clone() const {
    return std::make_unique<aoeAttack>(*this);
}

