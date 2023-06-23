//
// Created by prokoseb on 4.5.23.
//
#include <iostream>
#include "tile.h"

tile::tile(type id, char symbol, int x, int y, const rang::fgB &color) :
        _color(color), _type(id), _symbol(symbol), _position(x, y) {}

position tile::getPosition() const {
    return _position;
}

bool tile::isWalkable() const {
    return _type == type::path || _type == type::base;
}

void tile::print(std::ostream &out) const {
    out << _color << _symbol << rang::fg::reset;
}
