#include "asleep_state.hpp"
#include "mob.hpp"
#include "mob_state.hpp"
#include "rest_action.hpp"

namespace rln {

AsleepState::AsleepState(Mob* mob) : MobState(mob) {}

Action* AsleepState::action(Game* game) {
    // TODO: replace new
    return new RestAction(game, mob()->position(), mob());
}

}  // namespace rln
