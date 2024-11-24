#pragma once

#include "../game.hpp"
#include "../hero.hpp"
#include "skill.hpp"

// TODO: decide if it should be merged into Skill
//       since every skill is usable right now
class UsableSkill : public Skill {
public:
    // hero is stored?
    int mana_cost(Hero* hero, int level);

    bool usable(Game* game);

protected:
    // action wrapper -> ManaAction
};
