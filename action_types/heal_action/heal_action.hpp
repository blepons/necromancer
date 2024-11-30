#pragma once

#include <memory>
#include "entity_action.hpp"

namespace rln {

class HealAction : public EntityAction {
public:
    HealAction(Game* game,
               Point pos,
               std::shared_ptr<Entity> entity,
               int amount);

    ActionResult perform() override;

private:
    int amount_;
};

}  // namespace rln
