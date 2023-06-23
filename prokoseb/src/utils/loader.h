//
// Created by prokoseb on 4.6.23.
//

#ifndef TOWER_DEFENSE_LOADER_H
#define TOWER_DEFENSE_LOADER_H

#include "../config/config.h"
#include "../objects/tower.h"
#include "../objects/enemy.h"
#include "gameStats.h"
#include<optional>

/**
 * @brief struct that loads the object from the game and from teh saved game
 */
struct loader {
    /**
     * @brief Loads towers from config and add them to the vector of known towers
     * @param tg vector of attributes of towers parsed from the config
     * @param towers vector of towers that will be saved to
     */
    void loadTowers(const std::vector<towerConfig> &tg, std::vector<std::unique_ptr<tower>> &towers) const;

    /**
     * @brief Add effect to the tower
     * @param t tower that will be affected
     * @param effect effect that will be added
     * @param tow tower config that will be used to add the effect
     * @throws load_error there is a wrong value in the config
     */
    void addEffectToTower(tower &t, const effectConfig &effect, const towerConfig &tow) const;

    /**
     * @brief load the enemies from the config and add them to the vector of known enemies
     * @param eg vector of attributes of enemies parsed from the config
     * @param enemies vector of enemies that will be saved to
     */
    void loadEnemies(const std::vector<enemyConfig> &eg, std::vector<std::unique_ptr<enemy>> &enemies) const;

    /**
     * @brief load the game from saved file and parse it to the game
     * @param file file to load the game from
     * @param stats constants of the game
     * @param towers vector of known towers
     * @param listTowers list of placed towers
     * @param enemies vector of known enemies
     * @param enemyMap list of enemies on the map
     * @throws load_error there is a wrong value in the config
     */
    void loadTheGame(std::ifstream &file, gameStats &stats, const std::vector<std::unique_ptr<tower>> &towers,
                     std::list<std::unique_ptr<tower>> &listTowers, const std::vector<std::unique_ptr<enemy>> &enemies,
                     std::list<std::unique_ptr<enemy>> &enemyMap);

    /**
     * @brief load the game constants from the file
     * @param file file to load the game from
     * @param stats constants of the game
     * @throws load_error there is a wrong value in the config
     */
    void loadGameConstants(std::ifstream &file, gameStats &stats);

    /**
     * @brief load the towers from the file and saved it to the listTowers
     * @param file file to load the game from
     * @param towers vector of known towers
     * @param listTowers list of placed towers
     * @throws load_error there is a wrong value in the config
     */
    void loadSavedTowers(std::ifstream &file, const std::vector<std::unique_ptr<tower>> &towers,
                         std::list<std::unique_ptr<tower>> &listTowers);

    /**
     * @beirf load the enemies from the file and saved it to the enemyMap
     * @param file file to load the game from
     * @param enemies vector of known enemies
     * @param enemyMap list of enemies on the map
     * @throws load_error there is a wrong value in the config
     */
    void loadSavedEnemies(std::ifstream &file, const std::vector<std::unique_ptr<enemy>> &enemies,
                          std::list<std::unique_ptr<enemy>> &enemyMap);

    /**
     * @brief parse the int from the file
     * @param file file to load the game from
     * @return parsed int
     */
    std::optional<unsigned int> readInt(std::ifstream &file);
};


#endif //TOWER_DEFENSE_LOADER_H
