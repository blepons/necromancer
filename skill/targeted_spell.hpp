#pragma once

#include "spell.hpp"
#include "targeted_skill.hpp"

class TargetedSpell : public Spell, public ITargetedSkill {
protected:
    int range_;
};
