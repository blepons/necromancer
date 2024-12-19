#pragma once

#include <memory>
#include "direction.hpp"
#include "mob_state.hpp"

namespace rln {

class WanderState : public MobState {
public:
    WanderState(std::shared_ptr<Mob> mob);

    std::string identifier() const override;

    std::shared_ptr<Action> action(Game* game) override;

protected:
    Direction melee_dir(Game* game);

    Direction towards_enemy(Game* game);
};

}  // namespace rln
