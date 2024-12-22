#pragma once

#include <memory>
#include "entity_action.hpp"

namespace rln {

class SetBlockAction : public EntityAction {
public:
    SetBlockAction(Game* game,
                   Point pos,
                   std::shared_ptr<Entity> entity,
                   std::string tile_id);

    ActionResult perform() override;

private:
    std::string tile_id_;
};

}  // namespace rln
