//
// Created by prokoseb on 12.5.23.
//

#ifndef TOWER_DEFENSE_BFS_H
#define TOWER_DEFENSE_BFS_H

#include "passage.h"
#include <queue>
#include "../maps/tileMap.h"

/**
 * @brief Passage that finds path using BFS to find shortest path to the base
 * @throws std::invalid_argument if there is no path to the base
 */
class bfs : public passage {
public:
    std::deque<position> findPath(const tileMap &m, const position &pos) const override;

    std::unique_ptr<passage> clone() const override;
};


#endif //TOWER_DEFENSE_BFS_H
