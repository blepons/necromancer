#include "mob_state.hpp"
#include "mob.hpp"

namespace rln {

MobState::MobState(Mob* mob) : mob_(mob) {}

Mob* MobState::mob() {
    return mob_;
}

Point MobState::position() {
    return mob()->position();
}

}  // namespace rln
