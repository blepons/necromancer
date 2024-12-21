#pragma once

#include <memory>
#include <string>
#include "point.hpp"
#include "usable_skill.hpp"

namespace rln {

class TargetedSkill : public UsableSkill {
public:
    TargetedSkill(std::string identifier, int max_level);

    virtual int range(Game* game, int level) const = 0;

    virtual std::shared_ptr<Action> action(Game* game,
                                           int level,
                                           Point pos) = 0;
};

}  // namespace rln
