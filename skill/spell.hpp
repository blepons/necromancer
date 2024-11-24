#pragma once

#include "usable_skill.hpp"

class Spell : public UsableSkill {
protected:
    int base_mana_cost_;
    int base_damage_;
};
