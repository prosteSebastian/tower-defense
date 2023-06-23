//
// Created by prokoseb on 16.5.23.
//

#include "config.h"
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <set>
#include <unordered_set>
#include "../exceptions/config_error.h"


void config::loadConfig(const char *fileGameSettings) {
    if (!std::filesystem::exists(fileGameSettings)) {
        throw std::runtime_error("File not found");
    }
    if (!std::filesystem::is_regular_file(fileGameSettings)) {
        throw std::runtime_error("File is not a regular file");
    }

    std::ifstream gameSettings(fileGameSettings);
    if (gameSettings.fail()) {
        throw std::runtime_error("File could not be opened");
    }
    json config;

    config = json::parse(gameSettings);

    checkAndParseConfig(config);

    std::cout << rang::fg::green << "Config byl uspesne nacten" << rang::fg::reset << std::endl;
}

void config::checkAndParseConfig(const json &config) {
    if (!config.contains("gameSettings") || !config.contains("objects")) {
        throw config_error("Missing column/s");
    }
    const json &gameSettings = config["gameSettings"];
    checkAndParseGameConfig(gameSettings);

    const json &objects = config["objects"];
    if (!objects.contains("towers") || !objects.contains("enemies")) {
        throw config_error("Missing column/s");
    }
    const json &objectsTowers = config["objects"]["towers"];
    checkAndParseTowersConfig(objectsTowers);

    if (!objects.contains("enemies")) {
        throw config_error("Missing column/s");
    }
    const json &objectsEnemies = config["objects"]["enemies"];
    checkAndParseEnemiesConfig(objectsEnemies);
}

