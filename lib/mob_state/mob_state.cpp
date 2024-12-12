#include "mob_state.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include "mob.hpp"

namespace rln {

MobState::MobState(std::shared_ptr<Mob> mob) : mob_(mob) {}

json MobState::serialize() {
    return {{"identifier", identifier()}};
}

std::shared_ptr<Mob> MobState::mob() {
    return mob_;
}

Point MobState::position() {
    return mob()->position();
}

}  // namespace rln
