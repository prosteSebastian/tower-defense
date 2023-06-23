//
// Created by prokoseb on 16.5.23.
//

#ifndef TOWER_DEFENSE_CONFIG_H
#define TOWER_DEFENSE_CONFIG_H

#include"../../libs/json.hpp"
#include"../../libs/rang.hpp"

#include <string>
#include <utility>

using json = nlohmann::json;

/**
 * @brief Struct that holds the information about the ability of the enemy
 */
struct abilityConfig {
    abilityConfig(std::string name, int range, int cooldown, int power) : _name(std::move(name)), _range(range),
                                                                          _cooldown(cooldown), _abilityPower(power) {};
    std::string _name;
    int _range;
    int _cooldown;
    int _abilityPower;
};

/**
 * @brief Struct that holds the information about the enemy
 */
struct enemyConfig {
    enemyConfig(std::string name, char symbol, int hp, int speed, int reward, int damage,
                std::vector<abilityConfig> abilities) :
            _name(std::move(name)), _symbol(symbol), _hp(hp), _speed(speed), _reward(reward), _damage(damage),
            _abilities(std::move(abilities)) {};
    std::string _name;
    char _symbol;
    int _hp;
    int _speed;
    int _reward;
    int _damage;
    std::vector<abilityConfig> _abilities;
};

/**
 * @brief Struct that holds the information about attack, its type and reload time
 */
struct attack {
    attack(std::string type, int reloadTime) : _type(std::move(type)), _reloadTime(reloadTime) {};
    std::string _type;
    int _reloadTime;
};

/**
 * @brief Struct that holds the information about the effect of the tower
 */
struct effectConfig {
    effectConfig(std::string type, int duration) : _type(std::move(type)), _duration(duration) {};
    std::string _type;
    int _duration;
};

/**
 * @brief Struct that holds the information about the tower
 */
struct towerConfig {
    towerConfig(std::string name, char symbol, int range, int damage, int cost, attack at,
                std::vector<effectConfig> effects, rang::fg color) :
            _name(std::move(name)), _symbol(symbol), _range(range), _damage(damage), _cost(cost),
            _attack(std::move(at)),
            _effects(std::move(effects)), _color(color) {};
    std::string _name;
    char _symbol;
    int _range;
    int _damage;
    int _cost;

    attack _attack;
    std::vector<effectConfig> _effects;
    rang::fg _color;
};

/**
 * @brief Struct that holds the configuration about the wave
 */
struct wave {
    wave() = default;

    wave(int newWave, int playerInput, int spawnFrequency, int moneyPerWave, int scorePerWave, int winOnWave) :
            _newWave(newWave), _playerInput(playerInput), _spawnFrequency(spawnFrequency), _moneyPerWave(moneyPerWave),
            _scorePerWave(scorePerWave), _winOnWave(winOnWave) {};

    wave(const wave &w) = default;

    wave &operator=(const wave &w) = default;

    int _newWave;
    int _playerInput;
    int _spawnFrequency;
    int _moneyPerWave;
    int _scorePerWave;
    int _winOnWave;
};

/**
 * @brief Struct that store teh information about the ai sending the waves
 */
struct ai {
    ai() = default;

    ai(int bfsPathLimit, int towerPowerConstant, int hpBoost, double speedBoost, int dmgBoost) :
            bfsPathLimit(bfsPathLimit), towerPowerConstant(towerPowerConstant), hpBoost(hpBoost),
            speedBoost(speedBoost), dmgBoost(dmgBoost) {};

    ai(const ai &a) = default;

    ai &operator=(const ai &a) = default;

    int bfsPathLimit;
    int towerPowerConstant;
    int hpBoost;
    float speedBoost;
    int dmgBoost;
};

/**
 * @brief definition of the tower rules
 * @details the tower rules are used to calculate the price of the tower, the sell value of the tower etc.
 */
struct towerS {
    towerS() = default;

    towerS(int dmgIncrease, int rangeIncrease, float costDmgIncrease, float costRangeIncrease, int killRewardDivision,
           int sellValueDivision) :
            _dmgIncrease(dmgIncrease), _rangeIncrease(rangeIncrease), _costDmgIncrease(costDmgIncrease),
            _costRangeIncrease(costRangeIncrease), _killRewardDivision(killRewardDivision),
            _sellValueDivision(sellValueDivision) {};

    towerS(const towerS &t) = default;

    towerS &operator=(const towerS &t) = default;

    int _dmgIncrease;
    int _rangeIncrease;
    float _costDmgIncrease;
    float _costRangeIncrease;
    int _killRewardDivision;
    int _sellValueDivision;
};

/**
 * @brief definition of the enemy rules
 */
struct enemyS {
    enemyS() = default;

    enemyS(int deathScoreDivision) : _deathScoreDivision(deathScoreDivision) {};

    enemyS(const enemyS &e) = default;

    enemyS &operator=(const enemyS &e) = default;

    int _deathScoreDivision;
};

/**
 * @brief definition of the symbol of the tiles
 */
struct tileSymbols {
    tileSymbols() = default;

    tileSymbols(char path, char tower, char enemy, char base, char empty) :
            _path(path), _towerPlacement(tower), _enemySpawnPoint(enemy), _base(base), _wall(empty) {};

    tileSymbols(const tileSymbols &t) = default;

    tileSymbols &operator=(const tileSymbols &t) = default;

    char _path;
    char _towerPlacement;
    char _enemySpawnPoint;
    char _base;
    char _wall;
};

/**
 * @brief definition of the game rules
 */
struct gameRules {
    gameRules() = default;

    gameRules(int baseHp, int money, int maxTowerPlacement, int maxEnemySpawn, int maxWidth, int maxHeight) :
            _baseHp(baseHp), _money(money), _maxTowerPlacement(maxTowerPlacement), _maxEnemySpawn(maxEnemySpawn),
            _maxWidth(maxWidth), _maxHeight(maxHeight) {};
    int _baseHp;
    int _money;
    int _maxTowerPlacement;
    int _maxEnemySpawn;
    size_t _maxWidth;
    size_t _maxHeight;
};

/**
 * @brief definition of the game settings
 */
struct gameSettings {
    wave _waveSettings;
    ai _aiSettings;
    towerS _towerSettings;
    enemyS _enemySettings;
    tileSymbols _tileSymbols;
    gameRules _gameRules;
};

/**
 * @brief Config struct that load and parses the config file
 * @details The config file is a json file that contains the information about the game
 * @details The config file is loaded and parsed by the json library
 * @throws config_error if the value is not valid
 * @throws config_error if the column/s is/are missing
 * @throws config_error if there is duplicate tile symbols in the config file
 * @throws config_error if teh column has a wrong type
 */
struct config {
    /**
     * @brief load the config file
     * @param fileName path to the config file
     */
    void loadConfig(const char *fileName);

    /**
     * @brief check and parse the config file to sections
     * @param config json object that contains the config file
     */
    void checkAndParseConfig(const json &config);

    /**
     * @brief check and parse the game config
     * @param config json object that contains the config file
     */
    void checkAndParseGameConfig(const json &config);

    /**
     * @brief check and parse the tower config
     * @param config json object that contains the config file
     */
    void checkAndParseTowersConfig(const json &config);

    /**
     * @brief check and parse the enemy config
     * @param config json object that contains the config file
     */
    void checkAndParseEnemiesConfig(const json &config);

    gameSettings _gameSettings;
    std::vector<enemyConfig> _enemyConfig;
    std::vector<towerConfig> _towerConfig;
};


#endif //TOWER_DEFENSE_CONFIG_H
