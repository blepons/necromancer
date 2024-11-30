#pragma once

#include <memory>
#include "mob_state.hpp"

namespace rln {

class WanderState : public MobState {
    WanderState(std::shared_ptr<Mob> mob);

    std::shared_ptr<Action> action(Game* game) override;
};

}  // namespace rln
