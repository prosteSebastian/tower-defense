//
// Created by prokoseb on 4.6.23.
//

#include "loader.h"
#include "../exceptions/load_error.h"
#include "../attacks/aoeAttack.h"
#include "../attacks/snipeAttack.h"
#include "../attacks/closestAttack.h"
#include "../effects/slow.h"
#include "../effects/shot.h"
#include "../effects/burn.h"
#include "../effects/weakness.h"
#include "../abilities/heal.h"
#include "../abilities/speed.h"
#include "../abilities/invincibility.h"
#include "../exceptions/config_error.h"
#include "../passages/regular.h"
#include "../passages/bfs.h"

void loader::loadTowers(const std::vector<towerConfig> &tg, std::vector<std::unique_ptr<tower>> &towers) const {
    std::map<std::string, std::function<void(const towerConfig &)>> towerMap;
    towerMap["aoeAttack"] = [&](const towerConfig &tow) {
        tower t(tow._symbol, {1, 1}, tow._damage, tow._range, tow._cost,
                std::make_unique<aoeAttack>(tow._attack._reloadTime), tow._name, tow._color);
        for (const auto &effect: tow._effects) {
            addEffectToTower(t, effect, tow);
        }
        auto it = std::lower_bound(towers.begin(), towers.end(), t,
                                   [](const std::unique_ptr<tower> &a, const tower &b) {
                                       return a->getStats()._cost < b.getStats()._cost;
                                   });
        towers.insert(it, std::make_unique<tower>(t));
    };
    towerMap["closestAttack"] = [&](const towerConfig &tow) {
        tower t(tow._symbol, {1, 1}, tow._damage, tow._range, tow._cost,
                std::make_unique<closestAttack>(tow._attack._reloadTime), tow._name, tow._color);
        for (const auto &effect: tow._effects) {
            addEffectToTower(t, effect, tow);
        }
        auto it = std::lower_bound(towers.begin(), towers.end(), t,
                                   [](const std::unique_ptr<tower> &a, const tower &b) {
                                       return a->getStats()._cost < b.getStats()._cost;
                                   });
        towers.insert(it, std::make_unique<tower>(t));
    };
    towerMap["snipeAttack"] = [&](const towerConfig &tow) {
        tower t(tow._symbol, {1, 1}, tow._damage, tow._range, tow._cost,
                std::make_unique<snipeAttack>(tow._attack._reloadTime), tow._name, tow._color);
        for (const auto &effect: tow._effects) {
            addEffectToTower(t, effect, tow);
        }
        auto it = std::lower_bound(towers.begin(), towers.end(), t,
                                   [](const std::unique_ptr<tower> &a, const tower &b) {
                                       return a->getStats()._cost < b.getStats()._cost;
                                   });
        towers.insert(it, std::make_unique<tower>(t));
    };
    for (const auto &tow: tg) {
        if (towerMap.count(tow._attack._type) != 0) {
            towerMap[tow._attack._type](tow);
        } else {
            throw load_error("Wrong value");
        }
    }
}

void loader::addEffectToTower(tower &t, const effectConfig &effect, const towerConfig &tow) const {
    if (effect._type == "slow") {
        t.addEffect(std::make_unique<slow>(effect._duration, tow._damage));
    } else if (effect._type == "burn") {
        t.addEffect(std::make_unique<burn>(effect._duration, tow._damage));
    } else if (effect._type == "weakness") {
        t.addEffect(std::make_unique<weakness>(effect._duration, tow._damage));
    } else if (effect._type == "shot") {
        t.addEffect(std::make_unique<shot>(effect._duration, tow._damage));
    }
}

void loader::loadEnemies(const std::vector<enemyConfig> &eg, std::vector<std::unique_ptr<enemy>> &enemies) const {
    for (const auto &en: eg) {
        enemy e(-1, -1, en._symbol, en._hp, en._speed, en._reward, en._damage, en._name);
        auto it = std::lower_bound(enemies.begin(), enemies.end(), e,
                                   [](const std::unique_ptr<enemy> &a, const enemy &b) {
                                       return a->getStats()._reward < b.getStats()._reward;
                                   });
        for (const auto &ab: en._abilities) {
            if (ab._name == "heal") {
                e.addAbility(std::make_unique<heal>(ab._range, ab._cooldown, ab._abilityPower));
            } else if (ab._name == "speed") {
                e.addAbility(std::make_unique<speed>(ab._range, ab._cooldown, ab._abilityPower));
            } else if (ab._name == "invincibility") {
                e.addAbility(std::make_unique<invincibility>(ab._range, ab._cooldown));
            } else {
                throw load_error("Wrong value");
            }
        }
        enemies.insert(it, std::make_unique<enemy>(std::move(e)));
    }
}

