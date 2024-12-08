#pragma once

#include <array>
#include <memory>
#include <string>
#include "targeted_skill.hpp"

namespace rln {

class NecromancySkill : public TargetedSkill {
public:
    NecromancySkill();

    int mana_cost(std::shared_ptr<Hero> hero, int level) override;

    int range(Game* game, int level) const override;

    std::string undead_type(std::shared_ptr<Hero>, int level) const;

    std::shared_ptr<Action> action(Game* game, int level, Point pos) override;

private:
    static constexpr int base_mana_cost = 20;
    static constexpr int base_range = 3;

    static constexpr int mana_cost_increment = 3;
    static constexpr int range_increment = 1;

    static constexpr std::array<std::string, 5> undead_types_by_level_ = {
        "ghost", "skeleton", "mummie", "zombie", "ghoul"};
};

}  // namespace rln
