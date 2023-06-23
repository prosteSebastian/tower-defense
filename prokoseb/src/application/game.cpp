//
// Created by s on 29.4.23.
//

#include "game.h"
#include "../utils/gameConstants.cpp"

#include "../passages/bfs.h"

#include "../exceptions/load_error.h"

#include <ctime>

game::game(const char *fileName, const config &conf) : gMap(fileName, conf._gameSettings._tileSymbols,
                                                            conf._gameSettings._gameRules), _config(std::move(conf)) {
    enemyLocation.setBase(gMap._basePosition);
    _gameStats._money = _config._gameSettings._gameRules._money;
    _gameStats._baseHp = _config._gameSettings._gameRules._baseHp;
    _gameStats._fileName = fileName;
    setPlayerInputCommands();
    _spawner._settings = _config._gameSettings._aiSettings;
    _loader.loadTowers(_config._towerConfig, _towers);
    _loader.loadEnemies(_config._enemyConfig, _enemies);
}

void game::nextRound() {
    if ((_gameStats._round % _config._gameSettings._waveSettings._playerInput == 0)) {
        playerInput();
    }
    if ((_gameStats._round % _config._gameSettings._waveSettings._spawnFrequency == 0)
        && (_gameStats._wave < _config._gameSettings._waveSettings._winOnWave)) {
        spawnEnemies();
    }

    towersCommandAttack();

    updateEnemies();

    checkBase();

    usleep(400000);
    _gameStats._round++;
    if (_gameStats._round % _config._gameSettings._waveSettings._newWave == 0) {
        _gameStats._wave++;
        _gameStats._money += _config._gameSettings._waveSettings._moneyPerWave;
        _gameStats._score += _config._gameSettings._waveSettings._scorePerWave;
        _gameStats._round = 0;
    }
    if (_gameStats._wave >= _config._gameSettings._waveSettings._winOnWave && enemyLocation._enemyMap.empty()) {
        _state = stateOfGame::won;
    }
    draw(std::cout);
    incrementCds();
}


void game::draw(std::ostream &out) const {
    out << CLR_SCR;
    for (const auto &row: gMap._objectMap) {
        for (const auto &object: row) {
            position pos = object->getPosition();
            if (enemyLocation.isEnemy(pos)) {
                enemyLocation.print(out, pos);
            } else if (towerLocation.isTower(pos)) {
                towerLocation.print(out, pos);
            } else {
                object->print(out);
            }
        }
        out << std::endl;
    }
    if (_state == stateOfGame::lost) {
        out << rang::fg::red << "GAME OVER" << rang::fg::reset << std::endl;
        usleep(5000000);
    } else if (_state == stateOfGame::won) {
        out << rang::fg::green << "YOU WON" << rang::fg::reset << std::endl;
        usleep(3000000);
    } else if (_state == stateOfGame::finished) {
        out << rang::fg::red << "Quiting the game" << rang::fg::reset << std::endl;
        usleep(30000);
    } else {
        out << rang::fg::green << "Base HP: " << _gameStats._baseHp << rang::fg::reset << std::endl;
    }
    out << rang::fg::yellow << "Money: " << _gameStats._money << "$" << rang::fg::reset << std::endl;
    out << rang::fg::magenta << "Wave: " << _gameStats._wave << rang::fg::reset << std::endl;
    out << rang::fg::blue << "Score: " << _gameStats._score << rang::fg::reset << std::endl;
}

bool game::isRunning() const {
    return _state == stateOfGame::running;
}


void game::spawnEnemies() {
    for (const auto &pos: gMap._enemySpawnPoints) {
        std::unique_ptr<enemy> e = _spawner.spawnEnemy(_gameStats, _enemies,
                                                       pos, towerLocation._towers);

        e->generatePath(gMap);

        enemyLocation.addEnemy(std::move(e));
    }
}

void game::checkBase() {
    enemyLocation._enemyMap.remove_if([&](const std::unique_ptr<enemy> &e) {
        if (e->getPosition() == gMap._basePosition) {
            _gameStats._baseHp -= e->getStats()._damage;
            return true;
        }
        return false;
    });

    if (_gameStats._baseHp <= 0) {
        _state = stateOfGame::lost;
    }

}

void game::updateEnemies() {
    enemyLocation.updateEnemies();
    _gameStats._money += enemyLocation._gainedMoney;
    _gameStats._score += enemyLocation._gainedMoney / _config._gameSettings._enemySettings._deathScoreDivision;
    enemyLocation.resetGainedMoney();
}

