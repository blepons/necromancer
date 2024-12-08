#pragma once

#include <memory>
#include "targeted_skill.hpp"

namespace rln {

class DesiccationSkill : public TargetedSkill {
public:
    DesiccationSkill();

    int mana_cost(std::shared_ptr<Hero> hero, int level) override;

    int range(Game* game, int level) const override;

    int heal_amount(std::shared_ptr<Hero> hero, int level) const;

    std::shared_ptr<Action> action(Game* game, int level, Point pos) override;

private:
    static constexpr int base_range = 5;

    static constexpr int stat_increment = 3;

    static constexpr int range_increment = 2;
};

}  // namespace rln