void config::checkAndParseGameConfig(const json &gameSettings) {
    struct gameSettings gs{};
    const static std::unordered_set<std::string> gameConstants =
            {"waveSettings", "aiSettings", "towerSettings", "enemySettings", "tileSymbols", "gameRules"};
    for (const auto &i: gameSettings.items()) {
        if (gameConstants.count(i.key().c_str()) == 0) {
            throw config_error("Wrong column/s");
        }
    }
    if (gameSettings.size() != gameConstants.size()) {
        throw config_error("Missing column/s");
    }
    const static std::unordered_set<std::string> waveConstants =
            {"newWave", "playerInput", "spawnFrequency", "moneyPerWave", "scorePerWave", "winOnWave"};
    const json &waveSettings = gameSettings["waveSettings"];
    for (const auto &i: waveSettings.items()) {
        if (waveConstants.count(i.key().c_str()) == 0) {
            throw config_error("Wrong column/s");
        }
    }
    if (waveSettings.size() != waveConstants.size()) {
        throw config_error("Missing column/s");
    }

    for (const auto &i: waveSettings.items()) {
        if (!i.value().is_number()) {
            throw config_error("Wrong value");
        }
        if (i.value().get<int>() <= 0) {
            throw config_error("Wrong value");
        }
    }

    wave ws(waveSettings["newWave"].get<int>(), waveSettings["playerInput"].get<int>(),
            waveSettings["spawnFrequency"].get<int>(),
            waveSettings["moneyPerWave"].get<int>(), waveSettings["scorePerWave"].get<int>(),
            waveSettings["winOnWave"].get<int>());
    gs._waveSettings = ws;

    const static std::unordered_set<std::string> aiConstants =
            {"bfsPathLimit", "towerPowerConstant", "hpBoost", "speedBoost", "dmgBoost"};
    const json &aiSettings = gameSettings["aiSettings"];
    for (const auto &i: aiSettings.items()) {
        if (aiConstants.count(i.key().c_str()) == 0) {
            throw config_error("Wrong column/s");
        }
    }
    if (aiSettings.size() != aiConstants.size()) {
        throw config_error("Missing column/s");
    }

    if (!aiSettings["bfsPathLimit"].is_number() || !aiSettings["towerPowerConstant"].is_number() ||
        !aiSettings["hpBoost"].is_number()
        || !aiSettings["speedBoost"].is_number_float() || !aiSettings["dmgBoost"].is_number()) {
        throw config_error("Wrong value");
    }
    if (aiSettings["bfsPathLimit"].get<int>() <= 0 || aiSettings["towerPowerConstant"].get<int>() <= 0 ||
        aiSettings["hpBoost"].get<int>() <= 0
        || aiSettings["speedBoost"].get<float>() <= 0 || aiSettings["dmgBoost"].get<int>() <= 0) {
        throw config_error("Wrong value");
    }

    ai aiS(aiSettings["bfsPathLimit"].get<int>(), aiSettings["towerPowerConstant"].get<int>(),
           aiSettings["hpBoost"].get<int>(),
           aiSettings["speedBoost"].get<float>(), aiSettings["dmgBoost"].get<int>());
    gs._aiSettings = aiS;


    const json &towerSettings = gameSettings["towerSettings"];
    const static std::unordered_set<std::string> towerConstants =
            {"dmgIncrease", "rangeIncrease", "costDmgIncrease", "killRewardDivision", "sellValueDivision",
             "costRangeIncrease"};
    for (const auto &i: towerSettings.items()) {
        if (towerConstants.count(i.key().c_str()) == 0) {
            throw config_error("Wrong column/s");
        }
    }
    if (towerSettings.size() != towerConstants.size()) {
        throw config_error("Missing column/s");
    }

    if (!towerSettings["dmgIncrease"].is_number() || !towerSettings["rangeIncrease"].is_number() ||
        !towerSettings["costDmgIncrease"].is_number_float()
        || !towerSettings["killRewardDivision"].is_number() || !towerSettings["sellValueDivision"].is_number() ||
        !towerSettings["costRangeIncrease"].is_number_float()) {
        throw config_error("Wrong value");
    }
    if (towerSettings["dmgIncrease"].get<int>() <= 0 || towerSettings["rangeIncrease"].get<int>() <= 0 ||
        towerSettings["costDmgIncrease"].get<float>() <= 0
        || towerSettings["killRewardDivision"].get<int>() <= 0 || towerSettings["sellValueDivision"].get<int>() <= 0 ||
        towerSettings["costRangeIncrease"].get<float>() <= 0) {
        throw config_error("Wrong value");
    }
    towerS ts(towerSettings["dmgIncrease"].get<int>(), towerSettings["rangeIncrease"].get<int>(),
              towerSettings["costDmgIncrease"].get<float>(),
              towerSettings["costRangeIncrease"].get<float>(),
              towerSettings["killRewardDivision"].get<int>(), towerSettings["sellValueDivision"].get<int>());
    gs._towerSettings = ts;


    const json &enemySettings = gameSettings["enemySettings"];
    const static std::unordered_set<std::string> enemyConstants =
            {"deathScoreDivision"};
    for (const auto &i: enemySettings.items()) {
        if (enemyConstants.count(i.key().c_str()) == 0) {
            throw config_error("Wrong column/s");
        }
    }
    if (enemySettings.size() != enemyConstants.size()) {
        throw config_error("Missing column/s");
    }
    if (!enemySettings["deathScoreDivision"].is_number()) {
        throw config_error("Wrong value");
    }
    if (enemySettings["deathScoreDivision"].get<int>() <= 0) {
        throw config_error("Wrong value");
    }

    enemyS es(enemySettings["deathScoreDivision"].get<int>());
    gs._enemySettings = es;

    const json &tileSettings = gameSettings["tileSymbols"];
    const static std::unordered_set<std::string> tileConstants =
            {"path", "towerPlacement", "enemySpawnPoint", "wall", "base"};
    for (const auto &i: tileSettings.items()) {
        if (tileConstants.count(i.key().c_str()) == 0) {
            throw config_error("Wrong column/s");
        }
    }
    if (tileSettings.size() != tileConstants.size()) {
        throw config_error("Missing column/s");
    }

    for (const auto &i: tileSettings.items()) {
        if (!i.value().is_string()) {
            throw config_error("Wrong value of column/s");
        }
        if (i.value().get<std::string>().size() != 1) {
            throw config_error("Wrong value of column/s");
        }
    }

    std::set<char> setTiles;
    for (auto &i: tileSettings) {
        if (i.get<std::string>()[0] == '\0' || i.get<std::string>()[0] == '\n' || i.get<std::string>()[0] == '\r' ||
            i.get<std::string>()[0] == '\t') {
            throw config_error("Wrong value of column/s");
        }
        if (setTiles.count(i.get<std::string>()[0]) != 0) {
            throw config_error("Duplicate symbols");
        }
        setTiles.insert(i.get<std::string>()[0]);
    }

    tileSymbols tiles(tileSettings["path"].get<std::string>()[0], tileSettings["towerPlacement"].get<std::string>()[0],
                      tileSettings["enemySpawnPoint"].get<std::string>()[0],
                      tileSettings["base"].get<std::string>()[0], tileSettings["wall"].get<std::string>()[0]);
    gs._tileSymbols = tiles;

    const json &gameRules = gameSettings["gameRules"];
    const static std::unordered_set<std::string> gameRulesConstants =
            {"baseHp", "baseMoney", "maxTowerPlacement", "maxEnemySpawn", "maxWidth", "maxHeight"};
    for (const auto &i: gameRules.items()) {
        if (gameRulesConstants.count(i.key().c_str()) == 0) {
            throw config_error("Wrong column/s");
        }
    }
    if (gameRules.size() != gameRulesConstants.size()) {
        throw config_error("Missing column/s");
    }
    for (const auto &i: gameRules.items()) {
        if (!i.value().is_number()) {
            throw config_error("Wrong value of column/s");
        }
        if (i.value().get<int>() <= 0) {
            throw config_error("Wrong value of column/s");
        }
    }

    struct gameRules gr(gameRules["baseHp"].get<int>(), gameRules["baseMoney"].get<int>(),
                        gameRules["maxTowerPlacement"].get<int>(),
                        gameRules["maxEnemySpawn"].get<int>(), gameRules["maxWidth"].get<int>(),
                        gameRules["maxHeight"].get<int>());
    gs._gameRules = gr;

    _gameSettings = gs;
}

