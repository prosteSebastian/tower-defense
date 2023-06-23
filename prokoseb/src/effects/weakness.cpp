//
// Created by s on 26.5.23.
//

#include "weakness.h"
#include "../../libs/rang.hpp"

void weakness::evaluate(properties &prop) {
    if (_duration > 0) {
        prop._stats._damage /= _effectPower;
        _duration--;
    }
    if (_duration <= 0) {
        prop._stats._damage = prop._originalStats._damage;
    }
}

void weakness::print(std::ostream &out) const {
    out << rang::bgB::gray;
}

void weakness::resetPrint(std::ostream &out) const {
    out << rang::bg::reset;
}

void weakness::saveEffect(std::ostream &buffer) const {
    buffer << "weakness " << _duration << " " << _effectPower << std::endl;
}

std::shared_ptr<effect> weakness::clone() const {
    return std::make_shared<weakness>(*this);
}
