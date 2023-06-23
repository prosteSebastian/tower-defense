#include "../src/config/config.h"
#include "../src/application/app.h"
#include "../src/passages/bfs.h"
#include <iostream>
#include <cassert>
#include <filesystem>

int main() {
    std::cout << rang::fg::blue << "TESTING CONFIGS" << rang::fg::reset << std::endl;
    config _config;
    for (const auto &entry: std::filesystem::directory_iterator("testing/invalidConfigFiles/")) {
        std::cout << "For: " << entry.path() << std::endl;
        try {
            _config.loadConfig(entry.path().c_str());
            assert(false);
        }
        catch (std::exception &e) {
            std::cout << rang::fg::red << e.what() << rang::fg::reset << std::endl;
        }
        catch (...) {
            assert(false);
        }
        std::cout << std::endl;
    }


    config validConfig;
    validConfig.loadConfig("configFiles/config.json");

    std::cout << rang::fg::yellow << "TESTING MAPS" << rang::fg::reset << std::endl;
    for (const auto &entry: std::filesystem::directory_iterator("testing/invalidMaps/")) {
        std::cout << "Testing map: " << entry.path() << std::endl;
        try {
            game g(entry.path().c_str(), validConfig);
            enemy e(g.getMap()._enemySpawnPoints[0].x, g.getMap()._enemySpawnPoints[0].y, 0, 0, 0, 0, 0, "pepa");
            e.setPassage(std::make_unique<bfs>());
            e.generatePath(g.getMap());
            assert(false);
        }
        catch (std::exception &e) {
            std::cout << rang::fg::red << e.what() << rang::fg::reset << std::endl;
        }
        catch (...) {
            assert(false);
        }
        std::cout << std::endl;
    }

    std::cout << rang::fg::magenta << "TESTING LOADED GAMES" << rang::fg::reset << std::endl;
    app _app(validConfig);
    for (const auto &entry: std::filesystem::directory_iterator("testing/invalidLoadedGames/")) {
        std::cout << entry.path() << std::endl;
        try {
            _app.loadGameFromSave(entry.path().c_str());
            assert(false);
        }
        catch (std::exception &e) {
            std::cout << rang::fg::red << e.what() << rang::fg::reset << std::endl;
        }
        catch (...) {
            assert(false);
        }
        std::cout << std::endl;
    }

    return 0;
}