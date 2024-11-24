#pragma once

#include "mob_state.hpp"

namespace rln {

class AsleepState : public MobState {
public:
    AsleepState(Mob* mob);

    Action* action(Game* game) override;
};

}  // namespace rln
