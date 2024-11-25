#include "skill.hpp"
#include <string>
#include <utility>
#include "hero.hpp"
#include "skill_set.hpp"

namespace rln {

Skill::Skill(std::string identifier, int max_level)
    : identifier_(std::move(identifier)), max_level_(max_level) {}

int Skill::max_level() const {
    return max_level_;
}

int Skill::level(Hero* hero) {
    return hero->skill_set()->level(this);
}

std::string Skill::identifier() const {
    return identifier_;
}

}  // namespace rln
