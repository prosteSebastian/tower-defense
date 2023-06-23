//
// Created by prokoseb on 25.5.23.
//

#ifndef TOWER_DEFENSE_SLOW_H
#define TOWER_DEFENSE_SLOW_H

#include "effect.h"
#include "../../libs/rang.hpp"

/**
 * @brief Effect that slows down the enemy
 * @details decreases the speed of the enemy
 * @inherit effect
 * @see effect
 */
class slow : public effect {
public:
    slow(int duration, int slowAmmount) : effect(duration, slowAmmount) {}

    void evaluate(properties &prop) override;

    std::shared_ptr<effect> clone() const override;

    void print(std::ostream &out) const override;

    void resetPrint(std::ostream &out) const override;

    void saveEffect(std::ostream &buffer) const override;
};


#endif //TOWER_DEFENSE_SLOW_H
