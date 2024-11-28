#include "usable_skill.hpp"
#include <memory>
#include <string>
#include <utility>
#include "mana_action.hpp"
#include "skill.hpp"

namespace rln {

UsableSkill::UsableSkill(std::string identifier, int max_level)
    : Skill(std::move(identifier), max_level) {}

std::unique_ptr<Action> UsableSkill::wrap_action(
    std::shared_ptr<Hero> hero,
    int level,
    std::unique_ptr<EntityAction>&& action) {
    return std::make_unique<ManaAction>(std::move(action),
                                        mana_cost(hero, level));
}

}  // namespace rln
