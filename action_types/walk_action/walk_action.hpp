#pragma once

#include <memory>
#include "direction.hpp"
#include "entity_action.hpp"

namespace rln {

class WalkAction : public EntityAction {
public:
    WalkAction(Game* game,
               Point pos,
               std::shared_ptr<Entity> entity,
               Direction dir);

    ActionResult perform() override;

private:
    Direction direction_;
};

}  // namespace rln
