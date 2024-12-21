#include "necromancy_skill.hpp"
#include <memory>
#include <string>
#include "hero.hpp"
#include "necromancy_action.hpp"

namespace rln {

NecromancySkill::NecromancySkill() : TargetedSkill("necromancy", 5) {}

int NecromancySkill::mana_cost(std::shared_ptr<Hero>, int level) {
    return base_mana_cost + level * mana_cost_increment;
}

int NecromancySkill::range(Game*, int level) const {
    return base_range + level * range_increment;
}

std::string NecromancySkill::undead_type(std::shared_ptr<Hero>,
                                         int level) const {
    return undead_types_by_level_[level];
}

std::shared_ptr<Action> NecromancySkill::action(Game* game,
                                                int level,
                                                Point pos) {
    return wrap_action(game->hero(), level,
                       std::make_shared<NecromancyAction>(
                           game, pos, game->hero(), range(game, level),
                           undead_type(game->hero(), level)));
}

}  // namespace rln
