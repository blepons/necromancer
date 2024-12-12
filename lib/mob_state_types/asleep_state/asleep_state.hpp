#pragma once

#include <memory>
#include <string>
#include "mob_state.hpp"

namespace rln {

class AsleepState : public MobState {
public:
    AsleepState(std::shared_ptr<Mob> mob);

    std::string identifier() const override;

    std::shared_ptr<Action> action(Game* game) override;
};

}  // namespace rln
