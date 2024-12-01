#include "attack.hpp"
#include <memory>
#include "entity.hpp"

namespace rln {

Attack::Attack(int damage, int range) : damage_(damage), range_(range) {}

void Attack::perform(std::shared_ptr<Entity> source,
                     std::shared_ptr<Entity> target) {
    target->take_damage(nullptr, damage_, source);
}

bool Attack::ranged() const {
    return range_ > 0;
}

}  // namespace rln
