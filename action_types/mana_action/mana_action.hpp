#pragma once

#include <memory>
#include "action.hpp"
#include "entity_action.hpp"

namespace rln {

class ManaAction : public EntityAction {
    ManaAction(std::unique_ptr<EntityAction>&& action, int mana_cost);

    ActionResult perform() override;

protected:
    std::unique_ptr<EntityAction> wrapped_action_;
    int mana_cost_;
};

}  // namespace rln
