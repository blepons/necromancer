#pragma once

#include "entity_action.hpp"

namespace rln {

class Entity;

class AttackAction : public EntityAction {
public:
    AttackAction(Entity* attacker, Entity* target, Game* game, Point pos);

    ActionResult perform() override;

protected:
    Entity* target_;
};

}  // namespace rln
