#include "skill.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include "hero.hpp"
#include "skill_set.hpp"

namespace rln {

Skill::Skill(std::string identifier, int max_level)
    : identifier_(std::move(identifier)), max_level_(max_level) {}

json Skill::serialize() {
    json data = {{"identifier", identifier()}, {"max_level", max_level()}};
    return data;
}

int Skill::max_level() const {
    return max_level_;
}

int Skill::level(std::shared_ptr<Hero> hero) {
    return hero->skill_set().level(shared_from_this());
}

std::string Skill::identifier() const {
    return identifier_;
}

}  // namespace rln
