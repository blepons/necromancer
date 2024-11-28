#pragma once

#include <memory>
#include <string>
#include "usable_skill.hpp"

namespace rln {

class ActionSkill : public UsableSkill {
public:
    ActionSkill(std::string identifier, int max_level);

    virtual std::shared_ptr<Action> action(Game* game, int level) = 0;
};

}  // namespace rln
