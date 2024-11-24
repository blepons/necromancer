#include "hero.hpp"
#include <algorithm>
#include <cmath>
#include "skill_set.hpp"

namespace rln {

int Hero::level() const {
    return static_cast<int>(
        std::floor(1 + std::sqrt(100 - 2 * (50 - experience_)) / 10));
}

SkillSet* Hero::skills() {
    return skills_;
}

int Hero::mana() const {
    return mana_;
}

int Hero::max_mana() const {
    return max_mana_;
}

void Hero::spend_mana(int amount) {
    if (mana() < amount) {
        // throw?
    }
    mana_ -= amount;
}

void Hero::gain_mana(int amount) {
    mana_ = std::clamp(mana_ + amount, 0, max_mana());
}

}  // namespace rln
