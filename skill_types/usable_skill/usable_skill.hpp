#pragma once

#include <memory>
#include <string>
#include "entity_action.hpp"
#include "skill.hpp"

namespace rln {

class Game;
class Hero;

class UsableSkill : public Skill {
public:
    UsableSkill(std::string identifier, int max_level);

    virtual int mana_cost(std::shared_ptr<Hero> hero, int level) = 0;

    virtual bool usable(Game* game) = 0;

protected:
    std::unique_ptr<Action> wrap_action(std::shared_ptr<Hero> hero,
                                        int level,
                                        std::unique_ptr<EntityAction>&& action);
};

}  // namespace rln
