//
// Created by prokoseb on 3.6.23.
//

#include "towerStats.h"
#include <ostream>

towertStats::towertStats(std::string name, char symbol, position pos, int damage, int range, int cost, int level) :
        _name(std::move(name)), _symbol(symbol), _position(pos), _damage(damage), _range(range), _cost(cost),
        _level(level) {}


void towertStats::saveStats(std::ostream &buffer) const {
    buffer << _name << " " << _position.x << " " << _position.y << " " << _damage << " " << _range << " " << _cost
           << " " << _level << " ";
}