//
// Created by s on 9.5.23.
//

#ifndef TOWER_DEFENSE_MENUCOMMAND_H
#define TOWER_DEFENSE_MENUCOMMAND_H

#include<string>
#include <utility>
#include<vector>
#include <functional>
/*
 * silne inspirovano: https://gitlab.fit.cvut.cz/matouj10/pa2-2022-lab/-/tree/master/sw-tips/12-simple-menu
 */
/**
 * @brief Represents a menu command in menu
 */
class menuCommand {
public:
    /**
     * @brief Creates a menu command
     * @param name name of the command
     * @param action action to be performed when command is executed
     */
    menuCommand(std::string name, std::function<void()> action) : _name(std::move(name)), _action(std::move(action)) {}

    /**
     *
     * @return returns name of the command
     */
    std::string getName() const { return _name; }

    /**
     * @brief Executes the command
     */
    void action() const { _action(); }

private:
    std::string _name;
    std::function<void()> _action;
};


#endif //TOWER_DEFENSE_MENUCOMMAND_H
