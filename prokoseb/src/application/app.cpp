//
// Created by s on 9.5.23.
//

#include "app.h"
#include <filesystem>
#include "../utils/gameConstants.cpp"


app::app(config con) : mainMenu("Main menu:"), newGameMenu("Do you really want to start a new game?"),
                       loadGameMenu("Do you really want to load a saved game?"), currentMenu(&mainMenu), _config(con) {
    mainMenu.addCommand(menuCommand("Start a new game", [&]() { currentMenu = &newGameMenu; }));
    mainMenu.addCommand(menuCommand("Load game", [&]() { currentMenu = &loadGameMenu; }));
    mainMenu.addCommand(menuCommand("Exit the program", [&]() { currentMenu = nullptr; }));

    newGameMenu.addCommand(menuCommand("YES!", [&]() { newGame(); }));
    newGameMenu.addCommand(menuCommand("NO, I want to return to the main menu.", [&]() { currentMenu = &mainMenu; }));

    loadGameMenu.addCommand(menuCommand("YES!", [&]() { loadGame(); }));
    loadGameMenu.addCommand(menuCommand("NO, I want to return to the main menu.", [&]() { currentMenu = &mainMenu; }));
}

void app::run() {
    while (currentMenu && std::cin) {
        std::cout << TITLE << std::endl;
        currentMenu->showOptions();
        currentMenu->runCommands();
    }
}


void app::newGame() {
    menu chooseMapMenu("Choose the map:");
    for (const auto &entry: std::filesystem::directory_iterator("examples/")) {
        chooseMapMenu.addCommand(menuCommand(entry.path().filename().string(), [=]() {
            printMapandStartGame(entry.path().c_str());
        }));
    }
    chooseMapMenu.addCommand(menuCommand("Back", [&]() { currentMenu = &mainMenu; }));
    chooseMapMenu.showOptions();
    chooseMapMenu.runCommands();

}

void app::loadGame() {
    menu chooseGameMenu("Choose saved game:");
    for (const auto &entry: std::filesystem::directory_iterator("loadGames/")) {
        chooseGameMenu.addCommand(menuCommand(entry.path().filename().string(), [=]() {
            loadGameFromSave(entry.path().c_str());
        }));
    }
    chooseGameMenu.addCommand(menuCommand("Back", [&]() { currentMenu = &mainMenu; }));
    chooseGameMenu.showOptions();
    chooseGameMenu.runCommands();
}

void app::printMapandStartGame(const char *path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("File not found");
    }
    if (!std::filesystem::is_regular_file(path)) {
        throw std::runtime_error("File is not regular file");
    }
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    menu startGameMenu("Are you sure about starting a new game with this map?");
    startGameMenu.addCommand(menuCommand("YES 100%", [&]() {
        startGame(path);
        currentMenu = &mainMenu;
    }));
    startGameMenu.addCommand(menuCommand("NO :(", [&]() { newGame(); }));
    startGameMenu.showOptions();
    startGameMenu.runCommands();

}

void app::startGame(const char *path) {
    game g(path, _config);
    while (g.isRunning()) {
        if (std::cin.bad()) {
            throw std::runtime_error("There was an error while reading input.");
        }
        g.nextRound();
    }
}

void app::loadGameFromSave(const char *path) {
    std::ifstream file(path);
    if (!std::filesystem::is_regular_file(path)) {
        throw std::runtime_error("File is not regular file");
    }
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("File does not exist");
    }
    std::string map;
    std::getline(file, map);
    if (!std::filesystem::exists(map)) {
        throw std::runtime_error("Map file does not exist");
    }

    game g(map.c_str(), _config);
    g.loadGame(file);

    while (g.isRunning()) {
        if (std::cin.bad()) {
            throw std::runtime_error("There was an error while reading an input.");
        }
        g.nextRound();
    }

}
