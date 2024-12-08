#include "desiccation_skill.hpp"
#include <memory>
#include "desiccation_action.hpp"
#include "hero.hpp"

namespace rln {

DesiccationSkill::DesiccationSkill() : TargetedSkill("desiccation", 5) {}

int DesiccationSkill::mana_cost(std::shared_ptr<Hero>, int) {
    return 0;
}

int DesiccationSkill::range(Game*, int level) const {
    return base_range + level * range_increment;
}

int DesiccationSkill::heal_amount(std::shared_ptr<Hero> hero, int level) const {
    return hero->damage() + level * stat_increment;
}

std::shared_ptr<Action> DesiccationSkill::action(Game* game,
                                                 int level,
                                                 Point pos) {
    return std::make_shared<DesiccationAction>(
        game, pos, game->hero(), range(game, level),
        heal_amount(game->hero(), level));
}

}  // namespace rln
