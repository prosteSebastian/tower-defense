//
// Created by prokoseb on 4.5.23.
//

#ifndef TOWER_DEFENSE_TILE_H
#define TOWER_DEFENSE_TILE_H

#include <iostream>
#include "../utils/type.h"
#include "../utils/position.h"
#include "../../libs/rang.hpp"

/**
 * @brief Represents a tile on the map
 */
class tile {
public:
    /**
     * @brief Constructs a tile
     * @param id Type of the tile
     * @param symbol Symbol representing the tile
     * @param x x coordinate
     * @param y y coordinate
     * @param color Color of the tile to print
     */
    tile(type id, char symbol, int x, int y, const rang::fgB &color);

    /**
     * @brief Get position of tileb
     * @return Position of tile
     */
    position getPosition() const;

    /**
     * @brief Check if tile is walkable (path or base)
     * @return True if tile is walkable, false otherwise
     */
    bool isWalkable() const;

    /**
     * @brief Print tile to output stream
     * @param out Output stream
     */
    void print(std::ostream &out) const;

private:
    rang::fgB _color;
    type _type;
    char _symbol;
    position _position;
};


#endif //TOWER_DEFENSE_TILE_H
