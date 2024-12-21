#pragma once

#include <memory>
#include "entity_action.hpp"

namespace rln {

// TODO: should it be removed?
class DoNothingAction : public EntityAction {
public:
    DoNothingAction(Game* game, Point pos, std::shared_ptr<Entity> entity);

    ActionResult perform() override;
};

}  // namespace rln
