//
// Created by prokoseb on 9.5.23.
//

#ifndef TOWER_DEFENSE_REGULAR_H
#define TOWER_DEFENSE_REGULAR_H

#include "passage.h"

/**
 * @brief Passage that finds any path from start to end and returns it.
 */
class regular : public passage {
public:
    std::deque<position> findPath(const tileMap &m, const position &pos) const override;

    std::unique_ptr<passage> clone() const override;
};


#endif //TOWER_DEFENSE_REGULAR_H
