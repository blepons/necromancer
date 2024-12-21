#pragma once

#include <memory>
#include "entity_action.hpp"

namespace rln {

class WrathAction : public EntityAction {
public:
    WrathAction(Game* game,
                Point pos,
                std::shared_ptr<Entity> entity,
                int damage);

    ActionResult perform() override;

private:
    int damage_;
};

}  // namespace rln
