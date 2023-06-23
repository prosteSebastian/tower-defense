//
// Created by s on 9.5.23.
//

#include "menu.h"
#include <csignal>
#include "../utils/gameConstants.cpp"
#include "../../libs/rang.hpp"


void menu::addCommand(const menuCommand &command) {
    _commands.push_back(command);
}


void menu::showOptions() const {
    std::cout << title << std::endl;
    for (size_t i = 0; i < _commands.size(); i++) {
        std::cout << "[" << i + 1 << "] " << _commands[i].getName() << std::endl;
    }
}

void menu::runCommands() const {
    int choice = 0;
    while (std::cin && !choice && !_commands.empty()) {
        std::cout << "Enter your choice: ";
        if (!(std::cin >> choice) || choice > (int) _commands.size() || choice < 0) {
            if (std::cin.bad()) {
                throw std::runtime_error("Invalid input.");
            }
            if (std::cin.eof()) {
                throw std::runtime_error("EOF");
            }
            choice = 0;
            std::cout << rang::fg::red << "Invalid choice." << rang::fg::reset << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            showOptions();
        }
    }

    if (!choice) {
        return;
    }
    _commands[choice - 1].action();
    std::cout << CLR_SCR;
}
