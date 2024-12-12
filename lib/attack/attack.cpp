#include "attack.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include "entity.hpp"

namespace rln {

Attack::Attack(int range) : range_(range) {}

json Attack::serialize() {
    return {{"range", range_}};
}

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
