#include "asleep_state.hpp"
#include <memory>
#include <string>
#include "mob.hpp"
#include "mob_state.hpp"
#include "rest_action.hpp"

namespace rln {

AsleepState::AsleepState(std::shared_ptr<Mob> mob) : MobState(mob) {}

std::string AsleepState::identifier() const {
    return "asleep";
}

std::shared_ptr<Action> AsleepState::action(Game* game) {
    return std::make_shared<RestAction>(game, mob()->position(), mob());
}

}  // namespace rln
