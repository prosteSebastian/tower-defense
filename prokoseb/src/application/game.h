//
// Created by s on 29.4.23.
//

#ifndef TOWER_DEFENSE_GAME_H
#define TOWER_DEFENSE_GAME_H

#include <iostream>
#include <csignal>
#include <algorithm>
#include <optional>
#include "../maps/tileMap.h"
#include "../maps/enemies.h"
#include "../maps/towers.h"
#include "../objects/tower.h"
#include "../objects/enemy.h"
#include "../passages/regular.h"
#include "../config/config.h"
#include "../utils/playerInput.h"
#include "../utils/stateOfGame.h"
#include "../utils/gameStats.h"
#include "../utils/loader.h"
#include "../utils/spawner.h"

/**
 * @brief Class that represents the game itself
 * @details Contains all the objects and methods that are needed to run the game
 * @see tileMap
 * @see enemies
 * @see towers
 * @var _playerInput struct that contains the player input menu options
 * @var _gMap tileMap that represents the map
 * @var _enemies enemies that are currently in the game
 * @var _towers towers that are currently in the game
 * @var _state state of the game
 * @var _config configuration of the game
 * @var _towers towers loaded from the config, they are sorted by price
 * @var _enemies enemies loaded from the config, they are sorted by reward for killing them
 * @var _gameStats stats of the game
 * @throws load_error when the values in load file are not valid
 * @throws std::runtime_error when we couldn't open the file
 * @throws std::runtime_error when we can not write to teh file
 */
class game {
public:
    /**
     * @brief Constructor of the game
     * @param fileName path to the map
     * @param conf configuration of the game
     */
    explicit game(const char *fileName, const config &conf);

    /**
     * @brief One round / tick of the game
     * @details In loop runs the game logic, there runs player input, enemies movement, towers attack
     * @details spawns enemies and checks if the game is over
     */
    void nextRound();

/**
     * @brief Checks if the game is over
     * @return true if the game is running, false if the game is over (won or lost)
     */
    bool isRunning() const;

    /**
     * @brief spawn enemies to the spawn points
     * @details calls the spawn method of the spawner to spawn enemies
     */
    void spawnEnemies();

    /**
     * @brief updates the enemies
     * @details calls the move method of the enemies and gains money for killing enemies and scores points for killing enemies
     */
    void updateEnemies();

    /**
     * @brief Command for towers to attack
     * @details calls the attack method of the towers
     */
    void towersCommandAttack();

    /**
     * @brief Draws the game
     * @param out stream to draw to
     */
    void draw(std::ostream &out) const;

    /**
     * @brief checks the state of base if any enemies reached it if so then remove them and decrease the base health
     */
    void checkBase();

    /**
     * @brief build type of tower on position in player input
     * @param p position to build the tower on
     */
    void buildTower(const position &p);

    /**
     * @brief menu for upgrading towers
     */
    void upgradeTowers();

    /**
     * @brief options for upgrading tower (dmg, range)
     * @param t tower to upgrade
     */
    void upgradeTower(const std::unique_ptr<tower> &t);

    /**
     * @brief menu for destroying towers
     * @param p position to destroy the tower on
     * @param costOfTower cost of the tower to destroy
     */
    void destroyTowerOnPos(const position &p, int costOfTower);

    /**
     * @brief show build towers and then destroy the chosen one
     */
    void showBuildTowers();

    /**
     * @brief set player input commands
     */
    void setPlayerInputCommands();

    /**
     * @brief player input menu
     */
    void playerInput();

    /**
     * @brief show available tower positions
     */
    void showAvailableTowerPos();

    /**
     * @brief increment all culldown based things in the game
     * @details increment ability of enemies, realod time of towers, duration of applied effects to enemies
     */
    void incrementCds();

    /**
     * @brief save the game
     * @details save the game constants, towers and enemies, call their method to save themselves to the buffer
     * @details saves the loaded game to the folder "loadGames"
     */
    void saveTheGame();

    /**
     * @brief Save the game constants to the buffer
     * @param buffer Buffer to save the game constants to
     * @details Call the save method of the gameStats
     */
    void saveGameConstants(std::ostream &buffer);

    /**
     * @brief Save the towers to the buffer
     * @details call save method of the towers
     * @param buffer Buffer to save the towers to
     */
    void saveTowers(std::ostream &buffer);

    /**
     * @brief Save the enemies to the buffer
     * @details call save method of the enemies
     * @param buffer Buffer to save the enemies to
     */
    void saveEnemies(std::ostream &buffer);

    /**
     * @brief load the game from the file
     * @details load the game constants, towers and enemies, call their method to load themselves from the buffer
     * @details loads the saved game from the folder "loadGames"
     * @param file file to load the game from
     */
    void loadGame(std::ifstream &file);

    /**
     * @brief get tilemap, this is used for testing
     * @return
     */
    const tileMap &getMap() const { return gMap; }

private:
    struct playerInput _playerInput;

    tileMap gMap;

    enemies enemyLocation;

    towers towerLocation;

    stateOfGame _state = stateOfGame::running;

    config _config;

    std::vector<std::unique_ptr<tower>> _towers;

    std::vector<std::unique_ptr<enemy>> _enemies;

    gameStats _gameStats;

    loader _loader;

    spawner _spawner;
};


#endif //TOWER_DEFENSE_GAME_H
