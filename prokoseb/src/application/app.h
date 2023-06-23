//
// Created by s on 9.5.23.
//

#ifndef TOWER_DEFENSE_APP_H
#define TOWER_DEFENSE_APP_H

#include "../menu/menu.h"
#include "game.h"
#include "../config/config.h"

/**
 * @brief Main application class
 * @details Handles the main menu and the game
 * @see menu
 */
class app {
public:
    app(config con);

    /**
     * @brief Runs the application
     * @details in loop runs the menu
     */
    void run();

    /**
     * @brief Menu for statring a loaded gam
     */
    void loadGame();

    /**
     * @brief Menu for starting a new game
     */
    void newGame();

    /**
     * @brief Prints the map and starts the game
     * @param path path to the map
     * @throws std::runtime_error if the map file is not found
     * @throws std::runtime_error if the map is not a regular file
     */
    void printMapandStartGame(const char *path);

    /**
     * @brief runs the game loop from chosen map
     * @param path path to the map
     * @throws std::runtime_error when there was an error while reading an input
     */
    void startGame(const char *path);

    /**
     * @brief loads the game from saved file
     * @throws std::runtime_error if the map is not readable
     * @throws std::runtime_error when there was an error in input
     * @throws std::runtime_error if the map does not exists
     * @throws std::runtime_error if the file does not exists
     */
    void loadGameFromSave(const char *path);

private:
    menu mainMenu;
    menu newGameMenu;
    menu loadGameMenu;
    menu *currentMenu;

    config _config;
};


#endif //TOWER_DEFENSE_APP_H
