//
// Created by prokoseb on 5.5.23.
//

#include "enemies.h"
#include <utility>

void enemies::updateEnemies() {
    for (auto &_enemy: _enemyMap) {
        for (const auto &ab: _enemy->getAbilities()) {
            for (const auto &ene: _enemyMap) {
                properties tmpProp = ene->getProperties();
                ab->cast(_enemy->getStats()._position, tmpProp);
                ene->setProperties(tmpProp);
            }
        }
        _enemy->evalEffects();

        if (_enemy->getProperties()._stats._health <= 0) {
            _enemyMap.remove_if([&](const std::unique_ptr<enemy> &e) {
                if (e->getProperties()._stats._health <= 0) {
                    _gainedMoney += e->getProperties()._stats._reward;
                    return true;
                } else {
                    return false;
                }
            });
            break;
        }

        for (int i = 0; i < _enemy->getStats()._speed; ++i) {
            if (!_enemy->move()) {
                break;
            }
        }
    }
}

void enemies::addEnemy(std::unique_ptr<enemy> enemy) {
    _enemyMap.emplace_back(std::move(enemy));
}

bool enemies::isEnemy(const position &p) const {
    for (const auto &enemy: _enemyMap) {
        if (enemy->getPosition() == p) {
            return true;
        }
    }
    return false;
}

void enemies::print(std::ostream &out, const position &p) const {
    for (const auto &e: _enemyMap) {
        if (e->getPosition() == p) {
            e->print(out);
            break;
        }
    }
}

enemies::enemies(const enemies &m) {
    for (const auto &e: m._enemyMap) {
        _enemyMap.emplace_back(std::make_unique<enemy>(*e));
    }
    base = m.base;
    takenDamage = m.takenDamage;
}

enemies &enemies::operator=(const enemies &m) {
    if (this != &m) {
        for (const auto &e: m._enemyMap) {
            _enemyMap.emplace_back(std::make_unique<enemy>(*e));
        }
        base = m.base;
        takenDamage = m.takenDamage;
    }
    return *this;
}

void enemies::incrementAbilityCds() {
    for (const auto &enemy: _enemyMap) {
        for (const auto &ab: enemy->getAbilities()) {
            ab->incrementCd();
        }
    }
}

void enemies::validateEffect() const {
    for (const auto &enemy: _enemyMap) {
        enemy->validateEffects();
    }
}

void enemies::setBase(const position &p) {
    base = p;
}

void enemies::resetGainedMoney() {
    _gainedMoney = 0;
}