void config::checkAndParseTowersConfig(const json &objectsTowers) {
    std::unordered_set<std::string> effectOptions{
            "burn", "shot", "weakness", "slow"
    };
    std::unordered_set<std::string> attackOptions{
            "closestAttack", "snipeAttack", "aoeAttack"
    };
    std::unordered_map<std::string, rang::fg> colorOptions{
            {"red",     rang::fg::red},
            {"green",   rang::fg::green},
            {"blue",    rang::fg::blue},
            {"yellow",  rang::fg::yellow},
            {"cyan",    rang::fg::cyan},
            {"magenta", rang::fg::magenta},
            {"gray",    rang::fg::gray}
    };

    const static std::unordered_set<std::string> towerConstants =
            {"symbol", "range", "damage", "cost", "attack", "effects", "color"};
    for (const auto &[key, val]: objectsTowers.items()) {
        for (const auto &i: val.items()) {
            if (towerConstants.count(i.key().c_str()) == 0) {
                throw config_error("Wrong column/s");
            }
        }
        if (val.size() != towerConstants.size()) {
            throw config_error("Missing column/s");
        }

        if (!val["symbol"].is_string() || !val["range"].is_number() || !val["damage"].is_number() ||
            !val["cost"].is_number() || !val["color"].is_string()) {
            throw config_error("Wrong type of column/s");
        }
        rang::fg color;
        if (colorOptions.count(val["color"].get<std::string>()) == 0) {
            throw config_error("Wrong value of column/s");
        }
        color = colorOptions[val["color"].get<std::string>()];

        json attack = val["attack"];
        const static std::unordered_set<std::string> attackConstants =
                {"type", "reloadTime"};
        for (const auto &i: attack.items()) {
            if (attackConstants.count(i.key().c_str()) == 0) {
                throw config_error("Wrong column/s");
            }
        }
        if (attack.size() != attackConstants.size()) {
            throw config_error("Missing column/s");
        }
        if (!attack["type"].is_string() || !attack["reloadTime"].is_number()) {
            throw config_error("Wrong type of column/s");
        }

        if (attackOptions.count(attack["type"].get<std::string>()) == 0 || attack["reloadTime"].get<int>() <= 0) {
            throw config_error("Wrong value of column/s");
        }
        struct attack att(attack["type"].get<std::string>(), attack["reloadTime"].get<int>());

        json effects = val["effects"];
        std::vector<effectConfig> effectsVector;
        for (const auto &[type, duration]: effects.items()) {
            if (!duration.is_number() || duration.get<int>() <= 0 || effectOptions.count(type) == 0) {
                throw config_error("Wrong value of column/s");
            }
            effectsVector.emplace_back(type, duration.get<int>());
        }


        std::string name = key;
        char symbol = val["symbol"].get<std::string>()[0];
        int range = val["range"].get<int>();
        int damage = val["damage"].get<int>();
        int cost = val["cost"].get<int>();

        if (name.empty() || symbol == '\0' || isspace(symbol) || range <= 0 || damage <= 0 || cost <= 0) {
            throw config_error("Wrong value of column/s");
        }
        towerConfig tmp(name, symbol, range, damage, cost, att, effectsVector, color);
        _towerConfig.push_back(tmp);
    }
}

