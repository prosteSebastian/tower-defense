//
// Created by prokoseb on 3.6.23.
//

#include "fire.h"

int fire::getKillScore() const {
    return _killScore;
}

void fire::resetKillScore() {
    _killScore = 0;
}

bool fire::isReady() const {
    return _reloadTime == _remainingReloadTime;
}

void fire::addEffect(const std::shared_ptr<effect> &e) {
    _effects.emplace_back(e);
}

void fire::incrementReloadTime() {
    if (_remainingReloadTime < _reloadTime) {
        _remainingReloadTime++;
    }
}

void fire::upgradeEffect(int newEffectPower) {
    for (auto &e: _effects) {
        e->updateEffect(newEffectPower);
    }
}

void fire::saveFire(std::ostream &buffer) const {
    buffer << _remainingReloadTime;
}

void fire::setRemainingReload(int remainingReloadTime) {
    _remainingReloadTime = remainingReloadTime;
}


