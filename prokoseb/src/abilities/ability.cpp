//
// Created by s on 26.5.23.
//

#include "ability.h"
#include "../../libs/rang.hpp"

bool ability::isOnCooldown() const {
    return _cooldown != _remainingCooldown;
}

void ability::incrementCd() {
    _remainingCooldown++;
}

void ability::resetPrint(std::ostream &out) const {
    out << rang::style::reset;
}
