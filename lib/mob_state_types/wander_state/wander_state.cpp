#include "wander_state.hpp"
#include <memory>
#include <string>
#include "mob.hpp"

// TODO: remove temporary solution
#include "rest_action.hpp"

namespace rln {

WanderState::WanderState(std::shared_ptr<Mob> mob) : MobState(mob) {}

std::string WanderState::identifier() const {
    return "wander";
}

std::shared_ptr<Action> WanderState::action(Game* game) {
    // TODO: remove temporary solution
    return std::make_shared<RestAction>(game, mob()->position(), mob());
}

}  // namespace rln
