#include "mob_state.hpp"
#include <memory>
#include "mob.hpp"

namespace rln {

MobState::MobState(std::shared_ptr<Mob> mob) : mob_(mob) {}

std::shared_ptr<Mob> MobState::mob() {
    return mob_;
}

Point MobState::position() {
    return mob()->position();
}

}  // namespace rln
