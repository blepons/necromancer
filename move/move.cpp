#include "move.hpp"
#include <memory>

namespace rln {

Move::Move(int cooldown) : cooldown_(cooldown) {}

int Move::cooldown() const {
    return cooldown_;
}

bool Move::should_use(Game*, std::shared_ptr<Mob>) const {
    return true;
}

bool Move::should_use_on_damage(std::shared_ptr<Mob>, int) const {
    return false;
}

}  // namespace rln