void config::checkAndParseEnemiesConfig(const json &objectsEnemies) {
    std::unordered_set<std::string> abilityOptions{
            "heal", "invincibility", "speed"
    };
    const static std::unordered_set<std::string> enemyConstants =
            {"symbol", "health", "speed", "reward", "damage", "abilities"};
    for (const auto &[key, val]: objectsEnemies.items()) {
        for (const auto &i: val.items()) {
            if (enemyConstants.count(i.key().c_str()) == 0) {
                throw config_error("Wrong column/s");
            }
        }
        if (val.size() != enemyConstants.size()) {
            throw config_error("Missing column/s");
        }
        if (!val["symbol"].is_string() || !val["health"].is_number() || !val["speed"].is_number() ||
            !val["reward"].is_number() || !val["damage"].is_number()) {
            throw config_error("Wrong type of column/s");
        }

        std::vector<abilityConfig> abilities;
        const static std::unordered_set<std::string> abilityConstants =
                {"cd", "range", "power"};
        for (const auto &[name, properties]: val["abilities"].items()) {
            if (abilityOptions.count(name) == 0) {
                throw config_error("Wrong value of column/s");
            }
            for (const auto &i: properties.items()) {
                if (abilityConstants.count(i.key().c_str()) == 0) {
                    throw config_error("Wrong column/s");
                }
            }
            if (properties.size() != abilityConstants.size()) {
                throw config_error("Missing column/s");
            }

            if (!properties["cd"].is_number() || !properties["range"].is_number() || !properties["power"].is_number()) {
                throw config_error("Wrong type of column/s");
            }

            if (properties["cd"].get<int>() <= 0 || properties["range"].get<int>() <= 0 ||
                properties["power"].get<int>() <= 0) {
                throw config_error("Wrong value of column/s");
            }
            abilityConfig tmp(name, properties["cd"].get<int>(), properties["range"].get<int>(),
                              properties["power"].get<int>());
            abilities.emplace_back(tmp);
        }
        std::string name = key;
        char symbol = val["symbol"].get<std::string>()[0];
        int health = val["health"].get<int>();
        int speed = val["speed"].get<int>();
        int reward = val["reward"].get<int>();
        int damage = val["damage"].get<int>();

        if (name.empty() || symbol == '\0' || health <= 0 || speed <= 0 || reward <= 0 || damage < 0) {
            throw config_error("Wrong value of column/s");
        }
        enemyConfig tmp(name, symbol, health, speed, reward, damage, abilities);
        _enemyConfig.push_back(tmp);
    }
}



