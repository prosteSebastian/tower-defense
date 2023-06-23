//
// Created by prokoseb on 3.6.23.
//

#ifndef TOWER_DEFENSE_GAMESTATS_H
#define TOWER_DEFENSE_GAMESTATS_H

#include<ostream>

struct gameStats {
    void save(std::ostream &buffer) const {
        buffer << _money << std::endl;
        buffer << _baseHp << std::endl;
        buffer << _round << std::endl;
        buffer << _wave << std::endl;
        buffer << _score << std::endl;
    }

    const char *_fileName;
    int _baseHp;
    int _money;
    int _score = 0;
    int _wave = 0;
    int _round = 0;
};

#endif //TOWER_DEFENSE_GAMESTATS_H
