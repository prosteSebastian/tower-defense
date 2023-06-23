//
// Created by prokoseb on 25.4.23.
//

#include "enemy.h"

#include <utility>

enemy::enemy(int x, int y, char symbol, int health, int speed, int reward, int damage, std::string name) :
        _propeties(symbol, health, speed, reward, damage, x, y, std::move(name)) {}

bool enemy::move() {

    if (_moves.empty()) {
        return false;
    } else {
        _propeties._stats._position = _moves.front();
        _moves.pop_front();
        return true;
    }
}

std::ostream &operator<<(std::ostream &out, const enemy &e) {
    return out << "Symbol: " << e._propeties._stats._symbol << " | Health: " << e._propeties._stats._health
               << " | Speed: " << e._propeties._stats._speed << " | Reward: "
               << e._propeties._stats._reward << " | Damage: " << e._propeties._stats._damage << " | Position: "
               << e._propeties._stats._position;
}

void enemy::generatePath(const tileMap &m) {
    _moves = _passage->findPath(m, _propeties._stats._position);
}

enemy::enemy(const enemy &e) : _moves(e._moves), _propeties(e._propeties) {
    for (const auto &ef: e._appliedEffects) {
        _appliedEffects.emplace_back(ef->clone());
    }
    for (const auto &ab: e._abilities) {
        _abilities.emplace_back(ab->clone());
    }
}

enemy &enemy::operator=(const enemy &e) {
    if (this != &e) {
        _propeties = e._propeties;
        _moves = e._moves;
        _propeties._flags = e._propeties._flags;
        _propeties._originalStats = e._propeties._originalStats;
        for (const auto &ef: e._appliedEffects) {
            _appliedEffects.emplace_back(ef->clone());
        }
        for (const auto &ab: e._abilities) {
            _abilities.emplace_back(ab->clone());
        }

    }
    return *this;
}

void enemy::print(std::ostream &out) const {
    //call print on polymorphic abilities and effects to get the correct styling
    for (const auto &effect: _appliedEffects) {
        effect->print(out);
    }
    for (const auto &ab: _abilities) {
        ab->print(out);
    }
    out << _propeties._stats._symbol;
    for (const auto &ab: _abilities) {
        ab->resetPrint(out);
    }
    for (const auto &effect: _appliedEffects) {
        effect->resetPrint(out);
    }

}

void enemy::evalEffects() {
    for (const auto &effect: _appliedEffects) {
        effect->evaluate(_propeties);
    }
}

void enemy::validateEffects() {
    std::vector<std::shared_ptr<effect>> newEffects;
    for (const auto &effect: _appliedEffects) {
        if (effect->getDuration() > 0) {
            newEffects.emplace_back(effect);
        }
    }
    _appliedEffects = newEffects;
}

void enemy::addFlag(const flags &flag) {
    if (_propeties._flags.count(flag) == 0) {
        _propeties._flags.emplace(flag);
    }
}

bool enemy::canBeAttacked() const {
    return _propeties._flags.count(flags::canBeAttacked) != 0;
}

void enemy::save(std::ostream &buffer) const {
    _propeties.saveProperties(buffer);

    for (const auto &effect: _appliedEffects) {
        effect->saveEffect(buffer);
    }
}

void enemy::setStatsFromSavedGame(int health, int speed, int reward, int damage, const position &pos) {
    _propeties._stats._health = health;
    _propeties._stats._speed = speed;
    _propeties._stats._reward = reward;
    _propeties._stats._damage = damage;
    _propeties._stats._position = pos;
}

bool enemy::hasFlag(const flags &flag) const {
    return _propeties._flags.count(flag) != 0;
}

position enemy::getPosition() const {
    return _propeties._stats._position;
}

std::unique_ptr<enemy> enemy::clone() const {
    return std::make_unique<enemy>(*this);
}

void enemy::applyEffect(const std::shared_ptr<effect> &e) {
    _appliedEffects.emplace_back(e->clone());
}

properties enemy::getProperties() const {
    return _propeties;
}

void enemy::setProperties(const properties &other) {
    _propeties = other;
}

void enemy::addAbility(const std::shared_ptr<ability> &a) {
    _abilities.emplace_back(a->clone());
}

void enemy::setPassage(std::unique_ptr<passage> passage) {
    _passage = std::move(passage);
}

std::vector<std::shared_ptr<ability>> enemy::getAbilities() const {
    return _abilities;
}

stats enemy::getStats() const {
    return _propeties._stats;
}


