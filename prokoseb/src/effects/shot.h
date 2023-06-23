//
// Created by s on 27.5.23.
//

#ifndef TOWER_DEFENSE_SHOT_H
#define TOWER_DEFENSE_SHOT_H

#include "effect.h"

/**
 * @brief "Clasical" shot effect
 * @details decreases the health of the enemy
 * @inherit effect
 * @see effect
 */
class shot : public effect {
public:
    shot(int duration, int ammount) : effect(duration, ammount) {}

    void evaluate(properties &prop) override;

    std::shared_ptr<effect> clone() const override { return std::make_shared<shot>(*this); }

    void print(std::ostream &out) const override;

    void resetPrint(std::ostream &out) const override;

    void saveEffect(std::ostream &buffer) const override;
};


#endif //TOWER_DEFENSE_SHOT_H
