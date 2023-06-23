//
// Created by s on 27.5.23.
//

#ifndef TOWER_DEFENSE_INVINCIBILITY_H
#define TOWER_DEFENSE_INVINCIBILITY_H

#include "ability.h"

/**
 * @brief Ability that makes all targets in range invincible
 * @details Invincibility is added to the targets properties as flag
 * @inherit ability
 * @see ability
 */
class invincibility : public ability {
public:
    invincibility(int range, int cd) : ability(range, cd) {}

    void cast(const position &pos, properties &prop) override;

    std::shared_ptr<ability> clone() const override;

    void print(std::ostream &out) const override;
};


#endif //TOWER_DEFENSE_INVINCIBILITY_H
