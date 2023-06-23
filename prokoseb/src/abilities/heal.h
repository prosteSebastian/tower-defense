//
// Created by s on 26.5.23.
//

#ifndef TOWER_DEFENSE_HEAL_H
#define TOWER_DEFENSE_HEAL_H

#include "powerAbility.h"

/**
 * @brief Ability that heals all targets in range
 * @inherit powerAbility
 * @see powerAbility
 * @param healAmount Amount of health to add to the current health to targets including themselves
 */

class heal : public powerAbility {
public:
    heal(int range, int cd, int healAmount) : powerAbility(range, cd, healAmount) {}

    void cast(const position &from, properties &to) override;

    std::shared_ptr<ability> clone() const override;

    void print(std::ostream &out) const override;
};


#endif //TOWER_DEFENSE_HEAL_H
