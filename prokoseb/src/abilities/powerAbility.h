//
// Created by prokoseb on 3.6.23.
//

#ifndef TOWER_DEFENSE_POWERABILITY_H
#define TOWER_DEFENSE_POWERABILITY_H

#include "ability.h"

/**
 * @brief Base class for abilities that their effect depends on power
 * @inherit ability
 * @see ability
 * @param _abilityPower Power of the ability
 */
class powerAbility : public ability {
public:
    powerAbility(int range, int cd, int power) : ability(range, cd), _abilityPower(power) {}

protected:
    int _abilityPower;
};


#endif //TOWER_DEFENSE_POWERABILITY_H
