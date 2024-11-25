#pragma once

#include "mob_state.hpp"
#include <memory>

namespace rln {

class WanderState : public MobState {
    WanderState(Mob* mob);

    std::unique_ptr<Action> action(Game* game) override;
};

}  // namespace rln
