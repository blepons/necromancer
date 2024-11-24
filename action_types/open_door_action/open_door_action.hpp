#pragma once

#include "entity_action.hpp"

namespace rln {

class OpenDoorAction : public EntityAction {
public:
    OpenDoorAction(Game* game, Point pos, Entity* entity, Point door_pos);

    ActionResult perform() override;

private:
    Point door_pos_;
};

}  // namespace rln
