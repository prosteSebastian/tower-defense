//
// Created by prokoseb on 3.6.23.
//
#include "properties.h"

properties::properties(char symbol, int health, int speed, int reward, int damage, size_t x, size_t y, std::string name)
        :
        _stats(symbol, health, speed, reward, damage, {x, y}, std::move(name)), _originalStats(_stats) {}

void properties::removeFlag(const flags &f) {
    _flags.erase(f);
}

void properties::saveProperties(std::ostream &buffer) const {
    _stats.saveStats(buffer);
}


