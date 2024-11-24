#pragma once

#include "action_skill.hpp"
#include "spell.hpp"

class ActionSpell : public Spell, public IActionSkill {};
