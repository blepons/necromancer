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

    virtual bool usable(Game* game);

protected:
    std::shared_ptr<EntityAction> wrap_action(
        std::shared_ptr<Hero> hero,
        int level,
        std::shared_ptr<EntityAction> action);
};

}  // namespace rln
