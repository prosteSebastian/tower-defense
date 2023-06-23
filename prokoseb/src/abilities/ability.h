//
// Created by s on 26.5.23.
//

#ifndef TOWER_DEFENSE_ABILITY_H
#define TOWER_DEFENSE_ABILITY_H


#include <memory>
#include "../utils/properties.h"

/**
 * @brief Base class for abilities that modify the properties of the target
 * @details Abilities are used to permanently modify the properties of the target and it's used by the enemies
 */
class ability {
public:
    /**
     * @brief Constructor for the ability
     * @param range Range of the ability
     * @param cd    Cooldown of the ability
     * @var _remainingCooldown Remaining cooldown of the ability
     */
    ability(int range, int cd) : _range(range), _cooldown(cd), _remainingCooldown(cd) {}

    virtual ~ability() = default;

    /**
     * @brief Casts the ability on the target
     * @param caster Position of the caster
     * @param target Properties of the target
     */
    virtual void cast(const position &caster, properties &target) = 0;

    /**
     * @brief Clones the ability
     * @return Shared pointer to the cloned ability
     */
    virtual std::shared_ptr<ability> clone() const = 0;

    /**
     * @brief Prints the special effect of the ability to the output stream
     * @details This is used to print the special effect of the ability to the output stream using rang library
     * @param out Output stream
     */
    virtual void print(std::ostream &out) const = 0;

    /**
     * @brief Resets the special effect of the ability to the output stream
     * @param out
     */
    void resetPrint(std::ostream &out) const;

    /**
     * @brief Determines if the ability is on cooldown
     * @return True if the ability is on cooldown, false otherwise
     */
    bool isOnCooldown() const;

    /**
     * @brief Increments the remaining cooldown of the ability
     */
    void incrementCd();

protected:
    int _range;
    int _cooldown;
    int _remainingCooldown;
};


#endif //TOWER_DEFENSE_ABILITY_H
