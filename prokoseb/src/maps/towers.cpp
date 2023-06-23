//
// Created by prokoseb on 5.5.23.
//

#include "towers.h"
#include "../attacks/aoeAttack.h"

void towers::buildTower(int &money, const std::unique_ptr<tower> &t, const position &p, bool &success) {
    if (money - t->getStats()._cost < 0) {
        success = false;
        return;
    }
    std::unique_ptr<tower> newTower = t->clone();
    newTower->setPosition(p);
    auto it = std::lower_bound(_towers.begin(), _towers.end(), newTower,
                               [](const std::unique_ptr<tower> &a, const std::unique_ptr<tower> &b) {
                                   return a->getStats()._position < b->getStats()._position;
                               });
    _towers.insert(it, std::move(newTower));
    money -= t->getStats()._cost;
    success = true;
}

bool towers::isTower(const position &p) const {
    for (const auto &t: _towers) {
        if (t->getStats()._position == p) {
            return true;
        }
    }
    return false;
}

void towers::print(std::ostream &out, const position &p) const {
    for (const auto &x: _towers) {
        if (x->getStats()._position == p) {
            x->print(out);
        }
    }
}

void towers::attack(const enemies &enemyMap) {
    for (const auto &tower: _towers) {
        tower->attack(tower->getStats()._position, tower->getStats()._range, enemyMap);
        _killScore += tower->getStats()._killScore;
        tower->resetKillScore();
    }

}

void towers::reloadTowers() {
    for (const auto &tower: _towers) {
        tower->incrementReloadTime();
    }
}

void towers::resetKillScore() {
    _killScore = 0;
}

