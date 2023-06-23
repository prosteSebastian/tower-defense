//
// Created by prokoseb on 4.6.23.
//

#include "spawner.h"
#include "../passages/regular.h"
#include "../passages/bfs.h"

std::unique_ptr<enemy> spawner::spawnEnemy(const gameStats &stats, const std::vector<std::unique_ptr<enemy>> &enemies,
                                           const position &spawnPoint,
                                           const std::list<std::unique_ptr<tower>> &towers) const {
    int enemyIndex = stats._wave % enemies.size();
    std::unique_ptr<enemy> e;
    if (stats._wave <= _settings.bfsPathLimit) {

        e = std::make_unique<enemy>(spawnPoint.x, spawnPoint.y, enemies[enemyIndex]->getProperties()._stats._symbol,
                                    enemies[enemyIndex]->getProperties()._stats._health,
                                    enemies[enemyIndex]->getProperties()._stats._speed,
                                    enemies[enemyIndex]->getProperties()._stats._reward,
                                    enemies[enemyIndex]->getProperties()._stats._damage,
                                    enemies[enemyIndex]->getProperties()._stats._name);
        for (const auto &ab: enemies[enemyIndex]->getAbilities()) {
            e->addAbility(ab->clone());
        }
        e->setPassage(std::make_unique<regular>());
        e->addFlag(flags::dumb);
    } else {
        e = std::make_unique<enemy>(spawnPoint.x, spawnPoint.y, enemies[enemyIndex]->getProperties()._stats._symbol,
                                    enemies[enemyIndex]->getProperties()._stats._health,
                                    enemies[enemyIndex]->getProperties()._stats._speed,
                                    enemies[enemyIndex]->getProperties()._stats._reward,
                                    enemies[enemyIndex]->getProperties()._stats._damage,
                                    enemies[enemyIndex]->getProperties()._stats._name);
        for (const auto &ab: enemies[enemyIndex]->getAbilities()) {
            e->addAbility(ab->clone());
        }
        e->setPassage(std::make_unique<bfs>());
        e->addFlag(flags::bfs);
    }


    applyWaveBoosts(stats._wave, *e);
    int powerOfTowers = 0;
    for (const auto &tower: towers) {
        int power = tower->getStats()._damage * tower->getStats()._level;
        powerOfTowers += power;
    }
    if (powerOfTowers > _settings.towerPowerConstant) {
        int boost = powerOfTowers / _settings.towerPowerConstant;
        properties props = e->getProperties();
        props._stats._health += boost;
        props._stats._speed += boost;
        props._stats._damage += boost;
        e->setProperties(props);
    }
    e->addFlag(flags::canBeAttacked);
    return e;
}

void spawner::applyWaveBoosts(int wave, enemy &e) const {

    int hpBoost = wave * _settings.hpBoost;
    int speedBoost = wave / _settings.speedBoost;
    int damageBoost = wave * _settings.dmgBoost;
    properties props = e.getProperties();
    props._stats._health += hpBoost;
    props._stats._speed += speedBoost;
    props._stats._damage += damageBoost;
    e.setProperties(props);

}