void game::towersCommandAttack() {

    towerLocation.attack(enemyLocation);
    _gameStats._score += towerLocation._killScore / _config._gameSettings._towerSettings._killRewardDivision;
    _gameStats._money += towerLocation._killScore;
    towerLocation.resetKillScore();
}

void game::incrementCds() {
    enemyLocation.incrementAbilityCds();
    enemyLocation.validateEffect();
    towerLocation.reloadTowers();
}

void game::playerInput() {
    draw(std::cout);
    _playerInput.currentMenu = &_playerInput._menu;
    while (std::cin && _playerInput.currentMenu) {
        _playerInput.currentMenu->showOptions();
        _playerInput.currentMenu->runCommands();
        draw(std::cout);
    }
}

void game::showAvailableTowerPos() {
    menu towerMenu("Available tower positions [Y,X]:");
    for (const auto &[pos, isAvailable]: gMap._towerPlacementPoints) {
        if (isAvailable) {
            towerMenu.addCommand(menuCommand("[" + std::to_string(pos.y) + ", " + std::to_string(pos.x) + "]", [&]() {
                buildTower(pos);
            }));
        }
    }
    towerMenu.addCommand(menuCommand("Back", [&]() { playerInput(); }));
    towerMenu.showOptions();
    towerMenu.runCommands();
}

void game::buildTower(const position &p) {
    menu towerMenu("Choose type of tower - (cost)");
    bool _successInput = true;

    for (const auto &tower: _towers) {
        towerMenu.addCommand(
                menuCommand(tower->getStats()._name + " - (" + std::to_string(tower->getStats()._cost) + ")",
                            [&]() { towerLocation.buildTower(_gameStats._money, tower, p, _successInput); }));
    }
    towerMenu.addCommand(menuCommand("Back", [&]() { showAvailableTowerPos(); }));
    towerMenu.showOptions();
    towerMenu.runCommands();
    if (_successInput) {
        gMap.placedTower(p, false);
    } else {
        std::cout << rang::fg::red << "You don't have enough money" << rang::fg::reset << std::endl;
        usleep(1000000);
    }

}

void game::upgradeTowers() {
    menu upgradeMenu("Select which tower you want to upgrade [Y,X]:");
    for (const auto &tower: towerLocation._towers) {
        upgradeMenu.addCommand(menuCommand("[" + std::to_string(tower->getStats()._position.y) + ", " +
                                           std::to_string(tower->getStats()._position.x) + "]",
                                           [&]() { upgradeTower(tower); }));
    }
    upgradeMenu.addCommand(menuCommand("Back", [&]() { playerInput(); }));
    upgradeMenu.showOptions();
    upgradeMenu.runCommands();
}

void game::upgradeTower(const std::unique_ptr<tower> &t) {
    bool _successInput = true;
    int costDmgIncrease =
            (t->getStats()._cost * t->getStats()._level) * (_config._gameSettings._towerSettings._costDmgIncrease - 1);
    int costRangeIncrease = (t->getStats()._cost * t->getStats()._level) *
                            (_config._gameSettings._towerSettings._costRangeIncrease - 1);
    menu upgrade("What do you want to upgrade? - (cost)");
    upgrade.addCommand(menuCommand("Damage - (" + std::to_string(costDmgIncrease) + ")", [&]() {
        t->upgradeDamage(_gameStats._money, t, _successInput,
                         _config._gameSettings._towerSettings._dmgIncrease,
                         _config._gameSettings._towerSettings._costDmgIncrease);
    }));
    upgrade.addCommand(menuCommand("Range - (" + std::to_string(costRangeIncrease) + ")", [&]() {
        t->upgradeRange(_gameStats._money, _successInput,
                        _config._gameSettings._towerSettings._rangeIncrease,
                        _config._gameSettings._towerSettings._costRangeIncrease);
    }));
    upgrade.addCommand(menuCommand("Back", [&]() { upgradeTowers(); }));
    upgrade.showOptions();
    upgrade.runCommands();
    if (!_successInput) {
        std::cout << rang::fg::red << "You don't have enough money" << rang::fg::reset << std::endl;
        usleep(1000000);
    }
}

void game::showBuildTowers() {
    menu towers("Show your towers:");
    for (const auto &tower: towerLocation._towers) {
        towers.addCommand(menuCommand("[" + std::to_string(tower->getStats()._position.y) + ", " +
                                      std::to_string(tower->getStats()._position.x) + "]",
                                      [&]() {
                                          destroyTowerOnPos(tower->getStats()._position, tower->getStats()._cost);
                                      }));
    }
    towers.addCommand(menuCommand("Back", {[]() {}}));
    towers.showOptions();
    towers.runCommands();
}

