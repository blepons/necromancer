#pragma once

#include "mob_state.hpp"

namespace rln {

class WanderState : public MobState {
    WanderState(Mob* mob);

    Action* action(Game* game) override;
};

}  // namespace rln
