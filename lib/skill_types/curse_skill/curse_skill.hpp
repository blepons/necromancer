#pragma once

#include <memory>
#include "targeted_skill.hpp"

namespace rln {

class CurseSkill : public TargetedSkill {
public:
    CurseSkill();

    int mana_cost(std::shared_ptr<Hero> hero, int level) override;

    int range(Game* game, int level) const override;

    int damage(std::shared_ptr<Hero> hero, int level) const;

    std::shared_ptr<Action> action(Game* game, int level, Point pos) override;

private:
    static constexpr int base_mana_cost = 20;
    static constexpr int base_range = 15;

    static constexpr int damage_increment = 5;
    static constexpr int mana_cost_increment = 3;
    static constexpr int range_increment = 2;
};

}  // namespace rln
