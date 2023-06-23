//
// Created by s on 9.5.23.
//

#ifndef TOWER_DEFENSE_MENU_H
#define TOWER_DEFENSE_MENU_H

#include <iostream>
#include <climits>
#include "menuCommand.h"

/**
 * @brief Represents a menu in game
 * @throws std::runtime_error if eof is reached
 * @throws std::runtime_error if invalid input is entered
 */
class menu {
public:
    /**
     * @brief Creates a menu
     * @param title title of the menu
     */
    explicit menu(std::string title) : title(std::move(title)) {}

    /**
     * @brief Shows the commands of the menu
     */
    void showOptions() const;

    /**
     * @brief Runs the commands of the menu
     */
    void runCommands() const;

    /**
     * @brief Adds a command to the menu
     * @param command command to be added
     */
    void addCommand(const menuCommand &command);

private:
    std::string title;
    std::vector<menuCommand> _commands;
};


#endif //TOWER_DEFENSE_MENU_H
