//
// Created by s on 26.5.23.
//

#include "heal.h"
#include "../utils/distance.cpp"
#include "../../libs/rang.hpp"

void heal::cast(const position &pos, properties &prop) {
    if (isOnCooldown()) {
        return;
    }
    if (distance(pos, prop._stats._position) <= _range && prop._stats._health != prop._originalStats._health) {
        prop._stats._health = std::min(prop._stats._health + _abilityPower, prop._originalStats._health);
        _remainingCooldown = 0;
    }
}

void heal::print(std::ostream &out) const {
    out << rang::style::underline;
}

std::shared_ptr<ability> heal::clone() const {
    return std::make_shared<heal>(*this);
}
