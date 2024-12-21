#include "usable_skill.hpp"
#include <memory>
#include <string>
#include <utility>
#include "mana_action.hpp"
#include "skill.hpp"

namespace rln {

UsableSkill::UsableSkill(std::string identifier, int max_level)
    : Skill(std::move(identifier), max_level) {}

bool UsableSkill::usable(Game*) {
    return true;
}

std::shared_ptr<EntityAction> UsableSkill::wrap_action(
    std::shared_ptr<Hero> hero,
    int level,
    std::shared_ptr<EntityAction> action) {
    return std::make_shared<ManaAction>(std::move(action),
                                        mana_cost(hero, level));
}

}  // namespace rln
