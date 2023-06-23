//
// Created by prokoseb on 3.6.23.
//

#include "enemyStats.h"

stats::stats(char symbol, int health, int speed, int reward, int damage, position pos, std::string name) :
        _symbol(symbol), _health(health), _speed(speed), _reward(reward), _damage(damage), _position(pos),
        _name(std::move(name)) {}

void stats::saveStats(std::ostream &buffer) const {
    buffer << _name << " " << _health << " " << _speed << " " << _reward << " " << _damage << " " << _position.x << " "
           << _position.y << std::endl;
}


