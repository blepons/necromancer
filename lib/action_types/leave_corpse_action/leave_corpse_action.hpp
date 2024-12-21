#pragma once

#include <memory>
#include "entity_action.hpp"

namespace rln {

class LeaveCorpseAction : public EntityAction {
public:
    LeaveCorpseAction(Game* game, Point pos, std::shared_ptr<Mob> mob);

    ActionResult perform() override;
};

}  // namespace rln