void loader::loadTheGame(std::ifstream &file, gameStats &stats, const std::vector<std::unique_ptr<tower>> &towers,
                         std::list<std::unique_ptr<tower>> &listTowers,
                         const std::vector<std::unique_ptr<enemy>> &enemies,
                         std::list<std::unique_ptr<enemy>> &enemyMap) {
    loadGameConstants(file, stats);

    loadSavedTowers(file, towers, listTowers);

    loadSavedEnemies(file, enemies, enemyMap);
}

void loader::loadGameConstants(std::ifstream &file, gameStats &stats) {
    if (auto val = readInt(file); val.has_value()) {
        stats._money = val.value();
    } else {
        throw load_error("Wrong value");
    }
    if (auto val = readInt(file); val.has_value()) {
        stats._baseHp = val.value();
    } else {
        throw load_error("Wrong value");
    }
    if (auto val = readInt(file); val.has_value()) {
        stats._round = val.value();
    } else {
        throw load_error("Wrong value");
    }
    if (auto val = readInt(file); val.has_value()) {
        stats._wave = val.value();
    } else {
        throw load_error("Wrong value");
    }
    if (auto val = readInt(file); val.has_value()) {
        stats._score = val.value();
    } else {
        throw config_error("Wrong value");
    }
}

std::optional<unsigned int> loader::readInt(std::ifstream &file) {
    std::size_t len = 0;
    int val = 0;
    std::string line;
    try {
        std::getline(file, line);
        val = std::stoi(line, &len);
    }
    catch (std::exception &e) {
        return std::nullopt;
    }
    if (len != line.size()) {
        return std::nullopt;
    }
    if (val < 0) {
        return std::nullopt;
    }
    return val;
}

void loader::loadSavedTowers(std::ifstream &file, const std::vector<std::unique_ptr<tower>> &towers,
                             std::list<std::unique_ptr<tower>> &listTowers) {
    std::string line;
    while (std::getline(file, line) && !line.empty()) {
        std::istringstream iss(line);
        std::string name;
        iss >> name;
        bool found = false;
        for (const auto &tow: towers) {
            if (tow->getStats()._name == name) {
                found = true;
                size_t x, y;
                iss >> x >> y;
                int dmg, range, cost, lvl, remainingReload;
                iss >> dmg >> range >> cost >> lvl >> remainingReload;
                if (dmg < 0 || range < 0 || cost < 0 || lvl < 0) {
                    throw load_error("Wrong value");
                }
                auto t = tow->clone();
                t->setStatsFomSavedGame({x, y}, dmg, range, cost, lvl);
                if (remainingReload < 0) {
                    throw load_error("Wrong value");
                }
                t->setRemainingReload(remainingReload);
                auto it = std::lower_bound(listTowers.begin(), listTowers.end(), t,
                                           [](const std::unique_ptr<tower> &a, const std::unique_ptr<tower> &b) {
                                               return a->getStats()._position < b->getStats()._position;
                                           });
                listTowers.insert(it, std::move(t));
                break;
            }
        }
        if (!found) {
            throw load_error("Wrong value");
        }
    }

}

void loader::loadSavedEnemies(std::ifstream &file, const std::vector<std::unique_ptr<enemy>> &enemies,
                              std::list<std::unique_ptr<enemy>> &listEnemies) {
    std::string lineEnemy;
    while (std::getline(file, lineEnemy)) {
        std::istringstream iss(lineEnemy);
        std::string name;
        iss >> name;
        bool found = false;
        for (const auto &enemy: enemies) {
            if (enemy->getStats()._name == name) {
                found = true;
                size_t x, y;
                int hp, speed, reward, dmg;
                iss >> hp >> speed >> reward >> dmg >> x >> y;
                if (hp < 0 || reward < 0 || dmg < 0) {
                    throw load_error("Wrong value");
                }
                auto e = enemy->clone();
                e->setStatsFromSavedGame(hp, speed, reward, dmg, {x, y});
                if (e->hasFlag(flags::dumb)) {
                    e->setPassage(std::make_unique<regular>());
                } else {
                    e->setPassage(std::make_unique<bfs>());
                }

                std::string lineEA;
                while (std::getline(file, lineEA) && !lineEA.empty()) {
                    std::istringstream iss2(lineEA);
                    std::string effectName;
                    int duration, effectPower;
                    iss2 >> effectName >> duration >> effectPower;
                    if (effectName == "slow") {
                        e->applyEffect(std::make_unique<slow>(duration, effectPower));
                    } else if (effectName == "burn") {
                        e->applyEffect(std::make_unique<burn>(duration, effectPower));
                    } else if (effectName == "weakness") {
                        e->applyEffect(std::make_unique<weakness>(duration, effectPower));
                    } else if (effectName == "shot") {
                        e->applyEffect(std::make_unique<shot>(duration, effectPower));
                    } else {
                        throw load_error("Wrong value");
                    }
                }
                e->addFlag(flags::canBeAttacked);
                listEnemies.push_back(std::move(e));
                break;
            }
        }
        if (!found) {
            throw load_error("Wrong value");
        }
    }
}
