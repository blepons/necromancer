#pragma once

#include "entity_action.hpp"

namespace rln {

class RestAction : public EntityAction {
public:
    RestAction(Game* game, Point pos, Entity* entity);

    ActionResult perform() override;
};

}  // namespace rln
