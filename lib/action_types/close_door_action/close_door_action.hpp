#pragma once

#include <memory>
#include "entity_action.hpp"

namespace rln {

class CloseDoorAction : public EntityAction {
public:
    CloseDoorAction(Game* game,
                    Point pos,
                    std::shared_ptr<Entity> entity,
                    Point door_pos);

    ActionResult perform() override;

private:
    Point door_pos_;
};

}  // namespace rln
