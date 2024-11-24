#pragma once

#include "action.hpp"

class IActionSkill {
public:
    Action* action(Game* game, int level);
};
