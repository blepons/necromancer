#include "polymorph_skill.hpp"
#include <memory>
#include <string>
#include "hero.hpp"
#include "polymorph_action.hpp"

namespace rln {

PolymorphSkill::PolymorphSkill() : TargetedSkill("polymorph", 5) {}

int PolymorphSkill::mana_cost(std::shared_ptr<Hero>, int level) {
    return base_mana_cost + level * mana_cost_increment;
}

int PolymorphSkill::range(Game*, int level) const {
    return base_range + level * range_increment;
}

std::string PolymorphSkill::undead_type(std::shared_ptr<Hero>,
                                         int level) const {
    return undead_types_by_level_[level];
}

std::shared_ptr<Action> PolymorphSkill::action(Game* game,
                                                int level,
                                                Point pos) {
    return wrap_action(game->hero(), level,
                       std::make_shared<PolymorphAction>(
                           game, pos, game->hero(),
                           undead_type(game->hero(), level)));
}

}  // namespace rln
