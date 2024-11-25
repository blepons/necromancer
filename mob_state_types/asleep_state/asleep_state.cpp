#include "asleep_state.hpp"
#include <memory>
#include "mob.hpp"
#include "mob_state.hpp"
#include "rest_action.hpp"

namespace rln {

AsleepState::AsleepState(Mob* mob) : MobState(mob) {}

std::unique_ptr<Action> AsleepState::action(Game* game) {
    return std::make_unique<RestAction>(game, mob()->position(), mob());
}

}  // namespace rln
