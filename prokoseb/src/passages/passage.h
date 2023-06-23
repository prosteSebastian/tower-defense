//
// Created by prokoseb on 9.5.23.
//

#ifndef TOWER_DEFENSE_PASSAGE_H
#define TOWER_DEFENSE_PASSAGE_H

#include <utility>
#include <deque>
#include "../utils/position.h"
#include "../maps/tileMap.h"

/**
 * @brief Interface for finding path from position to the base
 * @throws std::invalid_argument if there is no path to the base
 */
class passage {
public:
    virtual ~passage() = default;

    /**
     * @brief Finds path from position to the base and returns it as a deque of positions
     * @param m Map to find path on
     * @param pos Position to find path from
     * @return the path
     */
    virtual std::deque<position> findPath(const tileMap &m, const position &pos) const = 0;

    /**
     * @brief Clones the passage
     * @return the clone
     */
    virtual std::unique_ptr<passage> clone() const = 0;
};


#endif //TOWER_DEFENSE_PASSAGE_H
