//
// Created by prokoseb on 25.4.23.
//
#include "tower.h"

tower::tower(char symbol, const position &p, int damage, int range, int price, std::unique_ptr<fire> attack,
             std::string name, rang::fg color)
        : _color(color), _attack(std::move(attack)), _stats(name, symbol, p, damage, range, price, 1) {}


tower::tower(const tower &t) : _color(t._color), _attack(t._attack->clone()), _stats(t._stats) {}

tower &tower::operator=(const tower &t) {
    _stats = t._stats;
    _color = t._color;
    _attack = t._attack->clone();
    return *this;
}


void tower::resetKillScore() {
    _stats._killScore = 0;
}

void tower::attack(const position &towerPos, int range, const enemies &enemyMap) {
    _attack->shoot(towerPos, range, enemyMap);
    _stats._killScore = _attack->getKillScore();
    _attack->resetKillScore();
}

void tower::upgradeDamage(int &money, const std::unique_ptr<tower> &tower, bool &success, int dmgIncrease,
                          float costIncrease) {
    int cost = (_stats._cost * _stats._level * (costIncrease - 1)); //increasing cost of upgrade
    if (money - cost >= 0) {
        _stats._damage += dmgIncrease;
        money -= cost;
        _stats._cost *= costIncrease;
        _stats._level++;
        tower->_attack->upgradeEffect(dmgIncrease);
        success = true;
    } else {
        success = false;
    }
}

void tower::upgradeRange(int &money, bool &success, int rangeIncrease, float costIncrease) {
    int cost = (_stats._cost * _stats._level * (costIncrease - 1)); //increasing cost of upgrade
    if (money - cost >= 0) {
        _stats._range += rangeIncrease;
        money -= cost;
        _stats._cost *= costIncrease;
        _stats._level++;
        success = true;
    } else {
        success = false;
    }
}

void tower::print(std::ostream &out) const {
    out << _color << _stats._symbol << rang::fg::reset;
}

void tower::saveTower(std::ostream &buffer) const {
    _stats.saveStats(buffer);
    _attack->saveFire(buffer);
}

void tower::addEffect(const std::shared_ptr<effect> &e) {
    _attack->addEffect(e->clone());
}

void tower::incrementReloadTime() {
    _attack->incrementReloadTime();
}

void tower::setStatsFomSavedGame(const position &p, int dmg, int range, int cost, int lvl) {
    _stats._position = p;
    _stats._damage = dmg;
    _stats._range = range;
    _stats._cost = cost;
    _stats._level = lvl;
}

void tower::setRemainingReload(int remainingReload) {
    _attack->setRemainingReload(remainingReload);
}

std::unique_ptr<tower> tower::clone() const {
    return std::make_unique<tower>(*this);
}

void tower::setPosition(const position &p) {
    _stats._position = p;
}




