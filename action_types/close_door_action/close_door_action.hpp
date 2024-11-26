#pragma once

#include "entity_action.hpp"
#include <memory>

namespace rln {

class CloseDoorAction : public EntityAction {
public:
    CloseDoorAction(Game* game, Point pos, std::shared_ptr<Entity> entity, Point door_pos);

    ActionResult perform() override;

private:
    Point door_pos_;
};

}  // namespace rln
