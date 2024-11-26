#pragma once

#include <memory>
#include "entity_action.hpp"

namespace rln {

class Entity;

class AttackAction : public EntityAction {
public:
    AttackAction(std::shared_ptr<Entity> attacker,
                 std::shared_ptr<Entity> target,
                 Game* game,
                 Point pos);

    ActionResult perform() override;

protected:
    std::shared_ptr<Entity> target_;
};

}  // namespace rln
