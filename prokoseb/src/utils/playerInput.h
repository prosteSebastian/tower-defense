//
// Created by s on 28.5.23.
//

#ifndef TOWER_DEFENSE_PLAYERINPUT_H
#define TOWER_DEFENSE_PLAYERINPUT_H

#include "../menu/menu.h"

/**
 * @brief Struct for player input
 * @details _menu Being the main menu for player input etc.
 */
struct playerInput {
    playerInput() : currentMenu(&_menu), _menu("Main menu"), _buildMenu("Build menu"),
                    _upgradeMenu("Upgrade menu"), _sellMenu("Sell menu"), _saveMenu("Save menu"),
                    _exitMenu("Exit menu") {}

    menu *currentMenu = nullptr;
    menu _menu;
    menu _buildMenu;
    menu _upgradeMenu;
    menu _sellMenu;
    menu _saveMenu;
    menu _exitMenu;
};


#endif //TOWER_DEFENSE_PLAYERINPUT_H
