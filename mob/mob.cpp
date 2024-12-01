#include "mob.hpp"
#include <memory>
#include "mob_state.hpp"
#include "asleep_state.hpp"

namespace rln {

std::shared_ptr<Mob> Mob::getptr() {
    return std::static_pointer_cast<Mob>(shared_from_this());
}

void Mob::init(Point pos) {
    Entity::init(pos);
    state_ = std::make_unique<AsleepState>(getptr());
}

}  // namespace rln
