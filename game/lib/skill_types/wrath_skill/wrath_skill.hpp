#pragma once

#include <memory>
#include "action_skill.hpp"

namespace rln {

class WrathSkill : public ActionSkill {
public:
    WrathSkill();

    int mana_cost(std::shared_ptr<Hero> hero, int level) override;

    int damage(std::shared_ptr<Hero> hero, int level) const;

    std::shared_ptr<Action> action(Game* game, int level) override;

private:
    static constexpr int base_mana_cost = 50;
    static constexpr int damage_increment = 10;
    static constexpr int mana_cost_increment = -5;
};

}  // namespace rln
