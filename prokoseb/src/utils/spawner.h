//
// Created by prokoseb on 4.6.23.
//

#ifndef TOWER_DEFENSE_SPAWNER_H
#define TOWER_DEFENSE_SPAWNER_H

#include "../objects/enemy.h"
#include "../objects/tower.h"
#include "../config/config.h"
#include "gameStats.h"

/**
 * @brief Spawns enemies according to the settings
 * @details first choose the type of enemy according to the settings
 * @details then give him smart or worse pathFinding algorithm depending on the settings
 * @details then apply wave boosts
 * @details then apply boost according to the power of towers
 */
struct spawner {
    /**
     * @brief Spawn the enemy
     * @param stats Game state stats
     * @param enemies Options of enemies to choose from
     * @param spawnPoint Where to spawn the enemy
     * @param towers Towers that are currently in the game
     * @return the enemy that was spawned
     */
    std::unique_ptr<enemy> spawnEnemy(const gameStats &stats, const std::vector<std::unique_ptr<enemy>> &enemies,
                                      const position &spawnPoint,
                                      const std::list<std::unique_ptr<tower>> &towers) const;

    /**
     * @brief Apply wave boosts to the enemy
     * @param wave Current wave
     * @param e Enemy to apply the boosts to
     */
    void applyWaveBoosts(int wave, enemy &e) const;

    /**
     * @var settings for the spawner
     */
    ai _settings;
};


#endif //TOWER_DEFENSE_SPAWNER_H
