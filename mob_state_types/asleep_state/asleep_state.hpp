#pragma once

#include "mob_state.hpp"
#include <memory>

namespace rln {

class AsleepState : public MobState {
public:
    AsleepState(std::shared_ptr<Mob> mob);

    std::unique_ptr<Action> action(Game* game) override;
};

}  // namespace rln
