#pragma once

#include <memory>
#include "entity_action.hpp"

namespace rln {

class DisappearAction : public EntityAction {
public:
    DisappearAction(Game* game, Point pos, std::shared_ptr<Entity> entity);

    ActionResult perform() override;
};

}  // namespace rln
