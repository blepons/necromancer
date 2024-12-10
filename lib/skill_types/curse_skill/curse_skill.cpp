#include "curse_skill.hpp"
#include <memory>
#include "bolt_attack_action.hpp"
#include "hero.hpp"

namespace rln {

CurseSkill::CurseSkill() : TargetedSkill("curse", 5) {}

int CurseSkill::mana_cost(std::shared_ptr<Hero>, int level) {
    return base_mana_cost + level * mana_cost_increment;
}

int CurseSkill::range(Game*, int level) const {
    return base_range + level * range_increment;
}

int CurseSkill::damage(std::shared_ptr<Hero> hero, int level) const {
    return hero->damage() + level * damage_increment;
}

std::shared_ptr<Action> CurseSkill::action(Game* game, int level, Point pos) {
    return std::make_shared<BoltAttackAction>(game, game->hero()->position(),
                                              pos, range(game, level),
                                              damage(game->hero(), level));
}

}  // namespace rln
