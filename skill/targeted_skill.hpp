#pragma once

#include "../action/action.hpp"
#include "skill.hpp"

class TargetedSkill : public Skill {
public:
    int range() const;

    Action* action(Game* game, int level, Point target);

protected:
    // ...???
};

// V4

namespace rln {

class ITargetedSkill {
public:
    int range() const;

    Action* action(Game* game, int level, Point target);
};

}  // namespace rln
