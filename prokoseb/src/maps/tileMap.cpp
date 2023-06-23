//
// Created by s on 26.4.23.
//

#include "tileMap.h"
#include<filesystem>

tileMap::tileMap(const std::string &fileName, const tileSymbols &ts, const gameRules &gr) : _ts(ts), _gr(gr) {

    if (!std::filesystem::is_regular_file(fileName)) {
        throw std::invalid_argument("Invalid file format");
    }
    std::ifstream file(fileName);
    if (file.fail()) {
        throw std::invalid_argument("File not found");
    }

    //helper map to convert char to tile type from config
    static std::unordered_map<char, type> tileUm = {
            {_ts._wall,            type::wall},
            {_ts._path,            type::path},
            {_ts._base,            type::base},
            {_ts._enemySpawnPoint, type::enemySpawn},
            {_ts._towerPlacement,  type::towerPlacement}
    };

    std::string line;
    size_t x = 0;
    size_t y = 0;
    size_t maxWidth = 0;
    int placedTower = 0;
    int enemySpawns = 0;
    int baseCount = 0;

    for (; std::getline(file, line);) {
        std::vector<std::unique_ptr<tile>> row;
        for (char c: line) {
            if (!tileUm.count(c)) {
                throw std::invalid_argument("Invalid character in map file"); //this should never happen
            }
            switch (tileUm.at(c)) {
                case type::wall:
                    row.emplace_back(std::make_unique<tile>(type::wall, c, x, y, rang::fgB::black));
                    break;
                case type::path:
                    row.emplace_back(std::make_unique<tile>(type::path, c, x, y, rang::fgB::cyan));
                    break;
                case type::towerPlacement:
                    row.emplace_back(std::make_unique<tile>(type::towerPlacement, c, x, y, rang::fgB::magenta));
                    _towerPlacementPoints.emplace_back(position{x, y}, true);
                    if (placedTower + 1 > _gr._maxTowerPlacement) {
                        throw std::invalid_argument("Map exceeds maximum tower placement");
                    }
                    placedTower++;
                    break;
                case type::enemySpawn:
                    row.emplace_back(std::make_unique<tile>(type::enemySpawn, c, x, y, rang::fgB::red));
                    _enemySpawnPoints.emplace_back(x, y);
                    if (enemySpawns + 1 > _gr._maxEnemySpawn) {
                        throw std::invalid_argument("Map exceeds maximum enemy spawn points");
                    }
                    enemySpawns++;
                    break;
                case type::base:
                    row.emplace_back(std::make_unique<tile>(type::base, c, x, y, rang::fgB::green));
                    _basePosition = {x, y};
                    if (baseCount + 1 != 1) {
                        throw std::invalid_argument("Map exceeds maximum base count");
                    }
                    baseCount++;
                    break;
                default:
                    throw std::invalid_argument("Invalid character in map file");
            }
            if (x + 1 > _gr._maxWidth) {
                throw std::invalid_argument("Map width exceeds maximum width");
            }
            x++;
        }
        _objectMap.push_back(std::move(row));
        if (x > maxWidth) {
            maxWidth = x;
        }
        if (y + 1 > _gr._maxHeight) {
            throw std::invalid_argument("Map height exceeds maximum height");
        }
        y++;
        x = 0;
    }
    if (placedTower < 1) {
        throw std::invalid_argument("Map must contain at least one tower placement point");
    }
    if (enemySpawns < 1) {
        throw std::invalid_argument("Map must contain at least one enemy spawn point");
    }
    if (baseCount != 1) {
        throw std::invalid_argument("Map must contain exactly one base");
    }
    _width = maxWidth;
    _height = y;
}

std::ostream &operator<<(std::ostream &out, const tileMap &map) {
    for (const auto &row: map._objectMap) {
        for (const auto &tile: row) {
            tile->print(out);
        }
        out << std::endl;
    }
    return out;
}

void tileMap::placedTower(const position &pos, bool placed) {
    for (auto &tPos: _towerPlacementPoints) {
        if (tPos.first == pos) {
            tPos.second = placed;
            return;
        }
    }
    throw std::invalid_argument("Invalid tower position");
}

const std::vector<position> tileMap::getNeighbours(const position &pos) const {
    std::vector<position> res;

    if (pos.x > 0 && _objectMap[pos.y].size() > pos.x - 1 && _objectMap[pos.y][pos.x - 1]->isWalkable()) {
        res.emplace_back(pos.x - 1, pos.y);
    }

    if (pos.x < _objectMap[pos.y].size() - 1 && _objectMap[pos.y][pos.x + 1]->isWalkable()) {
        res.emplace_back(pos.x + 1, pos.y);
    }

    if (pos.y > 0 && _objectMap[pos.y - 1].size() > pos.x && _objectMap[pos.y - 1][pos.x]->isWalkable()) {
        res.emplace_back(pos.x, pos.y - 1);
    }

    if (pos.y < _objectMap.size() - 1 && _objectMap[pos.y + 1].size() > pos.x &&
        _objectMap[pos.y + 1][pos.x]->isWalkable()) {
        res.emplace_back(pos.x, pos.y + 1);
    }

    return res;
}



