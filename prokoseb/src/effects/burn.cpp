//
// Created by prokoseb on 25.5.23.
//

#include "burn.h"

void burn::evaluate(properties &prop) {
    if (_duration > 0) {
        prop._stats._health -= _effectPower;
        _duration--;
    }
}

std::shared_ptr<effect> burn::clone() const {
    return std::make_shared<burn>(*this);
}

void burn::print(std::ostream &out) const {
    out << rang::fg::red;
}

void burn::resetPrint(std::ostream &out) const {
    out << rang::fg::reset;
}

void burn::saveEffect(std::ostream &buffer) const {
    buffer << "burn " << _duration << " " << _effectPower << std::endl;
}
