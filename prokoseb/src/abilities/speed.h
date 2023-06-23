//
// Created by s on 26.5.23.
//

#ifndef TOWER_DEFENSE_SPEED_H
#define TOWER_DEFENSE_SPEED_H

#include "powerAbility.h"

/**
 * @brief Ability that permanently increases speed of all targets in range
 * @inherit powerAbility
 * @see powerAbility
 * @param speedBuff Amount of speed to add to the current speed to targets including themselves
 */
class speed : public powerAbility {
public:

    speed(int range, int cd, int speedBuff) : powerAbility(range, cd, speedBuff) {}

    void cast(const position &pos, properties &prop) override;

    void print(std::ostream &out) const override;

    std::shared_ptr<ability> clone() const override;
};

#endif //TOWER_DEFENSE_SPEED_H
