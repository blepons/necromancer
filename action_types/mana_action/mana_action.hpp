#pragma once

#include "action.hpp"
#include "entity_action.hpp"

namespace rln {

class ManaAction : public EntityAction {
    ManaAction(EntityAction* action, int mana_cost);

    ActionResult perform() override;
    // {
    //     return ActionResult(false, true, wrapped_action_);
    // }

protected:
    Action* wrapped_action_;
    int mana_cost_;
};

}  // namespace rln
