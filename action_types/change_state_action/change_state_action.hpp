#pragma once

#include <memory>
#include "entity_action.hpp"
#include "mob_state.hpp"

namespace rln {

class ChangeStateAction : public EntityAction {
public:
    ChangeStateAction(Game* game,
                      Point pos,
                      std::shared_ptr<Entity> entity,
                      std::unique_ptr<MobState>&& state);

    ActionResult perform() override;

private:
    std::unique_ptr<MobState> state_;
};

}  // namespace rln
