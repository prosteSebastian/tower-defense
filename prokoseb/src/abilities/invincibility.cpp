//
// Created by s on 27.5.23.
//

#include "invincibility.h"
#include "../../libs/rang.hpp"
#include "../utils/distance.cpp"

void invincibility::cast(const position &pos, properties &prop) {
    if (isOnCooldown()) {
        return;
    }
    if (distance(pos, prop._stats._position) <= _range) {
        prop.removeFlag(flags::canBeAttacked);
        _remainingCooldown = 0;
    }
}

void invincibility::print(std::ostream &out) const {
    out << rang::style::crossed;
}

std::shared_ptr<ability> invincibility::clone() const {
    return std::make_shared<invincibility>(*this);
}

