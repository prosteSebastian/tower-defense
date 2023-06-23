//
// Created by prokoseb on 25.5.23.
//

#include "slow.h"

void slow::evaluate(properties &prop) {
    if (_duration > 0) {
        prop._stats._speed -= _effectPower;
        _duration--;
    }
    if (_duration <= 0) {
        prop._stats._speed = prop._originalStats._speed;
    }
}

void slow::print(std::ostream &out) const {
    out << rang::bg::green;
}

void slow::resetPrint(std::ostream &out) const {
    out << rang::bg::reset;
}

std::shared_ptr<effect> slow::clone() const {
    return std::make_shared<slow>(*this);
}

void slow::saveEffect(std::ostream &buffer) const {
    buffer << "slow " << _duration << " " << _effectPower << std::endl;
}
