//
// Created by prokoseb on 3.6.23.
//

#include "position.h"

position::position(size_t x, size_t y) : x(x), y(y) {}

bool position::operator==(const position &rhs) const {
    return x == rhs.x && y == rhs.y;
}

bool position::operator!=(const position &rhs) const {
    return !(rhs == *this);
}

bool position::operator<(const position &rhs) const {
    return y < rhs.y || (y == rhs.y && x < rhs.x);
}

std::ostream &operator<<(std::ostream &out, const position &p) {
    out << "(" << p.x << "," << p.y << ")";
    return out;
}


