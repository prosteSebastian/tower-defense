//
// Created by s on 26.4.23.
//

#ifndef TOWER_DEFENSE_TILEMAP_H
#define TOWER_DEFENSE_TILEMAP_H

#include<memory>
#include<unordered_map>
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include "../objects/tile.h"
#include "../utils/position.h"
#include "../utils/type.h"
#include "../config/config.h"


/**
 * @brief Represents a map of tiles
 * @details Map is represented as a 2D vector of unique pointers to tiles
 * @see tile
 */
struct tileMap {
    /**
     * @brief Constructs a map of tiles
     * @param fileName Name of the file to load map from
     * @param ts Config of tile symbols
     * @param gr Config of game rules
     * @throws std::invalid_argument if file is not valid (for example sym. links)
     * @throws std::invalid_argument when the file is not found or there was an error while opening it
     * @throws std::invalid_argument when the map exceeds the number of towerPlacementPoints
     * @throws std::invalid_argument when the map exceeds the number of enemySpawnPoints
     * @throws std::invalid_argument when the map exceeds the number of maximum base count
     * @throws std::invalid_argument when there is an invalid symbol in the map file that is not defined in config
     * @throws std::invalid_argument when the map exceeds the number of width
     * @throws std::invalid_argument when the map exceeds the number of height
     * @throws std::invalid_argument when the map does not have a base
     * @throws std::invalid_argument when the tower would be placed on an invalid tile
     * @throws std::invalid_argument when the map does not have a tower placement point
     * @throws std::invalid_argument when the map does not have a enemy spawn point
     */
    tileMap(const std::string &fileName, const tileSymbols &ts, const gameRules &gr);

    /**
     * @brief Takes the position in the map of towerPlacementPoints and set it to teh value of placed
     * @param pos Position to be set
     * @param placed Value to be set
     */
    void placedTower(const position &pos, bool placed);

    /**
     * @brief Return available path positions from a pos
     * @param pos Position to be checked
     * @return Vector of available path positions
     */
    const std::vector<position> getNeighbours(const position &pos) const;

    /**
     * @brief Print the tileMap
     * @param out The output stream to be printed to
     * @param map The tileMap to be printed
     * @return The output stream
     */
    friend std::ostream &operator<<(std::ostream &out, const tileMap &map);

    std::vector<std::vector<std::unique_ptr<tile>>> _objectMap;
    int _width;
    int _height;
    position _basePosition;
    tileSymbols _ts;
    gameRules _gr;
    std::vector<position> _enemySpawnPoints;
    std::vector<std::pair<position, bool>> _towerPlacementPoints;
};


#endif //TOWER_DEFENSE_TILEMAP_H
