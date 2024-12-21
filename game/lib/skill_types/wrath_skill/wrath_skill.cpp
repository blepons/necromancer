#include "wrath_skill.hpp"
#include <algorithm>
#include <memory>
#include "hero.hpp"
#include "wrath_action.hpp"

namespace rln {

WrathSkill::WrathSkill() : ActionSkill("wrath", 5) {}

int WrathSkill::mana_cost(std::shared_ptr<Hero>, int level) {
    auto calculated_mana_cost = base_mana_cost + mana_cost_increment * level;
    return std::max(0, calculated_mana_cost);
}

int WrathSkill::damage(std::shared_ptr<Hero> hero, int level) const {
    return hero->damage() + level * damage_increment;
}

std::shared_ptr<Action> WrathSkill::action(Game* game, int level) {
    return wrap_action(game->hero(), level,
                       std::make_shared<WrathAction>(
                           game, game->hero()->position(), game->hero(),
                           damage(game->hero(), level)));
}

}  // namespace rln
