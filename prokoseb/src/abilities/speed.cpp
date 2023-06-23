//
// Created by s on 26.5.23.
//

#include "speed.h"
#include "../../libs/rang.hpp"
#include "../utils/distance.cpp"

void speed::cast(const position &pos, properties &prop) {
    if (isOnCooldown()) {
        return;
    }

    if (distance(pos, prop._stats._position) <= _range) {
        prop._stats._speed += _abilityPower;
        _remainingCooldown = 0;
    }
}

void speed::print(std::ostream &out) const {
    out << rang::style::italic;
}

std::shared_ptr<ability> speed::clone() const {
    return std::make_shared<speed>(*this);
}


