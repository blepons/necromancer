#pragma once

#include <memory>
#include "entity_action.hpp"

namespace rln {

class ManaGainAction : public EntityAction {
public:
    ManaGainAction(Game* game,
                   Point pos,
                   std::shared_ptr<Hero> hero,
                   int amount);

    ActionResult perform() override;

private:
    int amount_;
};

}  // namespace rln
