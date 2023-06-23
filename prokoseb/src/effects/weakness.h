//
// Created by s on 26.5.23.
//

#ifndef TOWER_DEFENSE_WEAKNESS_H
#define TOWER_DEFENSE_WEAKNESS_H

#include "effect.h"

/**
 * @brief Effect that weakens the enemy
 * @details decreases the damage of the enemy
 * @inherit effect
 * @see effect
 */
class weakness : public effect {
public:
    weakness(int duration, int weaknessPower) : effect(duration, weaknessPower) {}

    void evaluate(properties &prop) override;

    std::shared_ptr<effect> clone() const override;

    void print(std::ostream &out) const override;

    void resetPrint(std::ostream &out) const override;

    void saveEffect(std::ostream &buffer) const override;
};


#endif //TOWER_DEFENSE_WEAKNESS_H
