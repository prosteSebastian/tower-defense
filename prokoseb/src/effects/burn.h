//
// Created by prokoseb on 25.5.23.
//

#ifndef TOWER_DEFENSE_BURN_H
#define TOWER_DEFENSE_BURN_H

#include "effect.h"
#include "../../libs/rang.hpp"

/**
 * @brief Effect that deals damage over time
 * @details Effect that deals damage over time
 * @inherit effect
 * @see effect
 */
class burn : public effect {
public:
    burn(int duration, int burnDmg) : effect(duration, burnDmg) {}

    void evaluate(properties &prop) override;

    std::shared_ptr<effect> clone() const;

    void print(std::ostream &out) const override;

    void resetPrint(std::ostream &out) const override;

    void saveEffect(std::ostream &buffer) const override;
};

#endif //TOWER_DEFENSE_BURN_H
