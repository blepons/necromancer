#pragma once

#include "entity_action.hpp"
#include <memory>

namespace rln {

class RestAction : public EntityAction {
public:
    RestAction(Game* game, Point pos, std::shared_ptr<Entity> entity);

    ActionResult perform() override;
};

}  // namespace rln
