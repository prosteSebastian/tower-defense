//
// Created by s on 27.5.23.
//

#include "shot.h"
#include "../../libs/rang.hpp"

void shot::evaluate(properties &prop) {
    if (_duration > 0) {
        prop._stats._health -= _effectPower;
        _duration--;
    }
}

void shot::print(std::ostream &out) const {
    out << rang::fg::yellow;
}

void shot::resetPrint(std::ostream &out) const {
    out << rang::fg::reset;
}

void shot::saveEffect(std::ostream &buffer) const {
    buffer << "shot " << _duration << " " << _effectPower << std::endl;
}
