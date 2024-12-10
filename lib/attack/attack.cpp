#include "attack.hpp"
#include <memory>
#include "entity.hpp"

namespace rln {

Attack::Attack(int range) : range_(range) {}

void Attack::perform(std::shared_ptr<Entity> source,
                     std::shared_ptr<Entity> target) {
    target->take_damage(nullptr, source->damage(), source);
}

bool Attack::ranged() const {
    return range_ > 0;
}

Attack Attack::melee() {
    return Attack(0);
}

}  // namespace rln
