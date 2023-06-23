//
// Created by prokoseb on 25.5.23.
//

#ifndef TOWER_DEFENSE_EFFECT_H
#define TOWER_DEFENSE_EFFECT_H

#include "../utils/properties.h"
#include <memory>

/**
 * @brief Abstract class that represents an effect
 * @details Effects are applied on enemies and change their stats
 * @param _duration Duration of the effect
 * @param _effectPower Power of the effect
 */
class effect {
public:
    /**
     * @brief Constructor for effect
     * @param duration Duration of the effect
     * @param effectPower Power of the effect
     */
    effect(int duration, int effectPower) : _duration(duration), _effectPower(effectPower) {}

    virtual ~effect() = default;

    /**
     * @brief Evaluates the effect and changes the stats of the enemy accordingly
     * @param prop Properties of the enemy
     */
    virtual void evaluate(properties &prop) = 0;

    /**
     * @brief Clones the effect
     * @return Shared pointer to the cloned effect
     */
    virtual std::shared_ptr<effect> clone() const = 0;

    /**
     * @brief Prints the effect to the output stream
     * @param out Output stream
     */
    virtual void print(std::ostream &out) const = 0;

    /**
     * @brief Resets the effect to the output stream
     * @param out Output stream
     */
    virtual void resetPrint(std::ostream &out) const = 0;

    /**
     * @brief Saves the effect to the buffer
     * @details Saves the effect to the buffer in the format:
     *     <effect type> <duration> <effect power>
     * @param buffer Buffer to save the effect to
     */
    virtual void saveEffect(std::ostream &buffer) const = 0;

    /**
     * @brief Updates the effect power
     * @param newEffectPower New effect power
     */
    void updateEffect(int newEffectPower) {
        _effectPower = newEffectPower;
    }

    /**
     * @return the duration of the effect
     */
    int getDuration() const { return _duration; }

protected:
    int _duration;
    int _effectPower;
};


#endif //TOWER_DEFENSE_EFFECT_H