void game::destroyTowerOnPos(const position &p, int costOfTower) {
    towerLocation._towers.remove_if([&](const std::unique_ptr<tower> &t) {
        if (t->getStats()._position == p) {
            _gameStats._money += costOfTower / _config._gameSettings._towerSettings._sellValueDivision;
            gMap.placedTower(p, true);
            return true;
        } else {
            return false;
        }
    });
}

void game::setPlayerInputCommands() {
    _playerInput._menu.addCommand(menuCommand("Build", [&]() { _playerInput.currentMenu = &_playerInput._buildMenu; }));
    _playerInput._menu.addCommand(
            menuCommand("Upgrade", [&]() { _playerInput.currentMenu = &_playerInput._upgradeMenu; }));
    _playerInput._menu.addCommand(menuCommand("Sell", [&]() { _playerInput.currentMenu = &_playerInput._sellMenu; }));
    _playerInput._menu.addCommand(
            menuCommand("Save the game", [&]() { _playerInput.currentMenu = &_playerInput._saveMenu; }));
    _playerInput._menu.addCommand(menuCommand("End your turn", [&]() { _playerInput.currentMenu = nullptr; }));
    _playerInput._menu.addCommand(
            menuCommand("Quit the game", [&]() { _playerInput.currentMenu = &_playerInput._exitMenu; }));

    _playerInput._buildMenu.addCommand(
            menuCommand("Show available tower positions", [&]() { showAvailableTowerPos(); }));
    _playerInput._buildMenu.addCommand(menuCommand("Back", [&]() { _playerInput.currentMenu = &_playerInput._menu; }));

    _playerInput._upgradeMenu.addCommand(menuCommand("Your towers:", [&]() { upgradeTowers(); }));
    _playerInput._upgradeMenu.addCommand(
            menuCommand("Back", [&]() { _playerInput.currentMenu = &_playerInput._menu; }));

    _playerInput._sellMenu.addCommand(menuCommand("Your towers:", [&]() { showBuildTowers(); }));
    _playerInput._sellMenu.addCommand(menuCommand("Back", [&]() { _playerInput.currentMenu = &_playerInput._menu; }));

    _playerInput._saveMenu.addCommand(menuCommand("Are you sure, you want to save the current game?", [&]() {
        saveTheGame();
        _playerInput.currentMenu = &_playerInput._menu;
    }));
    _playerInput._saveMenu.addCommand(menuCommand("No", [&]() { _playerInput.currentMenu = &_playerInput._menu; }));

    _playerInput._exitMenu.addCommand(menuCommand("Are you sure, you want to exit the game?", [&]() {
        _playerInput.currentMenu = nullptr;
        _state = stateOfGame::finished;
    }));
    _playerInput._exitMenu.addCommand(menuCommand("No", [&]() { _playerInput.currentMenu = &_playerInput._menu; }));
}
//---------------------------

void game::saveTheGame() {
    std::cout << "Saving the game..." << std::endl;
    usleep(1000000);

    std::ostringstream buffer;
    buffer << _gameStats._fileName << std::endl;

    saveGameConstants(buffer);

    saveTowers(buffer);
    buffer << std::endl;
    saveEnemies(buffer);

    std::time_t t = std::time(nullptr);
    char title[100];
    std::strftime(title, sizeof(title), "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    std::string path = "loadGames/" + std::string(title) + ".txt";
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Couldn't open the file");
    }
    if (!(file << buffer.str())) {
        throw std::runtime_error("Couldn't write to the file");
    }
    std::cout << rang::fg::green << "Game saved" << rang::fg::reset << std::endl;
    usleep(1000000);
}

void game::saveGameConstants(std::ostream &buffer) {
    _gameStats.save(buffer);
}

void game::saveTowers(std::ostream &buffer) {
    for (const auto &tower: towerLocation._towers) {
        tower->saveTower(buffer);
        buffer << std::endl;
    }
}

void game::saveEnemies(std::ostream &buffer) {
    for (const auto &enemy: enemyLocation._enemyMap) {
        enemy->save(buffer);
        buffer << std::endl;
    }
}

void game::loadGame(std::ifstream &file) {
    _loader.loadTheGame(file, _gameStats, _towers, towerLocation._towers, _enemies, enemyLocation._enemyMap);

    for (const auto &tower: towerLocation._towers) {
        gMap.placedTower(tower->getStats()._position, false);
    }

    for (const auto &enemy: enemyLocation._enemyMap) {
        enemy->generatePath(gMap);
    }

}